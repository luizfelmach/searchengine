#include "list.h"

struct list {
    struct list *next;
    ListItem     item;
};

List *list_node(List *next, ListItem item) {
    List *l = malloc(sizeof(List));
    l->item = item;
    l->next = next;
    return l;
};

List *list_init() {
    return NULL;
}

ListItem list_item(List *l) {
    return l->item;
}

List *list_next(List *l) {
    return l->next;
}

List *list_push_front(List *l, ListItem item) {
    List *node = list_node(l, item);
    return node;
}

List *list_push_back(List *l, ListItem item) {
    List *new_node = list_node(NULL, item);
    
    if (l == NULL) {
        return new_node;
    }

    List *current = l;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;

    return l;
}

void list_destroy(List *l) {
    while (l != NULL) {
        List *next = l->next;
        free(l);
        l = next;
    }
}