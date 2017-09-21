#include <stdio.h>
#include <string.h>

void swap(void* a, void* b, int bitCount){
	void* tmp[bitCount];
	memcpy(tmp, a, bitCount);
	memcpy(a, b, bitCount);
	memcpy(b, tmp, bitCount);
}

int main() {
	int a, b;
	scanf ("%d %d", &a, &b);
	swap(&a, &b, sizeof(int));
	printf("%d %d\n", a, b);
}
