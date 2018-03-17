//
// Created by bakurits on 12/26/17.
//

#ifndef FIRSTPROJ_LIST_H
#define FIRSTPROJ_LIST_H



typedef enum {
    Integer, Float, String, List
}type_t;

typedef struct {
    void* val_ptr;
    type_t type;
}elem_t;


typedef struct list_t{
    struct list_t* next;
    elem_t val;
}list_t;

void list_init(list_t* self);
void list_dispose(list_t* self);

list_t list_list(elem_t elem);


elem_t list_car(list_t* self);
list_t list_cdr(list_t* self);

list_t list_cons(elem_t elem, list_t* second_list);
list_t list_append(list_t* first_list, list_t* second_list);

elem_t copy(elem_t elem);

elem_t list_copy(elem_t elem);


#endif //FIRSTPROJ_LIST_H
