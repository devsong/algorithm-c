//
// Created by guanzhisong on 2024/4/1.
//
#include "stdio.h"
#include "test_stack.h"

void test_stack() {
    int n = 5;
    for (int i = 0; i < n; i++) {
        push(i);
    }
    print_stack();
    for (int i = 0; i < n; i++) {
        printf("%d ", top());
        pop();
    }
}