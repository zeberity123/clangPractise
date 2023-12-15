/*
 * wshop4.c
 *
 *  Created on: 2015. 2. 11.
 *      Author: elayer
 */

#include "wshop4.h"

// ��� ���, �α��� �޴� ���� �Լ��� ����
//-----------------------------------------------------------------
int disp_menu(void);
void enroll_num(int *e_num, char (*e_pwd)[11], int *e_cnt, int login_num);
int is_enroll_num(int num, int *e_num, int e_cnt);
void login_out(int *e_num, char (*e_pwd)[11], int e_cnt,  int *login_num);
//-----------------------------------------------------------------

// ��� ��� ���� ó�� �Լ�
int get_checkRange(char* what, int min, int max);   						 // ����� �Է� �޾� ��ȯ�ϴ� �Լ�
void printIDList(int *e_num, char (*e_pwd)[11], int e_cnt);   		 // ��� �� ��й�ȣ�� ����ϴ� �Լ�
int deleteID(int dno, int *e_num, char (*e_pwd)[11], int e_cnt);    // ��� �� ��й�ȣ ������ ���� �Լ�
int insertID(int id, int *e_num, char (*e_pwd)[11], int e_cnt);        // ��� �� ��й�ȣ ������ ���� �Լ�

//  ��� �� ��й�ȣ �迭�� dno ��° ��Ҹ� �����ϴ� �Լ�, ����� ����� �� ��ȯ
int deleteFromIDList(int dno, int*e_num, char (*e_pwd)[11], int e_cnt);

//  ��� �� ��й�ȣ �迭�� ���ο� id, pwd�� �����ϴ� �Լ�, ����� ����� �� ��ȯ
int insertToIDList(int id, char* pwd, int *e_num, char (*e_pwd)[11], int e_cnt);
//-----------------------------------------------------------------

// ��й�ȣ �Է°� ���ڿ� ó���Լ�
//-----------------------------------------------------------------
void input_password(char *pwd);
char *verify_pwd(char *sp);
int my_strlen(char *sp);
void my_strcpy(char *dp, char *sp);
void my_gets(char *sp, int size);
//-----------------------------------------------------------------

int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };   // �� ���� �ϼ�
#define MAX_ARY 5			 // �ִ� ����ο� ��

int main(void)
{
	/* wshop3���� �����̾��� ���� �������� ������ */
	int e_num[MAX_ARY]={0};           		// ��� �迭
	char e_pwd[MAX_ARY][11]={""};      	// ��й�ȣ  �迭 (�ִ� 5��, �ִ� 10��)
	int e_cnt=0;              							// ��� �ο� ��
	int login_num = 0;      							// �α��� �� ��� ����
	int num;

	while (1)
	{
		num = disp_menu();
		if (num == 0) break;

		switch (num)
		{
		case 1:
			enroll_num(e_num, e_pwd, &e_cnt, login_num); break;
		case 2:
			login_out(e_num, e_pwd, e_cnt, &login_num); break;
		case 3:
			//input_schedule();	break;
		case 4:
			//search_schedule(); break;
		default:
			printf("@ �޴� ��ȣ�� �ƴմϴ�!\n\n");
			break;
		}
	}
	PAUSE;
	return 0;
}

// �޴� ��� �� ���� ��ȣ ��ȯ
int disp_menu(void)
{
	int num;

	printf("\n===[ ȸ�ǽ� ���� �ý��� ]===\n");
	printf("1. ��� ���/����\n");
	printf("2. �α���/�α׾ƿ�\n");
	printf("3. ȸ�ǽ� ����\n");
	printf("4. ���� ���� ��ȸ\n");
	printf("0. ����\n");
	printf("---------------------------\n");

	printf("> ��ȣ ���� : "); OUT;
	scanf("%d", &num);

	return num;
}


//  �Ű����� ����
//	e_num : ��� �迭(���� ����)
//	e_cnt : ���� ��� �ο�(���� ����)
//	e_pwd : ��� ��ȣ �迭(���� ����)
//	login_num : �α��� ��ȣ - �α��� ���� ���� ��츸 �� �޴��� ����� �� �ֵ��� �˻�

// ��� ��� / ����

void enroll_num(int *e_num, char (*e_pwd)[11], int *e_cnt, int login_num)
{
	int num;                          			// ���
	int index;                                  // ����� �ִ� �迭�� ��ġ

	if (login_num != 0)                   // �̹� �α��� �� ���¸� ��ȯ
	{
		printf("@ �α׾ƿ� �� ����� �� �ֽ��ϴ�!\n");
		return;
	}

	printf("\n[ ��� ���/���� ]\n\n");
	num = get_checkRange("���", 1, 9999);
	if (num == 0)  return;

	// todo : ����� ��ϵǾ� �ִ��� Ȯ���Ͽ� ��ϵ� ����� �ִ� ��� ��� ����, ���� ��� ��� ��� ����


}


// �α��� / �α׾ƿ�
void login_out(int *e_num, char (*e_pwd)[11], int e_cnt, int *login_num)
{
	int num;
	char pwd[11]="";
	int index;

	if (*login_num != 0)
	{
		*login_num = 0;
		printf("# �α׾ƿ� �Ǿ����ϴ�!\n");
		return;
	}

	printf("\n[ �α��� ]\n\n");

	printf("> ��� : "); OUT;
	scanf("%d", &num);
	index = is_enroll_num(num, e_num, e_cnt);            // ��ϵ� ����̸� �迭�� ��� ��ġ ��ȯ, �ƴϸ� -1 ��ȯ

	if (index == -1)
	{
		printf("@ %d���� ��ϵ��� ���� ��ȣ�Դϴ�!\n", num);
		return;
	}

	printf("> ��й�ȣ : "); OUT;
	// todo : ��й�ȣ�� �Է� �޾�  ������ ��� �α��� ó��, �������� ���� ��� ��� ��ȣ�� Ʋ������ ǥ���ϰ� ��ȯó����




	printf("# �α��� �Ǿ����ϴ�!\n");
}


// ------------------------------------------------------------------------------------------------------------------------------------------
int get_checkRange(char* what, int min, int max) {
	int input = 0;
	printf("> %s(%d-%d) : ", what, min, max); OUT;
	scanf("%d", &input);
	if ((input < min) || (input > max))     // ��� ������ ���ڰ� �ƴϸ� ��ȯ
	{
		printf("@ ��ȿ�� ��ȣ�� �ƴմϴ�!\n");
		return 0;
	}
	return input;
}


int deleteFromIDList(int dno, int *e_num, char (*e_pwd)[11], int e_cnt) {
	int i=0;

	//  todo: ��� �� ��й�ȣ �迭���� dno ��ġ�� ��� ����

	return e_cnt;
}

int insertToIDList(int id, char* pwd, int *e_num, char (*e_pwd)[11], int e_cnt) {

	//  todo: ��� �� ��й�ȣ �迭�� �� �ڿ� id(���), pwd(��й�ȣ) �߰�


	return e_cnt;
}

void printIDList(int *e_num, char (*e_pwd)[11], int e_cnt){
	int i=0;

	printf("\n>> ���� ��ϵ� ���(��й�ȣ) : ");
	for (i = 0; i < e_cnt; i++)
	{
		printf("%5d(%s)", e_num[i], e_pwd[i]);
	}
	printf("\n\n");
}

int deleteID(int dno, int *e_num, char (*e_pwd)[11], int e_cnt) {
	char yn = 0;
	char pwd[11]="";

	printf("@ �̹� ��ϵǾ����ϴ�!\n");
	printf("@ ���� �Ͻðڽ��ϱ�(Y/N)?"); OUT;

	fflush(stdin);
	scanf("%c", &yn);

	// todo : yn�� ���� Y �Ǵ� y �� ��� ��й�ȣ�� �Է� �޾� ����� �´� ��й�ȣ �� ��� ���� ó�� �� �� e_cnt ����Ǿ� ��ȯ
	// ��� ��ȣ�� Ʋ�� ��� ��� ��ȣ�� �ٸ��ٴ� �޽����� ����ϰ� e_cnt ������� ��ȯ
	// yn�� ���� Y �Ǵ� y�� �ƴ� ��� ��� �Ǿ��ٴ� �޽��� ��� (���� ����)


	return e_cnt;
}


int insertID(int id, int *e_num, char (*e_pwd)[11], int e_cnt){
	char pwd[11] = "";

	if (e_cnt == MAX_ARY)                          						// ����ο� ���� �ִ� �ο� ���� ������ ��ȯ
	{
		printf("@ ��� �ο��� �ʰ��Ǿ����ϴ�!");
		return e_cnt;
	}
	// todo : ��й�ȣ�� input_password�� �̿��Ͽ� pwd�� �Է� ���� ��, id, pwd�� �迭�� �� �ڿ� �߰��ϰ� id, pwd ����� �����



	return e_cnt;
}

// ��ϵ� ��ȣ���� Ȯ��
int is_enroll_num(int num, int *e_num, int e_cnt)
{
	int i;

	for (i = 0; i < e_cnt; i++)
	{
		if (num == e_num[i]) return i;
	}
	return -1;
}

// ��й�ȣ ���� �˻�
char *verify_pwd(char *sp)
{
	char *errmsg[] = {
			"5�� �̻� �Է��ؾ� �մϴ�!",
			"���ĺ��� ���ڸ� �����մϴ�!"	};
	char *tp;	// ������ ��ġ�� ������ ����
	char ch;	// ���ڸ� ������ ����

    // todo: ��й�ȣ ���� �˻� �ڵ� ����
	// 5���� �̻��̾�� �ϸ�, ���ĺ��� ���ڸ� ������  ���� �ڵ�� errmsg ���

	return NULL;
}

// ��й�ȣ �Է�
void input_password(char *pwd)
{
	char first[11];      		// ù ��° �Է��� ��й�ȣ ����
	char second[11];       // ��й�ȣ ���ڿ� �Է��� �ӽ� �迭
	char *err_msg;      	 // �Է� �������� ������ ���� ���� ��� ����� ���� �޽���

	// todo : ��й�ȣ�� �Է� �޾� �����ϴ� �ڵ�


	my_strcpy(pwd, first);  // ��й�ȣ�� pwd�� �����Ͽ� ��ȯ�Ѵ�.
}



// �迭�� ����� ���ڿ��� ���� ��ȯ
int my_strlen(char *sp)
{
	int cnt = 0;

	// todo : ���ڿ��� ���̸� ���ϴ� �ڵ� �ۼ�

	return cnt;
}

// ���ڿ� ���� �Լ�
void my_strcpy(char *dp, char *sp)
{
	// todo: ���ڿ��� �����ϴ� �ڵ� �ۼ�

}

// �迭�� ũ������� ���ڿ� �Է�
void my_gets(char *sp, int size) {
	char ch;
	int i = 0;

	fflush(stdin);
	ch = getchar();
	while ((i < (size - 1)) && (ch != '\n'))
	{
		sp[i] = ch;
		i++;
		ch = getchar();
	}
	sp[i] = '\0';
	fflush(stdin);
}


