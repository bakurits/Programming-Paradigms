#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <search.h>

void VectorGrow(vector* v) {
    v->aloclen = v->aloclen << 1;
    v->elems = realloc(v->elems, v->aloclen * v->elemSize);
    assert(v->elems != NULL);
}

void VectorDecay(vector* v) {
    v->aloclen = v->aloclen >> 1;
    v->elems = realloc(v->elems, v->aloclen * v->elemSize);
    assert(v->elems != NULL);
}

static const int DEF_VEC_SIZE = 4;
void VectorNew(vector* v, int elemSize, VectorFreeFunction freeFn, int initialAllocation) {
    assert(v != NULL);
    assert(initialAllocation >= 0);
    assert(elemSize > 0);
    
    v->aloclen = (initialAllocation == 0) ? DEF_VEC_SIZE : initialAllocation;
    v->loglen = 0;
    v->elemSize = elemSize;
    v->freefn = freeFn;
    v->elems = malloc(v->aloclen * v->elemSize);
    assert(v->elems != NULL);
}

void VectorDispose(vector *v) {
    assert(v != NULL);
    if (v->freefn != NULL) {
        for (int i = 0; i < v->loglen; i++) {
            v->freefn(VectorNth(v, i));
        }
    }
    free(v->elems);
}

int VectorLength(const vector *v) {
    assert(v != NULL);
    return v->loglen;
}

void* VectorNth(const vector* v, int position) {
    assert(v != NULL);
    assert(position >= 0 && position < v->loglen);
    return (char*)v->elems + position * v->elemSize;
}

void VectorReplace(vector* v, const void* elemAddr, int position) {
    assert(v != NULL);
    assert(position >= 0 && position < v->loglen);

    if (v->freefn != NULL) v->freefn(VectorNth(v, position));
    
    memcpy(VectorNth(v, position), elemAddr, v->elemSize);
}

void VectorInsert(vector* v, const void* elemAddr, int position) {
    assert(v != NULL);
    assert(position >= 0 && position <= v->loglen);
    assert(elemAddr != NULL);

    if (position == v->loglen) {
        VectorAppend(v, elemAddr);
    } else {
        if (v->aloclen == v->loglen)  VectorGrow(v);
        v->loglen++;
        memmove(VectorNth(v, position + 1), VectorNth(v, position), (v->loglen - position - 1) * v->elemSize);
        memcpy(VectorNth(v, position), elemAddr, v->elemSize);
    }
}

void VectorAppend(vector* v, const void *elemAddr) {
    assert(v != NULL);
    assert(elemAddr != NULL);

    if (v->aloclen == v->loglen)  VectorGrow(v);
    
    v->loglen++;
    memcpy(VectorNth(v, v->loglen - 1), elemAddr, v->elemSize);
}

void VectorDelete(vector* v, int position) {
    assert(v != NULL);
    assert(position >= 0 && position < v->loglen);
    
    if (v->freefn != NULL)  v->freefn(VectorNth(v, position));

    if (position < v->loglen - 1)
        memmove(VectorNth(v, position), VectorNth(v, position + 1), (v->loglen - position - 1) * v->elemSize);
    v->loglen--;
    
    if (v->loglen < v->aloclen / 4 && v->aloclen != DEF_VEC_SIZE)
        VectorDecay(v); 
}

void VectorSort(vector* v, VectorCompareFunction compare) {
    assert(v != NULL);
    assert(compare != NULL);
    qsort(v->elems, v->loglen, v->elemSize, compare);
}

void VectorMap(vector* v, VectorMapFunction mapFn, void* auxData) {
    assert(v != NULL);
    assert(mapFn != NULL);
    for (int i = 0; i < v->loglen; i++) {
        mapFn(VectorNth(v, i), auxData);
    }
}

static const int kNotFound = -1;
int VectorSearch(const vector* v, const void* key, VectorCompareFunction searchFn, int startIndex, char isSorted) { 
    assert(v != NULL);
    assert(key != NULL);
    assert(searchFn != NULL);
    assert(startIndex >= 0 && startIndex <= v->loglen);
    
    if (startIndex == v->loglen) return -1;

    void* findedElem = NULL;
    size_t nmemb = v->loglen - startIndex;

    if (isSorted) {
        findedElem = bsearch(key, VectorNth(v, startIndex), nmemb, v->elemSize, searchFn);
    } else {
        findedElem = lfind(key, VectorNth(v, startIndex), &nmemb, v->elemSize, searchFn);
    }
    
    return (findedElem == NULL) ? kNotFound : ((char*)findedElem - (char*)v->elems) / v->elemSize;
}
