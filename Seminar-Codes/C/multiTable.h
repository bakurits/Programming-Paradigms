#ifndef __MULTISET_H__
#define __MULTISET_H__

typedef int (*MultiTableHashFunction)(const void *keyAddr, int numBuckets);

typedef int (*MultiTableCompareFunction)(const void *keyAddr1, const void *keyAddr2);

typedef void (*MultiTableMapFunction)(void *keyAddr, void *valueAddr, void *auxData);

typedef struct {
    hashset mappings;
    int keySize;
    int valueSize;
} multitable;

void MultiTableNew(multitable *mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, 
                    MultiTableHashFunction hash, MultiTableCompareFunction compare);

void MultiTableEnter(multitable *mt, const void *keyAddr, const void *valueAddr);

void MultiTableMap(multitable *mt, MultiTableMapFunction map, void *auxData);


#endif