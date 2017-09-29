#include <stdio.h>
#include <string.h>

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

int compare(int* first, int* second) {
    return strncmp((char*) first, (char*) second, sizeof(int));
}

int main() {
    int a[5] = {3, 5, 2, 1, 0};
    int key = 4;

    int* res = lnSearch(a, &key, 5, sizeof(int), (int (*)(const void *, const void *)) compare);

    if (res == NULL) {
        printf("Can't Find\n");
    } else {
        printf("%d\n", *res);
    }
    
}
