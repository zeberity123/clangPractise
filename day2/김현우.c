#include <stdio.h>
int main(void)
{
	int age = 25, chest = 95;
	char size;
	
	if (age < 2)
	{
		if (chest < 85) size = 'S';
		else if (chest >= 85 < 95) size = 'M';
		else size = 'L';
	}
	else
	{
		if (chest < 90) size = 'S';
		else if (chest >= 90 < 100) size = 'M';
		else size = 'L';
	}
	printf("사이즈는 %c입니다.\n", size);
	return 0;
}
