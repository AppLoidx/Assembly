// include guard here! 😎
#ifndef UTIL_H
#define UTIL_H

#include "linked_list.h"

linked_list *read_list(int bufferSize);

void print_list(linked_list *list);

void err_sys(const char *x);

void print_list_info(linked_list *list);

#endif