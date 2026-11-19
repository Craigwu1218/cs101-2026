#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SETS 5
#define NUM_COUNT 7
#define MAX_NUM 69

void gen_one_set(int set[NUM_COUNT])
{
    int used[MAX_NUM + 1] = {0};
    int i, j, tmp, n;

    for (i = 0; i < NUM_COUNT; i++) {
        do {
            n = rand() % MAX_NUM + 1;
        } while (used[n]);
        used[n] = 1;
        set[i] = n;
    }

    for (i = 0; i < NUM_COUNT - 2; i++) {
        for (j = 0; j < NUM_COUNT - 2 - i; j++) {
            if (set[j] > set[j + 1]) {
                tmp = set[j];
                set[j] = set[j + 1];
                set[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    int n, i, j;
    int sets[MAX_SETS][NUM_COUNT];
    time_t now;
    char *timestr;
    FILE *fp;

    srand((unsigned)time(NULL));

    printf("歡迎光臨長庚樂透彩購買機台\n");
    do {
        printf("請問您要買幾組樂透彩：");
        if (scanf("%d", &n) != 1) {
            return 1;
        }
    } while (n < 1 || n > MAX_SETS);

    for (i = 0; i < n; i++) {
        gen_one_set(sets[i]);
    }

    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟 lotto.txt\n");
        return 1;
    }

    now = time(NULL);
    timestr = ctime(&now);
    timestr[24] = '\0';             

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", timestr);

    for (i = 0; i < MAX_SETS; i++) {
        fprintf(fp, "[%d]:", i + 1);
        for (j = 0; j < NUM_COUNT; j++) {
            if (i < n)
                fprintf(fp, " %02d", sets[i][j]);
            else
                fprintf(fp, " --");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
