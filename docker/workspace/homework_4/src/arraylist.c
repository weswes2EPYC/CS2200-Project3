/**
 * Name: Wesley Hu
 * GTID: 903872846
 */

/*  PART 2: A CS-2200 C implementation of the arraylist data structure.
    Implement an array list.
    The methods that are required are all described in the header file.
    Description for the methods can be found there.

    Hint 1: Review documentation/ man page for malloc, calloc, and realloc.
    Hint 2: Review how an arraylist works.
    Hint 3: You can use GDB if your implentation causes segmentation faults.
    Hint 4: Remember to check if memory allocations succeed.

    You will submit this file to gradescope.
*/

#include "arraylist.h"

/* Student code goes below this point */
arraylist_t *create_arraylist(uint capacity)
{
    if (capacity <= 0)
    {
        return NULL;
    }

    arraylist_t *arraylist_pointer = (arraylist_t *)malloc(sizeof(arraylist_t));
    if (!arraylist_pointer)
    {
        return NULL;
    }

    arraylist_pointer->backing_array = (char **)malloc(capacity * sizeof(char *));
    if (!arraylist_pointer->backing_array)
    {
        free(arraylist_pointer);
        return NULL;
    }

    arraylist_pointer->size = 0;
    arraylist_pointer->capacity = capacity;
    return arraylist_pointer;
}

void add_at_index(arraylist_t *arraylist, char *word, int index)
{
    if (index < 0 || index > arraylist->size)
    {
        return;
    }

    if (arraylist->size >= arraylist->capacity)
    {
        resize(arraylist);
    }

    for (int i = arraylist->size; i > index; i--)
    {
        arraylist->backing_array[i] = arraylist->backing_array[i - 1];
    }

    arraylist->backing_array[index] = word;
    arraylist->size++;
}

void append(arraylist_t *arraylist, char *data)
{
    add_at_index(arraylist, data, arraylist->size);
}

char *remove_from_index(arraylist_t *arraylist, int index)
{
    if (index < 0 || index >= arraylist->size)
    {
        return NULL;
    }

    char *removed = arraylist->backing_array[index];
    for (int i = index; i < arraylist->size - 1; i++)
    {
        arraylist->backing_array[i] = arraylist->backing_array[i + 1];
    }
    arraylist->backing_array[arraylist->size - 1] = NULL;
    arraylist->size--;
    return removed;
}

void resize(arraylist_t *arraylist)
{
    uint new_capacity = arraylist->capacity * 2;
    char **new_array = (char **)realloc(arraylist->backing_array, new_capacity * sizeof(char *));

    if (!new_array)
    {
        return;
    }

    arraylist->backing_array = new_array;
    arraylist->capacity = new_capacity;
}

void destroy(arraylist_t *arraylist)
{
    if (!arraylist)
    {
        return;
    }
    // for(int i = 0; i < arraylist->capacity; i++) {
    //     free(arraylist->backing_array[i]);
    // }
    free(arraylist->backing_array);
    free(arraylist);
}