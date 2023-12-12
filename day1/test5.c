#include <stdio.h>

void main(void)
{
	static char fruit[] = "apple";
	char *ptr; // char 형 포인터변수 *는 참조 연산자 (주소) 
	
	ptr = fruit + strlen(fruit); // strlen -> NUll문자 제외 개수 리턴 
	
	while(--ptr >= fruit)
		puts(ptr);
}
