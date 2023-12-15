#include <stdio.h>

int main(void)
{
	int a, b;
	stt(&a, &b);
	printf("%d%d", a, b);
	return 0;
}

int stt(int *a, int *b)
{
	*a = 5;
	*b = 7;
}
