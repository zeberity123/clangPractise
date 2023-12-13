#include <stdio.h>
int main(void)
{	
	int a;
	unsigned char packed = 0;
	printf("���� �Է� (��:0, ��:1): ");
	scanf("%d", &a);
	
	packed |= (a & 1);
	
	printf("\n������ ���� �Է�: ");
	scanf("%d", &a);
	
	packed |= ((a<<1) & 14);
	
	printf("\n���� ���� �Է�(������:0, ����:1): ");
	scanf("%d", &a);

	packed |= ((a<<4) & 16);

	printBit(packed);

	return 0;
}


void printBit(unsigned char num)
{
    unsigned char mask = 0x01;
    int i=0;
    for(i=7; i>=0 ; i--)
	{
		if((mask << i) & num)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}
