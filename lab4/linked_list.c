#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "linked_list.h"

linked_list *list_create(int number)
{
    linked_list *new_list = (linked_list *)malloc(sizeof(linked_list));
    new_list->value = number;
    new_list->next = 0;
    return new_list;
}

linked_list *list_add_front(linked_list **list, int number)
{
    linked_list *new_head = list_create(number);
    new_head->next = *list;
    *list = new_head;
    return new_head;
}

linked_list *list_add_back(linked_list **list, int number)
{
    if (*list == 0)
    {
        return list_add_front(list, number);
    }

    linked_list *current = *list;
    while (current->next != 0)
    {
        current = current->next;
    }
    linked_list *new_element = list_create(number);
    current->next = new_element;
    return new_element;
}

int list_get(linked_list *list, size_t id)
{
    linked_list *current = list;
    size_t counter;
    for (counter = 0; counter < id; counter++)
    {
        if (current->next != 0)
        {
            current = current->next;
        }
        else
        {
            break;
        }
    }
    if (counter == id)
    {
        return current->value;
    }
    else
    {
        return 0;
    }
}

void list_free(linked_list *list)
{
    linked_list *current = list;
    while (current->next != 0)
    {
        linked_list *next = current->next;
        free(current);
        current = next;
    }
    free(current);
}

size_t list_length(linked_list *list)
{
    linked_list *current = list;
    size_t counter = 1;
    while (current->next != 0)
    {
        counter++;
        current = current->next;
    }
    return counter;
}

linked_list *list_node_at(linked_list *list, size_t id)
{
    linked_list *current = list;
    size_t counter;
    for (counter = 0; counter < id; counter++)
    {
        if (current->next != 0)
        {
            current = current->next;
        }
        else
        {
            break;
        }
    }
    if (counter == id)
    {
        return current;
    }
    else
    {
        return NULL;
    }
}

long long list_sum(linked_list *list)
{
    linked_list *current = list;
    long long sum = current->value;
    while (current->next != 0)
    {
        current = current->next;
        sum += current->value;
    }
    return sum;
}
