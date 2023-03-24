//
// Created by guanzhisong on 2023/3/22.
//
#include <stdlib.h>
#include <time.h>
#include "sort.h"

void recursive_quick_sort(p_sort_struct pss, uint64_t low, uint64_t high);

__attribute__((unused)) uint64_t partition(p_sort_struct pss, int start, int end);

void inner_merge_sort(p_sort_struct pss, uint64_t start, uint64_t end, const void *extra);

void merge(p_sort_struct pss, uint64_t low, uint64_t mid, uint64_t high, const void *extra);

uint64_t upper(const void *arr, size_t elem_len, uint64_t start, uint64_t end, const void *target,
               int (*compare)(const void *, const void *));

uint64_t calcMidIndex(uint64_t low, uint64_t high) {
    return low + ((high - low) >> 1);
}

void bubble_sort(p_sort_struct s) {
    uint64_t arr_len = s->arr_len;
    uint32_t elem_len = s->arr_elem_len;
    const void *arr = s->arr;
    for (uint64_t i = 0; i < arr_len; i++) {
        uint64_t swap_cnt = 0;
        for (uint64_t j = 0; j < arr_len - 1 - i; j++) {
            uint64_t offset = j * elem_len, offset_next = offset + elem_len;
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

void insert_sort_by_step(p_sort_struct pss, uint64_t start, uint64_t end, uint32_t step) {
    uint64_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    void *pivot = (void *) malloc(elem_len);
    for (uint64_t i = start; i <= end; i += step) {
        pss->set(pivot, arr + i * elem_len);
        uint64_t j = i;
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
    uint64_t len = pss->arr_len;
    uint64_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    void *pivot = (void *) malloc(elem_len);
    for (uint64_t i = 1; i < len; i++) {
        pss->set(pivot, arr + i * elem_len);
        uint64_t pos = upper(arr, elem_len, 0, i, pivot, pss->compare);
        for (uint64_t j = i; j > pos; j--) {
            uint64_t offset = j * elem_len;
            pss->set(arr + offset, arr + offset - elem_len);
        }
        pss->set(arr + pos * elem_len, pivot);
    }
    free(pivot);
}

uint64_t upper(const void *arr, size_t elem_len, uint64_t start, uint64_t end, const void *target,
               int(*compare)(const void *, const void *)) {
    uint64_t mid = calcMidIndex(start, end);
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

__attribute__((unused)) uint64_t lower(const void *arr, size_t elem_len, uint64_t start, uint64_t end, const void *target,
                                  int(*compare)(const void *, const void *)) {
    uint64_t mid = calcMidIndex(start, end + 1);
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
    uint64_t len = pss->arr_len;
    uint32_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    void *min = (void *) malloc(elem_len);
    for (uint64_t i = 0; i < len; i++) {
        pss->set(min, arr + i * elem_len);
        uint64_t minIndex = i;
        for (uint64_t j = i + 1; j < len; j++) {
            uint64_t offset = j * elem_len;
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
__attribute__((unused)) uint64_t partition(p_sort_struct pss, int start, int end) {
    const void *arr = pss->arr;
    size_t elem_len = pss->arr_elem_len;
    srand(time(NULL));
    uint64_t len = end - start;
    uint64_t rand_index = abs(rand()) % len;
    uint64_t start_offset = start * elem_len, rand_offset = (start + rand_index) * elem_len;
    pss->swap(arr + start_offset, arr + rand_offset);
    void *pivot = (void *) malloc(elem_len);
    pss->set(pivot, arr + start * elem_len);
    uint64_t pos = start;
    for (uint64_t i = start + 1; i <= end; i++) {
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
uint64_t partition2way(p_sort_struct pss, uint64_t start, uint64_t end) {
    const void *arr = pss->arr;
    size_t elem_len = pss->arr_elem_len;
    srand(time(NULL));
    uint64_t len = end - start;
    uint64_t rand_index = abs(rand()) % len;
    uint64_t start_offset = start * elem_len, rand_offset = (start + rand_index) * elem_len;
    pss->swap(arr + start_offset, arr + rand_offset);

    void *pivot = (void *) malloc(elem_len);
    pss->set(pivot, arr + start * elem_len);
    uint64_t i = start + 1, j = end;
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

void recursive_quick_sort(p_sort_struct pss, uint64_t low, uint64_t high) {
    if (high - low <= MIN_INSERT_LEN) {
        insert_sort_by_step(pss, low, high, 1);
        return;
    }
    uint64_t index = partition2way(pss, low, high);
    recursive_quick_sort(pss, low, index - 1);
    recursive_quick_sort(pss, index + 1, high);
}

void merge_sort(p_sort_struct pss) {
    size_t arr_len = pss->arr_len, elem_len = pss->arr_elem_len;
    void *extra = malloc(arr_len * elem_len);
    inner_merge_sort(pss, 0, pss->arr_len - 1, extra);
    free(extra);
}

void inner_merge_sort(p_sort_struct pss, uint64_t start, uint64_t end, const void *extra) {
    if (end - start <= MIN_INSERT_LEN) {
        insert_sort_by_step(pss, start, end, 1);
        return;
    }

    uint64_t mid = calcMidIndex(start, end);
    inner_merge_sort(pss, start, mid, extra);
    inner_merge_sort(pss, mid + 1, end, extra);
    uint32_t elem_len = pss->arr_elem_len;
    const void *arr = pss->arr;
    uint64_t offset = mid * elem_len, next_offset = offset + elem_len;
    if (pss->compare(arr + offset, arr + next_offset) > 0) {
        merge(pss, start, mid, end, extra);
    }
}

// 合并有序数组
void merge(p_sort_struct pss, uint64_t low, uint64_t mid, uint64_t high, const void *extra) {
    // 左右下标起始位置
    uint64_t i = low, j = mid + 1, k = low;
    uint32_t elem_len = pss->arr_elem_len;
    const void *origin = pss->arr;
    while (i <= mid && j <= high) {
        uint64_t firstOffset = i * elem_len, second_offset = j * elem_len;
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

