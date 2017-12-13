#include "myclib.h"

int compare(void* a, void* b) {
    char* first = *(char**) a;
    char* second = *(char**) b;

    for (int i = 0; ; i++) {
        char* curFirst = first + i;
        char* curSecond = second + i;
        if ((*curFirst) < (*curSecond)) return -1;
        if ((*curFirst) > (*curSecond)) return 1;
        if ((*curFirst) == 0) return 0;
        if ((*curSecond) == 0) return 0;
    }
    return 0;
}


int main() {
    char* s[] = {"Curl", "Alb", "Al"};

    mySelectionSort(s, sizeof(s) / sizeof(char*), sizeof(char*), (int (*)(const void *, const void *)) compare);

    for (int i = 0; i < sizeof(s) / sizeof(char*); i++) {
        printf("%s ", s[i]);
    }
    printf("\n");
}