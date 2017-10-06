#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

void grow(stack* s) {
    s->aloclen *= 2;
    s->elems = realloc(s->elems, s->aloclen);
    assert(s->elems != NULL);
}

void StackNew(stack* s, int elemSize, void(*freefn)(void*)) {
    assert(s != NULL);
    s->loglen = 0;
    s->aloclen = 4;
    s->elemSize = elemSize;
    s->elems = malloc(s->aloclen * s->elemSize);
    assert(s->elems != NULL);
    s->freefn = freefn;
}

void StackDispose(stack* s) {
    assert(s != NULL);
    if (s->freefn != NULL) {
        for (int i = 0; i < s->loglen; i++) {
            s->freefn((char*)s->elems + i * s->elemSize);
        }
        printf("yle xo araa\n");
    }
    free(s->elems);
}

void StackPush(stack* s, void* elemAddr) {
    assert(s != NULL);
    if (s->aloclen == s->loglen) {
        grow(s);
    }
    memcpy((char*) s->elems + s->loglen * s->elemSize, 
            elemAddr, s->elemSize);
    s->loglen++;
}

void StackPop(stack* s, void* elemAddr) {
    assert(s != NULL);
    assert(s->loglen > 0);
    s->loglen--;
    memcpy(elemAddr, (char*)s->elems + s->loglen * s->elemSize, s->elemSize);
}
