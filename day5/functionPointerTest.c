#include <stdio.h>

int num(char []);

int main(void)
{
	int (*fp)(char s[]);
	int res;
	fp = num;
	res = fp("Hello");
	printf("result : %d\n", res);
	
	return 0;
}

int num(char s[])
{
	return strlen(s);
}

