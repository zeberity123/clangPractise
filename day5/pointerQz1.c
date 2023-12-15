#include <stdio.h>

int main(void)
{
	char *str = "elephant"; // ¹®ÀÚ¿­ -> rodata (read only) 
	
//	*(str + 4) = 'a';
	str = "rabbit";
//	str[2] = 'k';
//	scanf("%s", str);
	printf("ss");
	return 0;
}
