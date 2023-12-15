#include <stdio.h>

int main()
{
	int i;
	for(i=10; i>0; i--)
	{
		if(i%2==0 || i%3==0)
			continue;
		printf("%d", i);
	}
	return 0;
}
