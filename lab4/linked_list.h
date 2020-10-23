// include guard here! 😎
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct linked_list linked_list;

// pretty easy, ya?
struct linked_list
{
    int value;
    linked_list *next;
};

linked_list *list_create(int number);

linked_list *list_add_front(linked_list **list, int number);

linked_list *list_add_back(linked_list **list, int number);

linked_list *list_node_at(linked_list *list, size_t id);

linked_list *list_copy(linked_list *list);

int list_get(linked_list *list, size_t id);

void list_free(linked_list *list);

size_t list_length(linked_list *list);

long long list_sum(linked_list *list);

bool list_equals(linked_list *first, linked_list *second);

#endif