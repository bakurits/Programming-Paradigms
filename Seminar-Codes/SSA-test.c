#include <stdio.h>
#include <string.h>
#include "SSA.h"

static void CountEmptyPrintNonEmpty(int index, const char *str, void *auxData) {
    if (strcmp(str, "") != 0) {
        printf("Oooo! Nonempty string at index %d: \"%s\"\n", index, str);
    } else {
        (*(int *)auxData)++;
    }
}

void freeString(void* ptr) {
    free ((char*)ptr);
}

int main(int argc, char **argv) {
    sparsestringarray ssa;
    char* st1 = strdup("need");
    char* st2 = strdup("moriiiiiiiiiiiiiiiiiiiiiiie");
    char* st3 = strdup("Eye");
    char* st4 = strdup("I");
    char* st5 = strdup("cowbell");
    SSANew(&ssa, sizeof(char*), 70000, 35, freeString);
    
    SSAInsert(&ssa, 33001, st1);
    SSAInsert(&ssa, 58291, st2);
    SSAInsert(&ssa, 33000, st3);    
    SSAInsert(&ssa, 33000, st4);
    SSAInsert(&ssa, 67899, st5);
    

    int numEmptyStrings = 0;
    SSAMap(&ssa, CountEmptyPrintNonEmpty, &numEmptyStrings);
    printf("%d of the strings were empty strings.\n", numEmptyStrings);
    SSADispose(&ssa);
    free (st1);
    free (st2);
    free (st3);
    free (st4);
    free (st5);
    return 0;
}
