#include <stdio.h>

void main(void)
{
	static char fruit[] = "apple";
	char *ptr; // char �� �����ͺ��� *�� ���� ������ (�ּ�) 
	
	ptr = fruit + strlen(fruit); // strlen -> NUll���� ���� ���� ���� 
	
	while(--ptr >= fruit)
		puts(ptr);
}
