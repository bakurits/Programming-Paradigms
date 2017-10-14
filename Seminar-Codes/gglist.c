#include "gglist.h";

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
    if (index > l->logLen) index = l->logLen;
    
    if (l->allocLen == l->logLen) ListGrow(List* l);

    elem* src = l->elems_array + index;
    memmove(src + 1, src, sizeof(src) * (l->logLen - index));
    src->size = elemSize;
    src->data = malloc(elemSize)
    memcpy(src->data, elemadr, elemSize);
    l->elemSize++;
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


void ListGet