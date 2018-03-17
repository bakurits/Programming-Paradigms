//
// Created by bakurits on 12/26/17.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

void list_init(list_t* self) {
    self->next = NULL;
}

void list_dispose(list_t* self) {
    if (self == NULL) return;

    switch (self->val.type){
        case String:
            free(self->val.val_ptr);
            break;
        case List:
            list_dispose(self->val.val_ptr);
            break;
    }
    list_dispose(self->next);
}

elem_t list_copy(elem_t elem) {
    elem_t result;
    result.type = elem.type;
    switch (elem.type){
        case String:
            result.type = String;
            result.val_ptr = strdup(elem.val_ptr);
            break;
        case List:
            if (elem.val_ptr == NULL) return elem;
            list_t* ls = elem.val_ptr;
            result.type = List;

            break;
        case Float:
            result.type = Float;
            result.val_ptr = malloc(sizeof(double));
            *(double*)result.val_ptr = *(double*)elem.val_ptr;
        case Integer:
            result.type = Integer;
            result.val_ptr = malloc(sizeof(int));
            *(int*)result.val_ptr = *(int*)elem.val_ptr;
            break;
    }
    return result;
}


list_t list_list(elem_t elem) {
    list_t result;
    result.val = list_copy(elem);
    result.next = NULL;
    return result;
}

elem_t list_car(list_t* self) {
    assert(self != NULL);
    return self->val;
}

list_t list_cdr(list_t* self) {
    assert(self != NULL);
    return *self->next;
}

list_t list_cons(elem_t elem, list_t* second_list) {
    list_t res = list_list(elem);
    return list_append(&res, second_list);
}


list_t list_append(list_t* first_list, list_t* second_list) {
    if (first_list == NULL) return *second_list;
    if (second_list == NULL) return *first_list;

    list_t res;
    list_t* cur = first_list;
    while (1) {

    }

}

