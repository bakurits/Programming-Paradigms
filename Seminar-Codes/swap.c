#include <stdio.h>

void swap(void* a, void* b, int bitCount){
	
}

int main() {
	int a, b;
	scanf ("%d %d", &a, &b);
	swap(&a, &b, sizeof(int));
	printf("%d %d\n", a, b);
}
