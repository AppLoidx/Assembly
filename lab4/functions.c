#include "functions.h"
#include <stdio.h>
#include <errno.h>

// executes f(int) for each list element
void foreach (linked_list *list, void(f)(int))
{
    linked_list *current = list;
    f(current->value);
    while (current->next != 0)
    {
        current = current->next;
        f(current->value);
    }
}

// maps f(int) for each list element
linked_list *map(linked_list *list, int(f)(int))
{
    linked_list *current = list;
    linked_list *result = list_create(f(current->value));
    while (current->next != 0)
    {
        current = current->next;
        list_add_back(&result, f(current->value));
    }
    return result;
}

// mutates original list with f(int) function
void map_mut(linked_list *list, int(f)(int))
{
    linked_list *current = list;
    current->value = f(current->value);
    while (current->next != 0)
    {
        current = current->next;
        current->value = f(current->value);
    }
}

// have side effect on accum
void foldl(linked_list *list, int *accum, int f(int, int))
{
    linked_list *current = list;
    *accum = f(current->value, *accum);
    while (current->next != 0)
    {
        current = current->next;
        *accum = f(current->value, *accum);
    }
}

linked_list *iterate(int s, size_t length, int f(int))
{
    linked_list *result = list_create(s);
    int value = s;
    for (size_t i = 1; i < length; i++)
    {
        value = f(value);
        list_add_back(&result, value);
    }
    return result;
}

bool save(linked_list *list, const char *filename)
{
    errno = 0;
    FILE *file = fopen(filename, "w");

    if (errno || ferror(file))
    {
        return false;
    }

    linked_list *current = list;
    fprintf(file, "%d", current->value);

    if (errno || ferror(file))
    {
        return false;
    }

    while (current->next != 0)
    {
        current = current->next;
        fprintf(file, " %d", current->value);
        if (errno || ferror(file))
        {
            return false;
        }
    }

    fflush(file);
    fclose(file);

    if (errno || ferror(file))
    {
        return false;
    }
    return true;
}

bool load(linked_list **list, const char *filename)
{
    errno = 0;
    FILE *file = fopen(filename, "r");
    if (errno || ferror(file))
    {
        return false;
    }
    int input;
    fscanf(file, "%d", &input);

    if (errno || ferror(file))
    {
        return false;
    }

    *list = list_create(input);
    while (fscanf(file, "%d", &input) != EOF)
    {
        if (errno || ferror(file))
        {
            return false;
        }
        list_add_back(list, input);
    }
    fclose(file);

    if (errno || ferror(file))
    {
        return false;
    }

    return true;
}

bool serialize(linked_list *list, const char *filename)
{
    errno = 0;
    linked_list *current = list;
    FILE *file = fopen(filename, "wb");

    if (errno || ferror(file))
    {
        return false;
    }

    fwrite(&current->value, sizeof(int), 1, file);

    while (current->next != 0)
    {
        current = current->next;
        fwrite(&current->value, sizeof(int), 1, file);
        if (errno || ferror(file))
            return false;
    }

    fflush(file);
    fclose(file);

    if (errno || ferror(file))
    {
        return false;
    }

    return true;
}

bool deserialize(linked_list **list, const char *filename)
{
    errno = 0;
    FILE *file = fopen(filename, "rb");

    if (errno || ferror(file))
    {
        return false;
    }

    if (*list != 0)
    {
        list_free(*list);
    }

    int input;

    fread(&input, sizeof(int), 1, file);

    if (errno || ferror(file))
    {
        return false;
    }
    *list = list_create(input);

    while (fread(&input, sizeof(int), 1, file) == 1)
    {
        if (errno || ferror(file))
        {
            return false;
        }

        list_add_back(list, input);
    }

    fclose(file);

    if (errno || ferror(file))
    {
        return false;
    }

    return true;
}