#include "multiTable.h"

void MultiTableNew(multitable *mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, 
    MultiTableHashFunction hash, MultiTableCompareFunction compare) {
    
    mt->keySize = keySizeInBytes;
    mt->valueSize = valueSizeInBytes;
    mt->mappings = malloc(sizeof(hashset));
    hashsetNew(mt->mappings, sizeof(pair), )
}

void MultiTableEnter(multitable *mt, const void *keyAddr, const void *valueAddr) {

}

void MultiTableMap(multitable *mt, MultiTableMapFunction map, void *auxData) {

}