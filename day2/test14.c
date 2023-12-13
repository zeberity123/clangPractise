#include <stdio.h>

int main(void)
{
	int s = 5, tot = 0;
	
	switch(s){
		default: tot=tot+1;
		case 1: tot=tot+2;
		case 2: tot=tot+3;
		case 3: tot=tot+4;
	}
	printf("%d\n", tot);
}

