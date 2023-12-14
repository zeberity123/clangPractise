#include <stdio.h>

int main(void)
{
	char *ptr[] = {"red", "orange", "pink", "white", "blue", "brown", "black", "gray"};
	
	printf("%c\n", *(*(ptr+3)+3)); //t
	printf("%c\n", *(*(ptr+5)+4)); //n
	
	return 0;
}
