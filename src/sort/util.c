//
// Created by guanzhisong on 2023/3/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "sort.h"


void print_arr(int *arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        printf("%d,", arr[i]);
    }
    printf("%d\n", arr[len - 1]);
}

void build_random_int_arr(int *base, size_t size, int bound) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        *(base + i) = (rand() % bound);
    }
}

int is_sorted(const void *base, uint64_t len, size_t size, int(*cmp)(const void *, const void *)) {
    uint64_t end = len * size;
    for (int i = 0; i < end - size; i += size) {
        if (cmp(base + i, base + i + size) > 0) {
            return 0;
        }
    }
    return 1;
}