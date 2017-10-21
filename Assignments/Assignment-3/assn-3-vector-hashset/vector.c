#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <search.h>

void VectorGrow(vector* v)
{
    v->aloclen *= 2;
    v->elems = realloc(v->elems, v->aloclen * v->elemSize);
    assert(v->elems != NULL);
}

static const int DEF_VEC_SIZE = 4;
void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
    assert(v != NULL);
    assert(initialAllocation >= 0);
    v->aloclen = initialAllocation == 0 ? DEF_VEC_SIZE : initialAllocation;
    v->elemSize = elemSize;
    v->freefn = freeFn;
    v->elems = malloc(v->aloclen * v->elemSize);
    assert(v->elems != NULL);
}

void VectorDispose(vector *v)
{
    assert(v != NULL);
    for (int i = 0; i < v->loglen; i++) {
        if (v->freefn != NULL)
            v->freefn((char*)v->elems + i * v->elemSize);
    }
    free(v->elems);
}

int VectorLength(const vector *v)
{
    assert(v != NULL);
    return v->loglen;
}

void* VectorNth(const vector* v, int position)
{
    assert(v != NULL);
    return (char*)v->elems + position * v->elemSize;
}

void VectorReplace(vector* v, const void* elemAddr, int position)
{
    assert(v != NULL);
    assert(position >= 0 && position < v->loglen);
    memcpy(VectorNth(v, position), elemAddr, v->elemSize);
}

void VectorInsert(vector* v, const void* elemAddr, int position)
{
    assert(v != NULL);
    assert(position >= 0 && position <= v->loglen);

    if (position == v->loglen)
    {
        VectorAppend(v, elemAddr);
        return;
    }
    
    if (v->aloclen == v->loglen)  VectorGrow(v);

    memmove(VectorNth(v, position + 1), VectorNth(v, position), (v->loglen - position) * v->elemSize);
    memcpy(VectorNth(v, position), elemAddr, v->elemSize);
    v->loglen++;
}

void VectorAppend(vector* v, const void *elemAddr)
{
    assert(v != NULL);
    if (v->aloclen == v->loglen)  VectorGrow(v);
    memcpy(VectorNth(v, v->loglen), elemAddr, v->elemSize);
    v->loglen++;
}

void VectorDelete(vector* v, int position)
{
    assert(v != NULL);
    assert(position >= 0 && position < v->loglen);
    
    if (v->freefn != NULL)  v->freefn(VectorNth(v, position));

    memmove(VectorNth(v, position + 1), VectorNth(v, position), (v->loglen - position) * v->elemSize);
    v->loglen--;
}

void VectorSort(vector* v, VectorCompareFunction compare)
{
    assert(v != NULL);
    assert(compare != NULL);
    qsort(v->elems, v->loglen, v->elemSize, compare);
}

void VectorMap(vector* v, VectorMapFunction mapFn, void* auxData)
{
    assert(v != NULL);
    assert(mapFn != NULL);
    for (int i = 0; i < v->loglen; i++) 
    {
        mapFn(VectorNth(v, i), auxData);
    }
}

static const int kNotFound = -1;
int VectorSearch(const vector* v, const void* key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{ 
    assert(v != NULL);
    assert(key != NULL);
    assert(searchFn != NULL);
    assert(startIndex >= 0 && startIndex < v->loglen);

    void* findedElem = NULL;

    if (isSorted) 
    {
        findedElem = bsearch(key, VectorNth(v, startIndex), 
                            v->loglen - startIndex - 1, v->elemSize, searchFn);
    }
    else
    {
        size_t nmemb = v->loglen - startIndex - 1;
        findedElem = lfind(key, VectorNth(v, startIndex), &nmemb, v->elemSize, searchFn);
    }

    return findedElem == NULL ? kNotFound : ((char*)findedElem - (char*)v->elems) / v->elemSize;
}
