#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list List;
typedef void       *ListItem;

/**
 * Initializes a List.
 *
 * Initializes the head of the List as NULL.
 *
 * @return NULL.
 */
List    *list_init();

/**
 * Returns the value of the List node.
 *
 *
 * @param l Pointer to the List.
 * @return Value of the node of the List.
 */
ListItem list_item(List *l);

/**
 * Returns the next node of the List.
 *
 *
 * @param l Pointer to the List.
 * @return Pointer to the next node of the List.
 */
List    *list_next(List *l);

/**
 * Pushes a value to the start of the List.
 *
 * Pushes a value to the start of the List.
 *
 * @param l Pointer to the List.
 * @param item Value to be pushed.
 * @return Pointer to the List.
 */
List    *list_push_front(List *l, ListItem item);

/**
 * Destroys the List.
 *
 * Destroys the List and deallocates the memory used by it.
 *
 * @param t Pointer to the List.
 */
void     list_destroy(List *l);

#endif