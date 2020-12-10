#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int hitCount = 0;
int missCount = 0;
int evictionCount = 0;

typedef struct {
    int valid;
    int tag;
    int stamp;
} CacheLine, *CacheSet, **Cache;

typedef struct {
    int h;      // Optional help flag that prints usage info.
    int v;      // Optional verbose flag that displays trace info.
    int s;      // Number of set index bits.
    int E;      // Number of lines per set.
    int b;      // Number of block bits
    char t[100];// Name of the valgrind trace to replay.
} Arguments;

Arguments initArgs(int argc, char* argv[]) {
    Arguments args;
    args.h = 0;
    args.v = 0;
    int opt;
    while(-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))) {
        switch(opt) {
            case 'h':
                args.h = 1;
                break;
            case 'v':
                args.v = 1;
                break;
            case 's':
                args.s = atoi(optarg);
                break;
            case 'E':
                args.E = atoi(optarg);
                break;
            case 'b':
                args.b = atoi(optarg);
                break;
            case 't':
                strcpy(args.t, optarg);
                break;
            default:
                break;
        }
    }
    return args;
}

Cache initCache(Arguments args) {
    int S = 1 << args.s;
    int E = args.E;
    Cache cache = (Cache) malloc(sizeof(CacheSet) * S);
    for(int i = 0; i < S; i++) {
        cache[i] = (CacheSet) malloc(sizeof(CacheLine) * E);
        for(int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].tag = -1;
            cache[i][j].stamp = -1;
        }
    }
    return cache;
}

void freeCache(Cache cache, Arguments args) {
    int S = 1 << args.s;
    for(int i = 0; i < S; i++) {
        free(cache[i]);
    }
    free(cache);
}

void get(Cache cache, Arguments args, int address) {
    long mask = 0xffffffffffffffff >> (64 - args.s);
    int setIndex = (address >> args.b) & mask;
    int tag = address >> (args.b + args.s);
    CacheSet set = cache[setIndex];
    
    // LRU
    int E = args.E;

    // Update all stamps of one set that hits.
    for(int i = 0; i < E; i++) {
        if(1 == set[i].valid) {
            set[i].stamp++;
        }
    }

    // Cache hits.
    for(int i = 0; i < E; i++) {
        if(1 == set[i].valid && set[i].tag == tag) {
            set[i].stamp = 0;
            hitCount++;
            return;
        }
    }

    // Cache doesn't hit.
    missCount++;
    // Check for an invalid line.
    for(int i = 0; i < E; i++) {
        if(0 == set[i].valid) {
            set[i].valid = 1;
            set[i].tag = tag;
            return;
        }
    }

    // Neither hit or an invalid line, then eviction happens.
    evictionCount++;
    int maxStamp = set[0].stamp;
    int maxLineIndex = 0;
    for(int i = 1; i < E; i++) {
        if(set[i].stamp > maxStamp) {
            maxStamp = set[i].stamp;
            maxLineIndex = i;
        }
    }
    set[maxLineIndex].tag = tag;
    set[maxLineIndex].stamp = 0;
}

void parseTrace(Cache cache, Arguments args) {
    char type;
    int address;
    int size;
    FILE* fp = fopen(args.t, "r");
    if(fp == NULL) {
        printf("Open error!");
        exit(0);
    }
    while(fscanf(fp, " %c %x,%d", &type, &address, &size) > 0) {
        switch(type) {
            case 'L':
                get(cache, args, address);
                break;
            // Modify operation results in accessing to cache twice.
            case 'M':
                get(cache, args, address);
                get(cache, args, address);
                break;
            case 'S':
                get(cache, args, address);
                break;
            default:
                break;
        }
    }
    fclose(fp);
}

int main(int argc, char* argv[]) {
    Arguments args = initArgs(argc, argv);
    Cache cache = initCache(args);
    parseTrace(cache, args);
    freeCache(cache, args);
    printSummary(hitCount, missCount, evictionCount);
    return 0;
}
