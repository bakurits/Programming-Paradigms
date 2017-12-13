#include "myclib.h"

void* lnSearch(const void* collection, const void* key,
                int len, int memSize, 
                int(*compare)(const void*, const void*)) {

    for (int i = 0; i < len; i++) {
        void* curInCol = (char*) collection + i * memSize;
        if (compare(curInCol, key) == 0)
            return curInCol;
    }
    return NULL;
}

void swap(void* a, void* b, int bitCount){
	char tmp[bitCount];
	memcpy(tmp, a, bitCount);
	memcpy(a, b, bitCount);
	memcpy(b, tmp, bitCount);
}

void mySelectionSort(void* a, int n, size_t bitCount, int(*compare)(const void*, const void*)) {
    for (int i = 0; i < n - 1; i++) {
        int iMin = i;
        for (int j = i + 1; j < n; j++) {
            if (compare((char*) a + iMin * bitCount, (char*) a + j * bitCount) > 0) {
                iMin = j;
            }
        }
        if (iMin != i) {
            swap((char*) a + i * bitCount, (char*) a + iMin * bitCount, bitCount);
        }
    }
}