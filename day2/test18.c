#include <stdio.h>
int main(void)
{
	int a = 0;
	printf("값을 입력하세요(1,2,3,4,8): ");
	scanf("%d", a);
	
	char w[] = "";
	w = ((a<<3) & 8) ? "off" : "on";
	printf("빨간불 %s", w);
	return 0;
}
