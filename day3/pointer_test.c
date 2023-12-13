#include <stdio.h>
void main(void)
{
	int *ptr;
	int n[] = {5, 10, 22, 34, 36, 44};
	ptr = n;
	
	printf("%d", *ptr++);
	printf("%d\n", *ptr);
	
	printf("%d", *ptr+1);
	printf("%d\n", *ptr);
	
	printf("%d", ++*ptr);
	printf("%d\n", *ptr);
	
	printf("%d", *(ptr+1));
	printf("%d\n", *ptr);
	
	printf("%d", *ptr+=1);
	printf("%d\n", *ptr);
	
	printf("%d", *++ptr);
	printf("%d\n", *ptr);
	
	printf("%d", (*ptr)++);
	printf("%d\n", *ptr);
}
