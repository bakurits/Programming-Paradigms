#include <stdio.h>
#include <string.h>

void floatToText(void* curFloat) {
    char* res = strdup("0000000000000000000000000");
    int a = *(int*) curFloat;
    int curInd = 0;
    if (a < 0) {
        printf("-");
    }
    printf("1.");
    for (int i = 22; i >= 0; i--) {
        if ((1 << i & a) > 0) {
            printf("1");
        } else {
            printf ("0");
        }
    }
    char b = (a >> 23);
    //printf("\n%d  asdasd\n", b);
    b  = 127 - b;
    printf(" * 2^%d\n", b);

    // for (int i = 7; i >= 0; i--) {
    //     if ((1 << i & b) > 0) {
    //         printf("1");
    //     } else {
    //         printf ("0");
    //     }
    // }
    
    // puts("");
}

int main(int argc, char* argv[])
{
    float fl;
    scanf ("%f", &fl);
    // fl = 0.15625;
    floatToText(&fl);
    
}
