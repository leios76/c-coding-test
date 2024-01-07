#include <stdio.h>
#include <string.h>
#include <stdint.h>

// #define RANDOM_RUN

#ifdef DEBUG_RUN
char * debug_line1 = "abaccaba";
char * debug_line2 = "guesswhoitisisitwhoguess";
char * debug_line3 = "xaabaababaaabxaa";
#ifdef RANDOM_RUN
#endif
#endif

struct word_t {
    int start;
    int length;
};

struct word_t words[1000 * 1000];
int word_index = 0;
char line[1000 * 1000];

int main(int q, char **x)
{
#ifdef DEBUG_RUN
#ifdef RANDOM_RUN
    srand(time(NULL));
#endif
#endif

    memset(words, 0, sizeof(words));
#ifdef DEBUG_RUN
    strcpy(line, debug_line3);
#else
    scanf("%s", line);
#endif

    int length = strlen(line);
    for (int i = 0; i < length / 2; i++) {
        words[word_index].length++;
#ifdef DEBUG_OUTPUT
        {
            char word[2][1000];
            memset(word, 0, sizeof(word));
            memcpy(word[0], line + words[word_index].start, words[word_index].length);
            memcpy(word[1], line + length - i - 1, words[word_index].length);
            printf("compare %d,%d %d %s %s\n", words[word_index].start, length - i - 1, words[word_index].length, word[0], word[1]);
        }
#endif
        if (memcmp(line + words[word_index].start, line + length - i - 1, words[word_index].length) == 0) {
            word_index++;
            words[word_index].start = i + 1;
        }
    }

    printf("%d\n", word_index);
    for (int i = 0; i < word_index; i++) {
        printf("%.*s\n", words[i].length, line + words[i].start);
    }
    return 0;
}