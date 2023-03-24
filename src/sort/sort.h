//
// Created by guanzhisong on 2023/3/22.
//

#ifndef ALGORITHM_C_SORT_H
#define ALGORITHM_C_SORT_H

#define MIN_INSERT_LEN 32

#include <stddef.h>
#include <stdint.h>

typedef struct {
    const void *arr;
    uint64_t arr_len;
    uint32_t arr_elem_len;

    int (*compare)(const void *, const void *);

    void (*swap)(const void *, const void *);

    void (*set)(const void *, const void *);
} sort_struct, *p_sort_struct;

void bubble_sort(p_sort_struct pss);

void insert_sort(p_sort_struct pss);

void binary_insert_sort(p_sort_struct pss);

void insert_sort_by_step(p_sort_struct pss, uint64_t start, uint64_t end, uint32_t step);

void select_sort(p_sort_struct pss);

void quick_sort(p_sort_struct pss);

void merge_sort(p_sort_struct pss);

#endif //ALGORITHM_C_SORT_H
