//
// Created by guanzhisong on 2023/3/22.
//

#ifndef ALGORITHM_C_SORT_H
#define ALGORITHM_C_SORT_H

#include <stddef.h>

typedef int SortElem;

typedef struct {
    const void *arr;
    size_t arr_len;
    size_t arr_elem_len;

    int (*compare)(const void *, const void *);

    void (*swap)(const void *, const void *);

    void (*set)(const void *, const void *);
} sort_struct, *p_sort_struct;

void bubble_sort(p_sort_struct pss);

void insert_sort(p_sort_struct pss);

void binary_insert_sort(p_sort_struct pss);

void insert_sort_by_step(p_sort_struct pss, int start, int end, int step);

void select_sort(p_sort_struct pss);

void quick_sort(p_sort_struct pss);

void merge_sort(p_sort_struct pss);

#endif //ALGORITHM_C_SORT_H
