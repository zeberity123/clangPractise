#include <stdio.h>

int main(void)
{	
	int num = 0;
	int cnt = 0;
	int i;
	printf("���ڸ� �Է��ϼ���(����: 0) :");
	scanf("%d", &num);
	
	while(num > 0)
	{ 	
		for(i=2; i<=num; i++)
		{
			if(num%i == 0)
			{
				cnt++;
			}
		}
		
		if(cnt == 1)
		{
			printf("�Ҽ��Դϴ�.");
		}
		else
		{
			printf("�Ҽ��� �ƴմϴ�.");
		}
		printf("\n���ڸ� �Է��ϼ���(����: 0) :");
		scanf("%d", &num);
		cnt = 0;
	}
	printf("Bye~~");
	
	return 0;
}
