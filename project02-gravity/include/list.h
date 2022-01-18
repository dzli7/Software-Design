#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
#include "free_func.h"

/**
 * A growable array of vectors, stored as pointers to malloc()ed vectors.
 * A list owns all the vectors in it, so it is responsible for free()ing them.
 * This line does two things:
 * - Declares a "struct vec_list" type
 * - Makes "vec_list_t" an alias for "struct vec_list"
 *
 * You will need to implement this struct type in vec_list.c.
 */
typedef struct list list_t;

/**
 * Allocates memory for a new list with space for the given number of elements.
 * The list is initially empty.
 * Asserts that the required memory was allocated.
 *
 * @param initial_size the number of list elements to allocate space for
 * @return a pointer to the newly allocated list
 */
list_t *list_init(size_t initial_size, free_func_t free_func);

/**
 * Releases the memory allocated for a list.
 * Also frees all vectors in the list.
 *
 * @param list a pointer to a list returned from vec_list_init()
 */
void list_free(list_t *list);

/**
 * Gets the size of a list (the number of occupied elements).
 * Note that this is NOT the list's capacity.
 *
 * @param list a pointer to a list returned from vec_list_init()
 * @return the number of vectors in the list
 */
size_t list_size(list_t *list);

/**
 * Gets the element at a given index in a list.
 * Asserts that the index is valid, given the list's current size.
 *
 * @param list a pointer to a list returned from vec_list_init()
 * @param index an index in the list (the first element is at 0)
 * @return the vector at the given index
 */
void *list_get(list_t *list, size_t index);

/**
 * Appends an element to the end of a list.
 * Asserts that the list has has remaining space,
 * and that the value being added is not NULL.
 *
 * @param list a pointer to a list returned from vec_list_init()
 * @param value the vector to add to the end of the list
 */
void list_add(list_t *list, void *value);

/**
 * Removes the element at the end of a list and returns it.
 * Asserts that the list is nonempty.
 *
 * @param list a pointer to a list returned from vec_list_init()
 * @return the vector at the end of the list
 */
void *list_remove(list_t *list);

void *list_remove_front(list_t *list);

// free_func_t get_free_func(list_t *list);

#endif // #ifndef __LIST_H__
