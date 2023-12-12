#include <stdio.h>

int main(void)
{	
	int num = 0;
	int cnt = 0;
	int i;
	printf("숫자를 입력하세요(종료: 0) :");
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
			printf("소수입니다.");
		}
		else
		{
			printf("소수가 아닙니다.");
		}
		printf("\n숫자를 입력하세요(종료: 0) :");
		scanf("%d", &num);
		cnt = 0;
	}
	printf("Bye~~");
	
	return 0;
}
