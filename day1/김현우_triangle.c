#include <stdio.h>

int main(void)
{
	int num;
	int i;
	int j; 
	int k;
	
	printf("Input number: ");
	scanf("%d", &num);
	
	if(num%2 == 1)
	{
		for(i=1; i<=num; i++)
		{	
			// asc
			printf("\n");
			for(k=1; k<=num-i; k++)
			{
				printf(" ");
			}
			for(j=1; j<=i; j++)
			{
				printf("*");
			}
		}printf("\n");
		
		for(i=1; i<=num; i++)
		{	
			// desc
			printf("\n");
			for(j=1; j<=i-1; j++)
			{
				printf(" ");
			}
			for(k=0; k<=num-i; k++)
			{
				printf("*");
			}
		}printf("\n");
		
		// diamond
		int w = (num-1)/2;
		for(i=0; i<=w-1; i++)
		{
			for(j=0; j<w-i; j++)
			{
				printf(" ");
			}
			for(k=0; k<i*2+1; k++)
			{
				printf("*");
			}printf("\n");
		}
		for(i=0; i<=w+1; i++)
		{
			for(j=0; j<i; j++)
			{
				printf(" ");
			}
			for(k=0; k<(w-i+1)*2-1; k++)
			{
				printf("*");
			}
			printf("\n");
		}	
	}
	else
	{
		printf("\n# 짝수가 입력되었습니다!");
	}
	
	return 0;
}
