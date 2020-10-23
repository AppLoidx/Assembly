// include guard here! 😎
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "linked_list.h"

linked_list *map(linked_list *list, int(f)(int));

void map_mut(linked_list *list, int(f)(int));

void foldl(linked_list *list, int *accumulator, int f(int, int));

linked_list *iterate(int s, size_t length, int f(int));

bool save(linked_list *list, const char *filename);

bool load(linked_list **list, const char *filename);

bool serialize(linked_list *list, const char *filename);

bool deserialize(linked_list **list, const char *filename);

void foreach (linked_list *list, void(f)(int));

#endif