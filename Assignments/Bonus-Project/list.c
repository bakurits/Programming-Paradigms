//
// Created by bakurits on 12/26/17.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"


void init(list_t* self) {
    self->next = NULL;
}

void dispose(list_t* self) {
    if (self == NULL) return;

    switch (self->val.type){
        case String:
            free(self->val.val_ptr);
            break;
        case List:
            dispose(self->val.val_ptr);
            break;
    }
    dispose(self->next);
}

elem_t copy(elem_t elem) {
    elem_t result;
    result.type = elem.type;
    switch (elem.type){
        case String:
            elem.val_ptr = strcpy(result.val_ptr, elem.val_ptr);
            break;
        case List:
            break;

        case Integer:


            break;
    }
}


list_t list(elem_t elem) {
    list_t result;
    result.val = copy(elem);
    result.next = NULL;
    return result;
}

elem_t car(list_t* self) {
    assert(self != NULL);
    return self->val;
}

list_t cdr(list_t* self) {
    assert(self != NULL);
    return *self->next;
}

list_t cons(elem_t elem, list_t* second_list) {
    list_t res = list(elem);
    return append(&res, second_list);
}


list_t append(list_t* first_list, list_t* second_list) {
    if (first_list == NULL) return *second_list;
    if (second_list == NULL) return *first_list;

    list_t res;
    list_t* cur = first_list;
    while (1) {

    }

}

