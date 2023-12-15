/*
 * packing.c
 *
 *  Created on: 2015. 2. 10.
 *      Author: elayer
 */
#include "wshop1.h"

#ifdef PACKING
int main()
{
	unsigned int     packing = 0;
	int     id;
	int     type;
	char    gender;

	printf("# 직원 정보 입력 \n");

	printf("* ID : "); OUT;
	scanf("%d", &id);

	printf("* 작업형태 : "); OUT;
	scanf("%d", &type);

	printf("* 성별(M or F) : "); OUT;
	fflush(stdin);
	scanf(" %c", &gender);

	packing |= id;
	packing |= type << 20;
	packing |= ((gender == 'M')? 0 : 1) << 28;

	printf("\n# 패킹결과 \n");
	printf(">> %u\n", packing );

	printf("\n# 언패킹 결과 \n");

	printf("* ID : %d\n", packing & 0xFFFFF);
	printf("* 작업형태 : %d\n", (packing >> 20) & 0xFF);
	printf("* 성별 : %s\n", (packing >> 28)? "여" : "남");

	/*
    printf("* ID : %d\n", (packing << 12) >> 12);
    printf("* 작업형태 : %d\n", (packing << 4 ) >> 24 );
    printf("* 성별 : %s\n", (packing >> 28)? "여" : "남");
	 */
	return 0;
}

#endif
