/*
 * idcheck.c
 *
 *  Created on: 2015. 2. 10.
 *      Author: elayer
 */
#include "wshop1.h"
#ifdef IDCHECK

int stroNum(char *str, int s, int e);
int leap_year(int year);
int formatErrorCheck(char *p_num);
int isY(void);
void idCheck(void);

int strtoNum(char *str, int s, int e)
{
    int num=0;
    int multi=1;
    int idx;
    int diff='1'-1;

    for(idx=e; idx>=s; idx--) {
        num += multi*(str[idx]-diff);
        multi*=10;
    }
    return num;
}

#if 0
int leap_year(int year)
{
    int leap=0;

    leap = !(year%4) && (year%100); //4�� ����̸鼭 100�� ����� �ƴϸ� ����
    leap = leap || !(year%400); //�׷��� 400�� ����� ����

	// �� ������ �ѹ��� �ϸ�
	 // leap = ( (!(year%4) && (year%100)) || !(year%400));
    return leap;
}
#endif

int leap_year(int year)
{
	if(year%4!=0) return 0;
	else if(year%100!=0) return 1;
	else if(year%400==0) return 1;
	else return 0;
}

int formatErrorCheck(char *p_num){
    int dayofmonth[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
	int check_num;
    int i, mod = 0, sum = 0;
    int year, leap=0;

    //�ֹι�ȣ���̴� 13
    if(strlen(p_num) != 13) {
        return 0;
    }
	//���� 12���� �Ѿ�� �ȵȴ�.
    if(strtoNum(p_num,2,3) > 12) {
        return 1;
    }
	//���� ������ ��¥�� �Ѿ�� �ȵȴ�.
    if(strtoNum(p_num,4,5) > dayofmonth[strtoNum(p_num, 2,3)]) {
       return 2;
    }
	//�����̸� 1
    year = (strtoNum(p_num, 6, 6) <=2) ? 1900  : 2000;
    year += strtoNum(p_num,0,1);
    leap = leap_year(year);

    //2���̰� ����̸� 29�� ������ �ȵȴ�.
    if(strtoNum(p_num,2,3)==2 && leap!=1 && strtoNum(p_num,4,5)==29){
	    return 3;
    }
    if(p_num[6]-'0'< 1 || p_num[6]-'0'> 4){
        return 4;
    }

	  //�ֹι�ȣ �����ڵ�(�����ѹ�) �˻�
	for(i=0,check_num = 2;i<12;i++,check_num++) {
        if(check_num == 10)
            check_num = 2;
        sum += check_num * (p_num[i] - '0');
    }
    mod = sum % 11;
    mod = (11-mod)%10;
    if(mod != p_num[12]-'0')
		return  5;

    return -1;
}

int isY(void){
    char answer;
    printf("�ٽ� �Է��Ͻðڽ��ϱ�? (y/n) "); OUT;
    fflush(stdin);
    scanf("%c", &answer);
    if (answer == 'Y' || answer == 'y') return 1;
    return 0;
}

int main(void) {
    char *errormsg[] = {
        "�ֹε�Ϲ�ȣ ���̰� Ʋ�Ƚ��ϴ�.",
        "�߸� �Էµ� ����ȣ �Դϴ�.",
        "�߸� �Էµ� �Ϲ�ȣ �Դϴ�.",
        "����ε� ���⳯¥�Դϴ�.",
        "���� ��ȣ�� �߸� �Է� �Ǿ����ϴ�.",
		"�����ڵ� ������ �ֹε�� ��ȣ �Դϴ�."
    };
    char p_num[15];
    int errorno=0;

    do {
        printf("\"-\"�� ������ Ȯ���� �ֹε�� ��ȣ 13�ڸ��� �Է��ϼ��� : "); OUT;
        scanf("%s", p_num);

        errorno = formatErrorCheck(p_num);
        if (errorno >= 0)
            printf("%s\n", errormsg[errorno]);
	    else
	        printf("�ùٸ� �ֹε�� ��ȣ �Դϴ�.\n");

    } while(isY());
}

#endif
