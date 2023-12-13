#include <stdio.h>
int main(void)
{
	int i;
	while(1){
		for(i=1; i<=5; i++){
			if(i%3==0) continue;
			printf("C programming..\n");
		}
		if(i==5) break;
	}
	return 0;
}
