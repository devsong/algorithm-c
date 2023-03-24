//
// Created by guanzhisong on 2023/3/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include "sort.h"
#include "util.h"

void recursive_quick_sort(const p_sort_struct pss, int low, int high);

int partition(const p_sort_struct pss, int start, int end);

void inner_merge_sort(const p_sort_struct pss, int start, int end, const void *extra);

void merge(const p_sort_struct pss, int low, int mid, int high, const void *extra);

int upper(const void *arr, size_t elem_len, int start, int end, const void *target,
          int (*compare)(const void *, const void *));

void swap_int_array(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int calcMidIndex(int low, int high) {
    return low + ((high - low) >> 1);
}

void bubble_sort(p_sort_struct s) {
    int len = s->arr_len;
    int elem_len = s->arr_elem_len;
    const void *arr = s->arr;
    for (int i = 0; i < len; i++) {
        int swap_cnt = 0;
        for (int j = 0; j < len - 1 - i; j++) {
            int offset = j * elem_len, offset_next = (j + 1) * elem_len;
            if (s->compare(arr + offset, arr + offset_next) > 0) {
                s->swap(arr + offset, arr + offset_next);
                swap_cnt++;
            }
        }
        if (swap_cnt == 0) {
            break;
        }
    }
}

void insert_sort_by_step(p_sort_struct pss, int start, int end, int step) {
    size_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    const void *pivot = (void *) malloc(elem_len);
    for (int i = start; i <= end; i += step) {
        pss->set(pivot, arr + i * elem_len);
        int j = i;
        while (j > start && pss->compare(arr + (j - step) * elem_len, pivot) > 0) {
            pss->set(arr + j * elem_len, arr + (j - step) * elem_len);
            j -= step;
        }
        pss->set(arr + j * elem_len, pivot);
    }
    free(pivot);
}

void insert_sort(p_sort_struct pss) {
    insert_sort_by_step(pss, 0, pss->arr_len - 1, 1);
}

void binary_insert_sort(p_sort_struct pss) {
    int len = pss->arr_len;
    int elem_len = pss->arr_elem_len;
    void *arr = pss->arr;
    const void *pivot = (void *) malloc(elem_len);
    for (int i = 1; i < len; i++) {
        pss->set(pivot, arr + i * elem_len);
        int pos = upper(arr, elem_len, 0, i, pivot, pss->compare);
        for (int j = i; j > pos; j--) {
            int offset = j * elem_len;
            pss->set(arr + offset, arr + offset - elem_len);
        }
        pss->set(arr + pos * elem_len, pivot);
    }
    free(pivot);
}

int upper(const void *arr, size_t elem_len, int start, int end, const void *target,
          int(*compare)(const void *, const void *)) {
    int mid = calcMidIndex(start, end);
    while (start < end) {
        if (compare(arr + mid * elem_len, target) > 0) {
            end = mid;
        } else {
            start = mid + 1;
        }
        mid = calcMidIndex(start, end);
    }
    return mid;
}

int lower(const void *arr, size_t elem_len, int start, int end, const void *target,
          int(*compare)(const void *, const void *)) {
    int mid = calcMidIndex(start, end + 1);
    while (start < end) {
        if (compare(arr + mid * elem_len, target) >= 0) {
            end = mid - 1;
        } else {
            start = mid;
        }
        mid = calcMidIndex(start, end + 1);
    }
    return mid;
}

void select_sort(p_sort_struct pss) {
    size_t len = pss->arr_len;
    size_t elem_len = pss->arr_elem_len;
    void *arr = pss->arr;
    const void *min = (void *) malloc(elem_len);
    for (int i = 0; i < len; i++) {
        pss->set(min, arr + i * elem_len);
        int minIndex = i;
        for (int j = i + 1; j < len; j++) {
            int offset = j * elem_len;
            if (pss->compare(arr + offset, min) < 0) {
                pss->set(min, arr + offset);
                minIndex = j;
            }
        }
        pss->swap(arr + i * elem_len, arr + minIndex * elem_len);
    }
    free(min);
}

// 快速排序分区
int partition(p_sort_struct pss, int start, int end) {
    const void *arr = pss->arr;
    size_t elem_len = pss->arr_elem_len;
    srand(time(0));
    int len = end - start;
    int rand_index = rand() % len;
    int start_offset = start * elem_len, rand_offset = (start + rand_index) * elem_len;
    pss->swap(arr + start_offset, arr + rand_offset);
    const void *pivot = (void *) malloc(elem_len);
    pss->set(pivot, arr + start * elem_len);
    int pos = start;
    for (int i = start + 1; i <= end; i++) {
        size_t offset = i * elem_len;
        if (pss->compare(arr + offset, pivot) < 0) {
            pos++;
            pss->swap(arr + offset, arr + pos * elem_len);
        }
    }
    pss->swap(arr + pos * elem_len, arr + start * elem_len);
    free(pivot);
    return pos;
}

// 双路快速排序
int partition2way(p_sort_struct pss, int start, int end) {
    const void *arr = pss->arr;
    size_t elem_len = pss->arr_elem_len;
    srand(time(0));
    int len = end - start;
    int rand_index = rand() % len;
    int start_offset = start * elem_len, rand_offset = (start + rand_index) * elem_len;
    pss->swap(arr + start_offset, arr + rand_offset);

    const void *pivot = (void *) malloc(elem_len);
    pss->set(pivot, arr + start * elem_len);
    int i = start + 1, j = end;
    while (1) {
        while (i <= j && pss->compare(arr + i * elem_len, pivot) < 0) {
            i++;
        }
        while (j >= i && pss->compare(arr + j * elem_len, pivot) > 0) {
            j--;
        }

        if (i >= j) {
            break;
        }
        pss->swap(arr + i * elem_len, arr + j * elem_len);

        i++;
        j--;
    }
    pss->swap(arr + j * elem_len, arr + start * elem_len);
    free(pivot);
    return j;
}

// 快速排序
void quick_sort(p_sort_struct pss) {
    recursive_quick_sort(pss, 0, pss->arr_len - 1);
}

void recursive_quick_sort(p_sort_struct pss, int low, int high) {
    if (high - low <= 32) {
        insert_sort_by_step(pss, low, high, 1);
        return;
    }
    int index = partition2way(pss, low, high);
    recursive_quick_sort(pss, low, index - 1);
    recursive_quick_sort(pss, index + 1, high);
}

void merge_sort(p_sort_struct pss) {
    size_t arr_len = pss->arr_len, elem_len = pss->arr_elem_len;
    const void *extra = malloc(arr_len * elem_len);
    inner_merge_sort(pss, 0, pss->arr_len - 1, extra);
    free(extra);
}

void inner_merge_sort(p_sort_struct pss, int start, int end, const void *extra) {
    if (end - start <= 32) {
        insert_sort_by_step(pss, start, end, 1);
        return;
    }

    int mid = calcMidIndex(start, end);
    inner_merge_sort(pss, start, mid, extra);
    inner_merge_sort(pss, mid + 1, end, extra);
    size_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    int offset = mid * elem_len, next_offset = offset + elem_len;
    if (pss->compare(arr + offset, arr + next_offset) > 0) {
        merge(pss, start, mid, end, extra);
    }
}

// 合并有序数组
void merge(p_sort_struct pss, int low, int mid, int high, const void *extra) {
    // 左右下标起始位置
    int i = low, j = mid + 1, k = low;
    size_t elem_len = pss->arr_elem_len;
    const void *origin = pss->arr;
    while (i <= mid && j <= high) {
        int firstOffset = i * elem_len, second_offset = j * elem_len;
        if (pss->compare(origin + firstOffset, origin + second_offset) < 0) {
            pss->set(extra + k * elem_len, origin + firstOffset);
            i++;
        } else {
            pss->set(extra + k * elem_len, origin + second_offset);
            j++;
        }
        k++;
    }
    while (i <= mid) {
        pss->set(extra + k * elem_len, origin + i * elem_len);
        i++;
        k++;
    }
    while (j <= high) {
        pss->set(extra + k * elem_len, origin + j * elem_len);
        j++;
        k++;
    }
    // 归并后的数据copy回元数组
    k = low;
    while (low <= high) {
        pss->set(origin + low * elem_len, extra + k * elem_len);
        low++;
        k++;
    }
}

