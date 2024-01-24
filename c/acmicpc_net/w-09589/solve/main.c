#include <stdio.h>
#include <string.h>
#include <stdint.h>

// #define RANDOM_RUN

struct color_combi_info_t {
    uint64_t input_mask;
    int output_index;
};

struct color_t {
    char color[128];
    int index;
    float cert;
};
struct c_color_t {
    struct color_t colors[300];
    int colors_count;
};

char color_table[300][128];
int color_table_count = 0;

struct color_combi_info_t combination_table[100];
int combination_table_count = 0;

struct c_color_t c_colors[500];
int c_colors_count = 0;

int c_color_case[500];

int add_color_table(char * c)
{
    strcpy(color_table[color_table_count++], c);
    return color_table_count;
}

int find_color_table(char * c)
{
    for (int i = 0; i < color_table_count; i++) {
        if (strcmp(c, color_table[i]) == 0) {
            return i;
        }
    }
    return add_color_table(c);
}

int mix_color(char * a, char * b)
{
    uint64_t mask;
    mask = (1ULL << (find_color_table(a))) | (1ULL << (find_color_table(b)));
    for (int i = 0; i < combination_table_count; i++) {
        if (combination_table[i].input_mask == mask) {
            return combination_table[i].output_index;
        }
    }
    return -1;
}


int main(int q, char **x)
{
    int r;
    int t;
    int c;
    char color1[128];
    char color2[128];
    char color3[128];
    int color_index1;
    int color_index2;
    int color_index3;
    float cert;
#ifdef DEBUG_RUN
#ifdef RANDOM_RUN
    srand(time(NULL));
#endif
#endif

    memset(combination_table, 0, sizeof(combination_table));
    memset(color_table, 0, sizeof(color_table));

    scanf("%d", &r);

    for (int i = 0; i < r; i++) {
        scanf("%s %s %s", color1, color2, color3);
        color_index1 = find_color_table(color1);
        color_index2 = find_color_table(color2);
        color_index3 = find_color_table(color3);

        combination_table[combination_table_count].input_mask = (1ULL << color_index1) | (1ULL << color_index2);
        combination_table[combination_table_count].output_index = color_index3;
#ifdef DEBUG_OUTPUT
        printf("0x%08lX -> %d\n", combination_table[combination_table_count].input_mask, combination_table[combination_table_count].output_index);
#endif
    }

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d", &c);
        memset(c_colors, 0, sizeof(c_colors));
        for (int j = 0; j < c; j++) {
            while (1) {
                scanf("%s", c_colors[j].colors[c_colors[j].colors_count].color);
                if (strcmp(c_colors[j].colors[c_colors[j].colors_count].color, "END") == 0) {
                    break;
                } else {
                    scanf("%f", &c_colors[j].colors[c_colors[j].colors_count].cert);
                    c_colors[j].colors[c_colors[j].colors_count].index = find_color_table(c_colors[j].colors[c_colors[j].colors_count].color);
#ifdef DEBUG_OUTPUT
                    printf("%s %d %f\n", c_colors[j].colors[c_colors[j].colors_count].color, c_colors[j].colors[c_colors[j].colors_count].index, c_colors[j].colors[c_colors[j].colors_count].cert);
#endif
                    c_colors[j].colors_count++;
                }
            }
        }

    }

    return 0;
}