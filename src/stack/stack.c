//
// Created by guanzhisong on 2024/4/1.
//
#include <stdio.h>
#include <assert.h>
#include "stack.h"

#define STACK_SIZE 100

static stack_type stack[STACK_SIZE];
static int top_element = -1;

void push(stack_type e) {
    assert(!is_full());
    top_element++;
    stack[top_element] = e;
}

stack_type pop(void) {
    assert(!is_empty());
    stack_type e = stack[top_element];
    top_element--;
    return e;
}

stack_type top(void) {
    assert(!is_empty());
    return stack[top_element];
}

int is_full() {
    return top_element >= STACK_SIZE ? 1 : 0;
}

int is_empty() {
    return top_element == -1 ? 1 : 0;
}

void print_stack() {
    for (int i = 0; i <= top_element; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}


