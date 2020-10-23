#include <stdio.h>
#include <errno.h>

#include "util.h"
#include "linked_list.h"

linked_list *read_list(int bufferSize)
{
    linked_list *list = 0;

    printf("Введите числа\n");
    char buf[bufferSize];

    int res = fgets(buf, bufferSize, stdin);
    printf("Input res : %d", res);
    int number = 0;
    int isNumberNotNull = 0;
    int sign = 1;

    for (int i = 0; i < bufferSize; i++)
    {
        if (buf[i] == 0)
        {
            break;
        }

        if (buf[i] == 32 || buf[i] == 10)
        {
            if (isNumberNotNull)
            {
                list_add_front(&list, sign * number);
                number = 0;
                isNumberNotNull = 0;
                sign = 1;
            }
        }
        else if (buf[i] == 45)
        {
            if (isNumberNotNull)
                continue;
            else
                sign = -1;
        }
        else
        {
            int val = buf[i] - '0';
            if (isNumberNotNull)
                number = number * 10 + val;
            else
                number = val;

            isNumberNotNull = 1;
        }
    }

    return list;
}

void print_list(linked_list *list)
{
    if (list == 0)
    {
        puts("Empty list");
        return;
    }
    puts("------------------------------");
    printf("List size is : %zu\n\n", list_length(list));

    for (int i = 0; i < list_length(list); i++)
    {
        printf("list[%d] = %d\n", i, list_get(list, i));
    }
    puts("\n");
}

void err_sys(const char *x)
{
    perror(x);
    exit(1);
}

void print_list_info(linked_list *list)
{
    puts("\n--[ List INFO ]--\n");

    size_t listLength = list_length(list);
    int getIndex = listLength > 3 ? listLength / 2 : 0;

    printf("list_get(%d) = %d\n", getIndex, list_get(list, getIndex));
    linked_list *node = list_node_at(list, getIndex);

    if (listLength > 1)
    {
        printf("list_node_at(%d) : %p (value: %d), next : %p (value: %d)",
               getIndex,
               node,
               node->value,
               node->next,
               node->next->value);
    }
    else
    {
        printf("list_node_at(%d) : %p (value: %d) , next : empty",
               getIndex,
               node,
               node->value);
    }
    puts("");
    printf("list_sum: %lld", list_sum(list));
}