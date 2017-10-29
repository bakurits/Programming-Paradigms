#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn) {
	assert(h != NULL);
	
	assert(elemSize > 0);
	assert(numBuckets > 0);
	
	assert(hashfn != NULL);
	assert(comparefn != NULL);

	h->elemCount = 0;
	h->elemSize = elemSize;
	h->numBuckets = numBuckets;
	h->hashfn = hashfn;
	h->comparefn = comparefn;
	h->freefn = freefn;

	h->elems = malloc(numBuckets * sizeof(vector));
	assert(h->elems != NULL);

	for (int i = 0; i < numBuckets; i++) {
		VectorNew(h->elems + i, elemSize, freefn, 0);
	}
}

void HashSetDispose(hashset *h) {
	assert(h != NULL);
	for (int i = 0; i < h->numBuckets; i++) {
		VectorDispose(h->elems + i);
	}
	free(h->elems);
}

int HashSetCount(const hashset *h) {
	assert(h != NULL);
	return h->elemCount;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void* auxData) {
	assert(h != NULL);
	assert(mapfn != NULL);
	for (int i = 0; i < h->numBuckets; i++) {
		VectorMap(h->elems + i, mapfn, auxData);
	}
}

void HashSetEnter(hashset *h, const void *elemAddr) {
	assert(h != NULL);
	assert(elemAddr != NULL);

	int hashOfElem = h->hashfn(elemAddr, h->numBuckets);
	assert(hashOfElem >= 0 && hashOfElem < h->numBuckets);

	int findIndex = VectorSearch(h->elems + hashOfElem, elemAddr, h->comparefn, 0, false);

	if (findIndex != -1) {
		VectorReplace(h->elems + hashOfElem, elemAddr, findIndex);
	} else {
		h->elemCount++;
		VectorAppend(h->elems + hashOfElem, elemAddr);
	}
}

void* HashSetLookup(const hashset *h, const void *elemAddr) {
	assert(h != NULL);
	assert(elemAddr != NULL);

	int hashOfElem = h->hashfn(elemAddr, h->numBuckets);
	assert(hashOfElem >= 0 && hashOfElem < h->numBuckets);

	int findIndex = VectorSearch(h->elems + hashOfElem, elemAddr, h->comparefn, 0, false);

	if (findIndex == -1){
		return NULL;
	} else {
		return VectorNth(h->elems + hashOfElem, findIndex);
	}
}
