#include <stdio.h>
#include <string.h>
#include <stdint.h>

//#define RANDUM_RUN

#ifdef RANDUM_RUN
int max_monster_count = 10000;
int max_monster_health = 1000 * 1000 * 1000;
#endif

#define CLUSTER_SIZE    16
#define CLUSTER_COUNT   ((1000 * 1000 * 1000 + (1 << CLUSTER_SIZE) - 1) / (1 << CLUSTER_SIZE))

struct monster_t {
    int index;
    int health;
    uint64_t death_time;

    int prev_index;
    int next_index;
};

struct monster_t monster_pool[100000];
struct monster_t monster_pool_verify1[100000];
struct monster_t monster_pool_verify2[100000];
int head_index_table[CLUSTER_COUNT];
int tail_index_table[CLUSTER_COUNT];

uint64_t dead_bitmap[(100 * 1000 + 63) / 64];

int dead_count_map1[(100 * 1000 + 4095) / 4096];
int dead_count_map2[(100 * 1000 + 63) / 64];

int main()
{
    int total_monster_count = 0;
    int alive_monster_count = 0;

    int curr_index;
    int table_index;
    int direction;

    uint64_t tick = 0;
    int turn = 0;

    memset(monster_pool, 0xFF, sizeof(monster_pool));
    memset(head_index_table, 0xFF, sizeof(head_index_table));
    memset(tail_index_table, 0xFF, sizeof(tail_index_table));

    memset(dead_bitmap, 0, sizeof(dead_bitmap));

    memset(dead_count_map1, 0, sizeof(dead_count_map1));
    memset(dead_count_map2, 0, sizeof(dead_count_map2));

#ifdef RANDUM_RUN
    srand(time(NULL));
    total_monster_count = rand() % max_monster_count + 1;
#else
    scanf("%d", &total_monster_count);
#endif

    for (int i = 0; i < total_monster_count; i++) {
        monster_pool[i].index = i;

#ifdef RANDUM_RUN
        monster_pool[i].health = rand() % (max_monster_health) + 1;
#else
        scanf("%d", &monster_pool[i].health);
#endif
        table_index = monster_pool[i].health >> CLUSTER_SIZE;

        direction = (monster_pool[i].health >> (CLUSTER_SIZE - 1)) & 0x01;
        if (direction) {
            curr_index = tail_index_table[table_index];
        } else {
            curr_index = head_index_table[table_index];
        }
        while (curr_index > -1) {
            if (direction) {
                if (monster_pool[curr_index].health < monster_pool[i].health || (monster_pool[curr_index].health == monster_pool[i].health && curr_index < i)) {
                    // insert after curr_index
                    if (monster_pool[curr_index].next_index == -1) {
#ifdef DEBUG_OUTPUT
                        printf("[%d] insert new monster(%d, %d) after tail(%d, %d)\n", table_index, i, monster_pool[i].health, curr_index, monster_pool[curr_index].health);
#endif
                        monster_pool[curr_index].next_index = i;
                        monster_pool[i].prev_index = tail_index_table[table_index];
                        tail_index_table[table_index] = i;
                    } else {
#ifdef DEBUG_OUTPUT
                        printf("[%d] insert new monster(%d, %d) before monster(%d, %d), after monster(%d, %d)\n", table_index, i, monster_pool[curr_index].next_index, monster_pool[monster_pool[curr_index].next_index].health, monster_pool[i].health, curr_index, monster_pool[curr_index].health);
#endif
                        monster_pool[monster_pool[curr_index].next_index].prev_index = i;
                        monster_pool[i].next_index = monster_pool[curr_index].next_index;

                        monster_pool[curr_index].next_index = i;
                        monster_pool[i].prev_index = curr_index;
                    }
                    break;
                }

                if (monster_pool[curr_index].prev_index == -1) {
#ifdef DEBUG_OUTPUT
                    printf("[%d] insert new monster(%d, %d) before head(%d, %d)\n", table_index, i, monster_pool[i].health, curr_index, monster_pool[curr_index].health);
#endif
                    monster_pool[curr_index].prev_index = i;
                    monster_pool[i].next_index = curr_index;
                    head_index_table[table_index] = i;
                    break;
                }
                curr_index = monster_pool[curr_index].prev_index;
            } else {
                if (monster_pool[curr_index].health > monster_pool[i].health || (monster_pool[curr_index].health == monster_pool[i].health && curr_index > i)) {
                    // insert before curr_index
                    if (monster_pool[curr_index].prev_index == -1) {
#ifdef DEBUG_OUTPUT
                        printf("[%d] insert new monster(%d, %d) before head(%d, %d)\n", table_index, i, monster_pool[i].health, curr_index, monster_pool[curr_index].health);
#endif
                        monster_pool[curr_index].prev_index = i;
                        monster_pool[i].next_index = head_index_table[table_index];
                        head_index_table[table_index] = i;
                    } else {
#ifdef DEBUG_OUTPUT
                        printf("[%d] insert new monster(%d, %d) before monster(%d, %d), after monster(%d, %d)\n", table_index, i, monster_pool[i].health, curr_index, monster_pool[curr_index].health, monster_pool[curr_index].prev_index, monster_pool[monster_pool[curr_index].prev_index].health);
#endif
                        monster_pool[monster_pool[curr_index].prev_index].next_index = i;
                        monster_pool[i].prev_index = monster_pool[curr_index].prev_index;

                        monster_pool[curr_index].prev_index = i;
                        monster_pool[i].next_index = curr_index;
                    }
                    break;
                }

                if (monster_pool[curr_index].next_index == -1) {
#ifdef DEBUG_OUTPUT
                    printf("[%d] insert new monster(%d, %d) after tail(%d, %d)\n", table_index, i, monster_pool[i].health, curr_index, monster_pool[curr_index].health);
#endif
                    monster_pool[curr_index].next_index = i;
                    monster_pool[i].prev_index = curr_index;
                    tail_index_table[table_index] = i;
                    break;
                }
                curr_index = monster_pool[curr_index].next_index;
            }
        }

        if (head_index_table[table_index] == -1) {
#ifdef DEBUG_OUTPUT
            printf("[%d] set head new monster(%d, %d)\n", table_index, i, monster_pool[i].health);
#endif
            head_index_table[table_index] = i;
        }
        if (tail_index_table[table_index] == -1) {
#ifdef DEBUG_OUTPUT
            printf("[%d] set tail new monster(%d, %d)\n", table_index, i, monster_pool[i].health);
#endif
            tail_index_table[table_index] = i;
        }
    }

    alive_monster_count = total_monster_count;

#ifdef DEBUG_OUTPUT
    for (int i = 0; i < CLUSTER_COUNT; i++) {
        curr_index = head_index_table[i];
        while (curr_index > -1) {
            printf("[%08d] %03d] h%010d n%08d\n", i, curr_index, monster_pool[curr_index].health, monster_pool[curr_index].next_index);
            curr_index = monster_pool[curr_index].next_index;
        }
    }
#endif


    for (int i = 0; i < CLUSTER_COUNT; i++) {
        while (head_index_table[i] > -1) {
    #ifdef DEBUG_OUTPUT
            printf("pass tick: %lu -> %lu\n", tick, tick + (uint64_t)(monster_pool[head_index_table[i]].health - turn) * alive_monster_count);
    #endif
            tick += (uint64_t)(monster_pool[head_index_table[i]].health - turn) * alive_monster_count;
            turn += monster_pool[head_index_table[i]].health - turn;
            curr_index = head_index_table[i];
            int dead_monster_count = 0;
            int distance = 0;
            int ordered_curr_index = -1;
            while (curr_index > -1) {
                if (monster_pool[curr_index].health > turn) {
    #ifdef DEBUG_OUTPUT
                    printf("next: turn %d, monster(%d, %d)\n", turn, curr_index, monster_pool[curr_index].health);
    #endif
                    break;
                } else if (monster_pool[curr_index].health == turn) {
                    for (; ordered_curr_index < total_monster_count;) {
                        if (((ordered_curr_index + 1) % 4096) == 0 && ordered_curr_index + 4096 < curr_index) {
#ifdef DEBUG_OUTPUT
                            printf("jump distance %d -> %d, distance %d + %d\n", ordered_curr_index, ordered_curr_index + 4096, distance, 4096 - dead_count_map1[(ordered_curr_index + 4096) / 4096]);
#endif
                            distance += 4096 - dead_count_map1[(ordered_curr_index + 4096) / 4096];
                            ordered_curr_index += 4096;
                        } else if (((ordered_curr_index + 1) % 64) == 0 && ordered_curr_index + 64 < curr_index) {
#ifdef DEBUG_OUTPUT
                            printf("jump distance %d -> %d, distance %d + %d\n", ordered_curr_index, ordered_curr_index + 64, distance, 64 - dead_count_map2[(ordered_curr_index + 64) / 64]);
#endif
                            distance += 64 - dead_count_map2[(ordered_curr_index + 64) / 64];
                            ordered_curr_index += 64;
                        } else {
                            ordered_curr_index++;
                            if (!(dead_bitmap[ordered_curr_index / 64] & (1ULL << (ordered_curr_index % 64)))) {
                                distance++;
                            }
                        }
                        if (ordered_curr_index == curr_index) {
                            break;
                        }
                    }
#ifdef DEBUG_OUTPUT
                    printf("remove: turn %u, monster(%d, %d), death_time: %lu - %d + %d\n", turn, curr_index, monster_pool[curr_index].health, tick, alive_monster_count, distance);
#endif
                    monster_pool[curr_index].death_time = tick - alive_monster_count + distance;
                    dead_count_map1[curr_index / 4096]++;
                    dead_count_map2[curr_index / 64]++;
                    dead_bitmap[curr_index / 64] |= (1ULL << (curr_index % 64));
#ifdef DEBUG_OUTPUT
                    printf("decrease count1 %d => %d, count2 %d => %d clear map[%d] mask(0x%016llX) value (0x%016lX)\n", curr_index / 4096, dead_count_map1[curr_index / 4096], curr_index / 64, dead_count_map2[curr_index / 64], curr_index / 64, (1ULL << (curr_index % 64)), dead_bitmap[curr_index / 64]);
#endif

                    // remove monster
                    if (monster_pool[curr_index].prev_index > -1) {
                        monster_pool[monster_pool[curr_index].prev_index].next_index = monster_pool[curr_index].next_index;
                    } else {
                        head_index_table[i] = monster_pool[curr_index].next_index;
                    }
                    if (monster_pool[curr_index].next_index > -1) {
                        monster_pool[monster_pool[curr_index].next_index].prev_index = monster_pool[curr_index].prev_index;
                    }

                    dead_monster_count++;
                } else {
#ifdef DEBUG_OUTPUT
                    printf("unknown case: turn %d, monster(%d, %d)\n", turn, curr_index, monster_pool[curr_index].health);
#endif
                }
                curr_index = monster_pool[curr_index].next_index;
            }
            alive_monster_count -= dead_monster_count;
        }
    }

#ifdef DEBUG_RUN
    int found = 0;
    tick = 0;
    memcpy(monster_pool_verify1, monster_pool, sizeof(monster_pool));
    while (1) {
        int min_health = 1000 * 1000 * 1000;
        found = 0;
        for (int i = 0; i < total_monster_count; i++) {
            if (monster_pool_verify1[i].health > 0 && min_health > monster_pool_verify1[i].health) {
                min_health = monster_pool_verify1[i].health;
            }
        }
        if (min_health > 1) {
            min_health--;
        }
        for (int i = 0; i < total_monster_count; i++) {
            if (monster_pool_verify1[i].health >= min_health) {
                monster_pool_verify1[i].health -= min_health;
                tick += min_health;
                found = 1;
                if (monster_pool_verify1[i].health == 0) {
                    monster_pool_verify1[i].death_time = tick;
                }
            }
        }
        if (!found) {
            break;
        }
    }
#if 0
    tick = 0;
    memcpy(monster_pool_verify2, monster_pool, sizeof(monster_pool));
    while (1) {
        found = 0;
        for (int i = 0; i < total_monster_count; i++) {
            if (monster_pool_verify2[i].health > 0) {
                monster_pool_verify2[i].health--;
                tick++;
                found = 1;
                if (monster_pool_verify2[i].health == 0) {
                    monster_pool_verify2[i].death_time = tick;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    found = 0;
    for (int i = 0; i < total_monster_count; i++) {
        if (monster_pool[i].death_time != monster_pool_verify1[i].death_time || monster_pool[i].death_time != monster_pool_verify2[i].death_time) {
#ifdef DEBUG_OUTPUT
            printf("[%4d, %04d] %6ld -- (X) %6ld %6ld\n", i, monster_pool[i].health, monster_pool[i].death_time, monster_pool_verify1[i].death_time, monster_pool_verify2[i].death_time);
#endif
            found = 1;
        } else {
#ifdef DEBUG_OUTPUT
            printf("[%4d, %04d] %6ld -- ( ) %6ld %6ld\n", i, monster_pool[i].health, monster_pool[i].death_time, monster_pool_verify1[i].death_time, monster_pool_verify2[i].death_time);
#endif
        }
    }
#else
    found = 0;
    for (int i = 0; i < total_monster_count; i++) {
        if (monster_pool[i].death_time != monster_pool_verify1[i].death_time) {
#ifdef DEBUG_OUTPUT
            printf("[%4d, %04d] %6ld -- (X) %6ld\n", i, monster_pool[i].health, monster_pool[i].death_time, monster_pool_verify1[i].death_time);
#endif
            found = 1;
        } else {
#ifdef DEBUG_OUTPUT
            printf("[%4d, %04d] %6ld -- ( ) %6ld\n", i, monster_pool[i].health, monster_pool[i].death_time, monster_pool_verify1[i].death_time);
#endif
        }
    }
#endif
    if (found) {
        fprintf(stderr, "======================NOK!!!\n");
    }
#else
    for (int i = 0; i < total_monster_count; i++) {
        printf("%ld\n", monster_pool[i].death_time);
    }
#endif
    return 0;
}
