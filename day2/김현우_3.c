#include <stdio.h>

void sum(int a);

int main(void)
{
	sum(10);
	sum(100);
	return 0;
}

void sum(int a)
{
	int sum = 0;
	int i; 
	for(i = 0; i <= a; i++)
	{
		sum += i;
	}
	printf("1부터 %d까지의 합은 %d입니다.\n", a, sum);
}
