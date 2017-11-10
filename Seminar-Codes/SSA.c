#include "SSA.h"

void SSANew(sparsestringarray *ssa, int elemSize, int arrayLength, int groupSize, SSAFreeFunction freefn) {
    ssa->arrayLength = arrayLength;
    ssa->groupSize = groupSize;
    ssa->numGroups = arrayLength / groupSize;
    ssa->elemSize = elemSize;

    ssa->freefn = freefn;

    ssa->groups = malloc(ssa->numGroups * sizeof(group));
    
    for (int i = 0; i < ssa->numGroups; i++) {
        ssa->groups[i].bitmap = malloc(groupSize * sizeof(bool));
        VectorNew(&ssa->groups[i].strings, elemSize, NULL, 1);
    }
}

void* SSANth(sparsestringarray *ssa, int index) {
    assert (ssa != NULL);
    assert (index >= 0 && index < ssa->arrayLength);

    int groupIndex = index / ssa->groupSize;
    int bitmapIndex = index % ssa->groupSize;

    group* groupPtr = &(ssa->groups[groupIndex]);
    
    int vecIndex = 0;

    for (int i = 0; i < bitmapIndex; i++) {
        if (groupPtr->bitmap[i]) 
            vecIndex++;
    }

    if (groupPtr->bitmap[bitmapIndex]) {
        return VectorNth(&groupPtr->strings, vecIndex);
    } else {
        return NULL;
    }

}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str) {
    int groupIndex = index / ssa->groupSize;
    int bitmapIndex = index % ssa->groupSize;

    group* groupPtr = &(ssa->groups[groupIndex]);

    int vecIndex = 0;

    for (int i = 0; i < bitmapIndex; i++) {
        if (groupPtr->bitmap[i]) 
            vecIndex++;
    }
    
    

    if (groupPtr->bitmap[bitmapIndex]) {
        VectorReplace(&groupPtr->strings, str, vecIndex);
        return false;
    } else {
        VectorInsert(&groupPtr->strings, str, vecIndex);
        groupPtr->bitmap[bitmapIndex] = true;
        return true;
    }

}

void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData) {
    for (int i = 0; i < ssa->arrayLength; i++) {
        void* ptr = SSANth(ssa, i);
        if (ptr != NULL)
            mapfn(i, ptr, auxData);
        else 
            mapfn(i, "", auxData);
    }
}

void SSADispose(sparsestringarray *ssa) {
    for (int i = 0; i < ssa->numGroups; i++) {
        VectorDispose(&ssa->groups[i].strings);
        free (ssa->groups[i].bitmap);
    }
    free (ssa->groups);
}