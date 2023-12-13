#include <stdio.h>

int main(void)
{
	int score[5];
	int i;
	int total = 0;
	double avg;
	int count;
	
	count = sizeof(score) / sizeof(score[0]);
	
	for (i = 0; i < count; i++)
	{
		scanf("%d", &score[i]);
	}
	
	return 0;
}
