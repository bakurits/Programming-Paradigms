#ifndef MYCLIB_H_  
#define MYCLIB_H_


#include <stdio.h>
#include <string.h>

/*
 *
 */
void swap(void* a, void* b, int bitCount);

/*
 *
 */
void mySelectionSort(void* a, int n, size_t bitCount, int(*compare)(const void*, const void*));

/*
 *
 */
void* lnSearch(const void* collection, const void* key,
                int len, int memSize, 
                int(*compare)(const void*, const void*));



#endif