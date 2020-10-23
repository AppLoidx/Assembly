#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include "linked_list.h"
#include "util.h"
#include "functions.h"

#define MAX_LINE 200

void static printWithSpace(int v);
void static printWithNewLine(int v);
int static mapSquare(int v);
int static mapCube(int v);
int static accumMapSum(int v, int accum);
int static accumFindMax(int v, int accum);
int static accumFindMin(int v, int accum);
int static mapAbs(int v);
int static mapMulTwo(int v);

int main()
{

    linked_list *list = read_list(MAX_LINE);

    print_list(list);

    puts("Add element 14 using list_add_back\n");
    list_add_back(&list, 14);

    print_list_info(list);

    puts("\n\n--[ Test higher order functions ]--");

    puts("\n [ Print with whitespace ]");
    foreach (list, printWithSpace)
        ;

    puts("\n\n [ Print with newline ]");
    foreach (list, printWithNewLine)
        ;

    puts("\n [ Map square ]");
    linked_list *newMapList = map(list, mapSquare);
    print_list(newMapList);
    list_free(newMapList);

    puts("\n [ Map cube ]");
    newMapList = map(list, mapCube);
    print_list(newMapList);
    list_free(newMapList);

    int accum;
    puts("\n [ foldl - SUM ]");
    accum = 0;
    foldl(list, &accum, accumMapSum);
    printf("Accumulator: %d", accum);

    puts("\n\n [ foldl - MAX ]");
    accum = INT_MIN;
    foldl(list, &accum, accumFindMax);
    printf("Accumulator: %d", accum);

    puts("\n\n [ foldl - MIN ]");
    accum = INT_MAX;
    foldl(list, &accum, accumFindMin);
    printf("Accumulator: %d", accum);

    puts("\n\n [ Mutate map with map_mut ]");
    map_mut(list, mapAbs);

    print_list(list);

    puts("\n\n [ Create list using iterate function ]");
    print_list(iterate(1, 10, mapMulTwo));

    puts("\n\n [ Write list to a file : output.txt ]");
    if (save(list, "output.txt"))
    {
        puts("Success!");
    }
    else
    {
        puts("Fail!");
    }

    puts("\n\n [ Load list from file : output.txt ]");

    linked_list *loadList = 0;
    if (load(&loadList, "output.txt"))
    {
        puts("Success!");
    }
    else
    {
        puts("Fail!");
    }

    list_free(loadList);

    puts("\n\n [ Serialize list to \"serialized.bin\" ]");

    if (serialize(list, "serialized.bin"))
    {
        puts("Successfuly serialized!");
    }
    else
    {
        puts("Failed to serialize!");
    }

    puts("\n\n [ Load list from serialized data ]");

    linked_list *deserialized_list = 0;
    if (deserialize(&deserialized_list, "serialized.bin"))
    {
        puts("Successfuly deserialized!");
    }
    else
    {
        puts("Failed to deserialize!");
    }

    list_free(deserialized_list);

    return 0;
}

void static printWithSpace(int v)
{
    printf("%d ", v);
}

void static printWithNewLine(int v)
{
    printf("%d\n", v);
}

int static mapSquare(int v)
{
    return v * v;
}

int static mapCube(int v)
{
    return v * v * v;
}

int static accumMapSum(int v, int accum)
{
    return accum + v;
}

int static accumFindMax(int v, int accum)
{
    if (v > accum)
    {
        return v;
    }
    else
    {
        return accum;
    }
}

int static accumFindMin(int v, int accum)
{
    if (v < accum)
    {
        return v;
    }
    else
    {
        return accum;
    }
}

int static mapAbs(int v)
{
    if (v < 0)
    {
        return -v;
    }
    else
    {
        return v;
    }
}

int static mapMulTwo(int v)
{
    return v * 2;
}
