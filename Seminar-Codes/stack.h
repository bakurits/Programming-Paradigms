#ifndef STACK_H_  
#define STACK_H_

typedef struct {
    void* elems;
    int elemSize;
    int loglen;
    int aloclen;
    void (*freefn)(void*);
} stack;

void StackNew(stack* s, int elemSize, void(*freefn)(void*));
void StackDispose(stack* s);
void StackPush(stack* s, void* elemAddr);
void StackPop(stack* s, void* elemAddr);

#endif