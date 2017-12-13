#include "gglist.h"
#include <assert.h>

void ListNew(List* l) {
    l->logLen = 0;
    l->allocLen = 4;
    l->elems_array = malloc(l->allocLen * sizeof(elem));
}

void ListGrow(List* l) {
    l->allocLen *= 2;
    l->elems_array = realloc(l->elems_array, sizeof(elem) * l->allocLen);
}

void ListInsert(List* l, int index, void* elemAdr, int elemSize) {
    assert(index >= 0);

    if (index > l->logLen) index = l->logLen;
    
    if (l->allocLen == l->logLen) ListGrow(l);

    elem* src = l->elems_array + index;
    memmove(src + 1, src, sizeof(elem) * (l->logLen - index));
    src->size = elemSize;
    src->data = malloc(elemSize);
    memcpy(src->data, elemAdr, elemSize);
    l->logLen++;
}

void ListRemove(List* l, int index) {
    assert(index >=0 && index < l->logLen);
    memmove(l->elems_array + index + 1, l->elems_array + index + 1, (l->logLen - index) * sizeof(elem));
}

void ListAppend(List* l, void* elemAdr, int elemSize) {
    ListInsert(l, l->logLen, elemAdr, elemSize);
}

void ListDispose(List* l) {
    for (int i = 0; i < l->logLen; i++) {
        free((l->elems_array + i)->data);
    }
    free(l->elems_array);
}

void ListGet(List* l, int index, void *elemAdr) {
    assert(index >=0 && index < l->logLen);
    memcpy(elemAdr, l->elems_array + index, sizeof(elem));
}