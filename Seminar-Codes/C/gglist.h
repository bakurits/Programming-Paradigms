#ifndef __GGLIST__
#define __GGLIST__

#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;
    int size;
} elem;

typedef struct {
    int logLen;
    int allocLen;
    elem* elems_array;
} List;

void ListNew(List* l);
void ListInsert(List* l, int index, void* elemadr, int elemSize);
void ListRemove(List* l, int index);
void ListAppend(List* l, void* elemAdr, int elemSize);
void ListDispose(List* l);
void ListGet(List* l, int index, void *elemAdr);

#endif