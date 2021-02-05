#include "cachelab.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Cacheline
{
    int valid;
    int tag;
    int stamp;
}Cacheline;

Cacheline **Cache;
char *path;
char line[1024];
int Hits, Misses, Evicts;

void initCache(int s, int E) {
    int S = (1 << s);
    Cache = (Cacheline**)malloc(S * sizeof(Cacheline*));
    
    for (int i = 0; i < S; ++i) {
        Cache[i] = (Cacheline*)malloc(E * sizeof(Cacheline));
        for (int j = 0; j < E; ++j) {
            Cache[i][j].valid = 0;
            Cache[i][j].tag = -1;
            Cache[i][j].stamp = -1;
        }
    }
}

void update(uint64_t addr, int s, int E, int b) {
    unsigned index = (addr >> b) & ((1 << s) - 1);
    unsigned tag = addr >> (s + b);
    int64_t MAXSTAMP = INT64_MIN;
    int MAXINDEX = 0;

    // 如果命中这更新这一行
    for (int j = 0; j < E; ++j) {
        if (Cache[index][j].tag == tag && Cache[index][j].valid == 1) {
            Cache[index][j].stamp = 0;
            ++Hits;
            return;
        }
    }

    // 没命中，找个空行放进去
    for (int j = 0; j < E; ++j) {
        if (Cache[index][j].valid == 0) {
            Cache[index][j].tag = tag;
            Cache[index][j].stamp = 0;
            Cache[index][j].valid = 1;
            ++Misses;
            return;
        }
    }

    // 没有空行了，需要按照 LRU 替换一个最少使用的行（stamp 最大）
    for (int j = 0; j < E; ++j) {
        if (Cache[index][j].stamp > MAXSTAMP) {
            MAXSTAMP = Cache[index][j].stamp;
            MAXINDEX = j;
        }
    }
    Cache[index][MAXINDEX].tag = tag;
    Cache[index][MAXINDEX].valid = 1;
    Cache[index][MAXINDEX].stamp = 0;
    ++Misses;
    ++Evicts;
    return;
}

void updateStamp(int s, int E) {
    int S = (1 << s);
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < E; ++j) {
            if (Cache[i][j].valid == 1) {
                ++Cache[i][j].stamp;
            }
        }
    }
}

void freeCache(int s) {
    int S = (1 << s);
    for (int i = 0; i < S; ++i) free(Cache[i]);
    free(Cache);
}

int main(int argc, char **argv)
{
    int s, E, b, size;
    char op;
    uint64_t addr;

    // parse arguments
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            switch (argv[i][1])
            {
                case 's':
                    s = argv[++i][0] - '0';
                    break;
                case 'E':
                    E = argv[++i][0] - '0';
                    break;
                case 'b':
                    b = argv[++i][0] - '0';
                    break;
                case 't':
                    path = argv[++i];
                    break;
                default:
                    break;
            }
        }
    }

    // initial cache
    initCache(s, E);

    // read instruction from tracefile
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("invalid tracefile: %s\n", path);
        exit(-1);
    }
    while (fgets(line, 100, fp) != NULL)
    {
        sscanf(line, " %c %lx,%d", &op, &addr, &size);
        switch (op)
        {
            case 'L': case 'S':
                update(addr, s, E, b);
                break;
            case 'M':
                update(addr, s, E, b);
                update(addr, s, E, b);
                break;
            default:
                break;
        }
        updateStamp(s, E);
    }
    
    // release
    fclose(fp);
    freeCache(s);

    printSummary(Hits, Misses, Evicts);
    return 0;
}
