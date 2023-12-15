#include <stdio.h>

int sum(int, int);
int sub(int, int);
int mul(int, int);
int div(int, int);

int main(void)
{
	int (*fp)(int, int);
	int res;
	
	fp = sum;
	res = fp(10, 20);
	printf("result : %d\n", res);
	
	fp = sub;
	res = fp(30, 10);
	printf("result : %d\n", res);

	fp = mul;
	res = fp(3, 13);
	printf("result : %d\n", res);
	
	fp = div;
	res = fp(39, 3);
	printf("result : %d\n", res);
	
	return 0;
}

int sum(int a, int b)
{
	return (a + b);
}

int sub(int a, int b)
{
	return (a - b);
}

int mul(int a, int b)
{
	return (a * b);
}

int div(int a, int b)
{
	return (a / b);
}

