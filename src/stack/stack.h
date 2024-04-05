//
// Created by guanzhisong on 2023/3/23.
//

#ifndef ALGORITHM_C_STACK_H
#define ALGORITHM_C_STACK_H

typedef int stack_type;

void push(stack_type e);

stack_type pop(void);

stack_type top(void);

int is_empty(void);

int is_full(void);

void print_stack(void);

#endif //ALGORITHM_C_STACK_H
