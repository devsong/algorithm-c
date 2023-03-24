//
// Created by guanzhisong on 2023/3/27.
//

#include "test_sort.h"


int int_cmp(const void *first, const void *second) {
    return (*(int *) (first)) - ((*(int *) second));
}

void int_swap(const void *first, const void *second) {
    if (first == second) {
        return;
    }
    int tmp = *((int *) first);
    *((int *) first) = *((int *) second);
    *((int *) second) = tmp;
}

void int_set(const void *first, const void *second) {
    if (first == second) {
        return;
    }
    *((int *) first) = *((int *) second);
}


void sort_bench_mark(const char *sort_alg, p_sort_struct pss, void(*sort_func)(p_sort_struct)) {
    uint64_t arr_len = pss->arr_len;
    uint32_t elem_len = pss->arr_elem_len;
    void *cpy_arr = malloc(pss->arr_len * pss->arr_elem_len);
    const void *old_arr = pss->arr;
    memcpy(cpy_arr, pss->arr, arr_len * elem_len);
    if (arr_len <= 10) {
        printf("origin arr\n");
        print_arr(cpy_arr, arr_len);
    }
    pss->arr = cpy_arr;
    clock_t start = clock();
    sort_func(pss);
    clock_t stop = clock();
    int result = is_sorted(pss->arr, pss->arr_len, pss->arr_elem_len, pss->compare);
    printf("sort alg %s,len %jd cost time %f\n", sort_alg, arr_len, (double) (stop - start) / CLOCKS_PER_SEC);
    if (!result) {
        printf("sort_alg %s is not sorted\n", sort_alg);
    }
    if (arr_len <= 10) {
        printf("sorted arr\n");
        print_arr(cpy_arr, arr_len);
    }
    pss->arr = old_arr;
    free(cpy_arr);
}


void test_sort_benchmark(){
    int arr[] = {10, 100, 1000, 10000, 100000,1000000};

    sort_struct s;
    s.arr_elem_len = sizeof(int);
    s.compare = int_cmp;
    s.swap = int_swap;
    s.set = int_set;

    int arr_len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++) {
        int len = arr[i];
        void *ptr = calloc(len, sizeof(int));
        build_random_int_arr(ptr, len, 100);
        s.arr = ptr;
        s.arr_len = len;

        if (len <= 10000) {
            sort_bench_mark("bubble_sort", &s, bubble_sort);
            sort_bench_mark("select_sort", &s, select_sort);
            sort_bench_mark("insert_sort", &s, insert_sort);
            sort_bench_mark("binary_insert_sort", &s, binary_insert_sort);
        }
        sort_bench_mark("quick_sort", &s, quick_sort);
        sort_bench_mark("merge_sort", &s, merge_sort);
        free(ptr);
    }
}