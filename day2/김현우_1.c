#include <stdio.h>

int main(void)
{
	int arr[9] = {0,};
	int won[9] = {10000, 5000, 1000, 500, 100, 50, 10, 5, 1};
	
	int sal = 0;
	
	printf("월급: ");
	scanf("%d", &sal);
	int i;
	for(i = 0; i < 9; i++)
	{
		arr[i] = sal / won[i];
		printf("\n%d원권  %d매", won[i], arr[i]);
		sal -= won[i] * arr[i];
	}
	return 0;
}
