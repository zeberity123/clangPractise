#include <stdio.h>
int main(void)
{
	int a = 0;
	printf("���� �Է��ϼ���(1,2,3,4,8): ");
	scanf("%d", a);
	
	char w[] = "";
	w = ((a<<3) & 8) ? "off" : "on";
	printf("������ %s", w);
	return 0;
}
