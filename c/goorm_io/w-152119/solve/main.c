#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int m;
    int s[5000];
    int t[5000];
    int a[5000];
    int b[5000];
    int c[5000];
};
struct context_t context;

int r(struct context_t * ctx, int i, int type_s, int type_t)
{
    int t;
    int v;
    int p;
    if (ctx->m == i) {
        return 0;
    }

    if (1) {
        if (type_s == type_t) {
            if (type_s == 0) {
                p = ctx->a[i];
            } else {
                p = ctx->c[i];
            }
        } else {
            p = ctx->b[i];
        }
        v = 1e9;
        t = r(ctx, i + 1, 0, 0) + p;
        if (v > t) {
            v = t;
        }
        t = r(ctx, i + 1, 0, 1) + p;
        if (v > t) {
            v = t;
        }
        t = r(ctx, i + 1, 1, 0) + p;
        if (v > t) {
            v = t;
        }
        t = r(ctx, i + 1, 1, 1) + p;
        if (v > t) {
            v = t;
        }
    }
    return v;
}

int solve(struct context_t * ctx)
{
    /*
    도로번호
    도시번호
    도시종류
    도로가격
    dp[][][][] = 도로 가격 합산

    음식 번호
    1번 인덕션 온도
    2번 인덕션 온도
    3번 인덕션 온도
    음식 온도
    dp[음식번호][1번 인덕션 온도][2번 인덕션 온도][3번 인덕션 온도] = 온도 조작 수 합산

    사건 번호
    경찰차1 최종 사건
    경찰차2 최종 사건

    dp[경찰차1 최종 사건 번호][경찰차2 최종 사건 번호] = 이동거리 합산
    */
    int p1 = r(ctx, 0, 0, 0);
    int p2 = r(ctx, 0, 0, 1);
    return (p1 > p2) ? p2 : p1;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d", &ctx->n, &ctx->m);

    for (int i = 0; i < ctx->m; i++) {
        scanf("%d %d %d %d %d", &ctx->s[i], &ctx->t[i], &ctx->a[i], &ctx->b[i], &ctx->c[i]);
    }
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
