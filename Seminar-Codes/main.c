#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

void StringFree(void* elem)
{
    char** curElem = (char**) elem;
    free(*curElem);
}

int main(int argc, char* argv[])
{
    const char* friends[] = {"Al", "Bob", "Curl"};
    stack s;

    StackNew(&s, sizeof(char*), StringFree);
    for (int i = 0; i < 3; i++) {
        char* copy = strdup(friends[i]);
        StackPush(&s, &copy);
    }
    
    char* name;
    StackPop(&s, &name);
    printf("%s\n", name);
    free(name);
    StackDispose(&s);
    return 0;
}
