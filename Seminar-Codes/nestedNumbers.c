#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    Integer, String, List, Nil
} nodeType;

char* stringConcat(const char* first, const char* second) {
    char* result = malloc(strlen(first) + strlen(second) + 1);
    strcpy(result, first);
    strcat(result, second);
    return result;
}

char* concatAll(nodeType* list) {
    switch(*list) {
        case Integer: return strdup("");
        case Nil: return strdup("");
        case String: return strdup((char*) (list + 1));
    }

    nodeType** lists = (nodeType**)(list + 1);
    char* front = concatAll(lists[0]);
    char* back = concatAll(lists[1]);
    free(front);
    free(back);
    char* result = stringConcatfront(front, back);
    return result;

}

int main() {

}