#ifdef __GGLIST__
#define __GGLIST__

typedef struct elem {
    void* data;
    int size;
} elem;

typedef struct List {
    int logLen;
    int allocLen;
    elem* elems_array;
};

void ListNew(List* l);
void ListInsert(List* l, int index, void* elemadr, int elemSize);
void ListAppend(List* l, void* elemAdr, int elemSize);
void ListDispose(List* l);




#endif