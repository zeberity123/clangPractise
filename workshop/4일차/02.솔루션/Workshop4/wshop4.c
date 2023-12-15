/*
 * wshop4.c
 *
 *  Created on: 2015. 2. 11.
 *      Author: elayer
 */

#include <stdio.h>
#include <string.h>
#define OUT fflush(stdout)
#define PAUSE do { OUT; fflush(stdin); 	getchar(); } while(0)

// 사번 등록, 로그인 메뉴 관련 함수와 변수
//-----------------------------------------------------------------
int disp_menu(void);
void enroll_num(int *e_num, char (*e_pwd)[11], int *e_cnt, int login_num);
int is_enroll_num(int num, int *e_num, int e_cnt);
void login_out(int *e_num, char (*e_pwd)[11], int e_cnt,  int *login_num);
//-----------------------------------------------------------------

// 사번 등록 관련 처리 함수
int get_checkRange(char* what, int min, int max);   						 // 사번을 입력 받아 반환하는 함수
void printIDList(int *e_num, char (*e_pwd)[11], int e_cnt);   		 // 사번 및 비밀번호를 출력하는 함수
int deleteID(int dno, int *e_num, char (*e_pwd)[11], int e_cnt);    // 사번 및 비밀번호 삭제를 위한 함수
int insertID(int id, int *e_num, char (*e_pwd)[11], int e_cnt);        // 사번 및 비밀번호 삽입을 위한 함수

//  사번 및 비밀번호 배열의 dno 번째 요소를 삭제하는 함수, 변경된 요소의 수 반환
int deleteFromIDList(int dno, int*e_num, char (*e_pwd)[11], int e_cnt);

//  사번 및 비밀번호 배열에 새로운 id, pwd를 삽입하는 함수, 변경된 요소의 수 반환
int insertToIDList(int id, char* pwd, int *e_num, char (*e_pwd)[11], int e_cnt);
//-----------------------------------------------------------------

// 비밀번호 입력과 문자열 처리함수
//-----------------------------------------------------------------
void input_password(char *pwd);
char *verify_pwd(char *sp);
int my_strlen(char *sp);
void my_strcpy(char *dp, char *sp);
void my_gets(char *sp, int size);
//-----------------------------------------------------------------

int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };   // 각 달의 일수
#define MAX_ARY 5			 // 최대 등록인원 수

int main(void)
{
	/* wshop3에서 전역이었던 것을 지역으로 수정함 */
	int e_num[MAX_ARY]={0};           		// 사번 배열
	char e_pwd[MAX_ARY][11]={""};      	// 비밀번호  배열 (최대 5명, 최대 10자)
	int e_cnt=0;              							// 등록 인원 수
	int login_num = 0;      							// 로그인 된 사번 저장
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
			printf("@ 메뉴 번호가 아닙니다!\n\n");
			break;
		}
	}
	PAUSE;
	return 0;
}

// 메뉴 출력 후 선택 번호 반환
int disp_menu(void)
{
	int num;

	printf("\n===[ 회의실 예약 시스템 ]===\n");
	printf("1. 사번 등록/삭제\n");
	printf("2. 로그인/로그아웃\n");
	printf("3. 회의실 예약\n");
	printf("4. 예약 상태 조회\n");
	printf("0. 종료\n");
	printf("---------------------------\n");

	printf("> 번호 선택 : "); OUT;
	scanf("%d", &num);

	return num;
}


//  매개변수 설명
//	e_num : 사번 배열(수정 가능)
//	e_cnt : 현재 등록 인원(수정 가능)
//	e_pwd : 비밀 번호 배열(수정 가능)
//	login_num : 로그인 번호 - 로그인 되지 않은 경우만 이 메뉴를 사용할 수 있도록 검사

// 사번 등록 / 삭제

void enroll_num(int *e_num, char (*e_pwd)[11], int *e_cnt, int login_num)
{
	int num;                          			// 사번
	int index;                                  // 사번이 있는 배열의 위치

	if (login_num != 0)                   // 이미 로그인 된 상태면 반환
	{
		printf("@ 로그아웃 후 사용할 수 있습니다!\n");
		return;
	}

	printf("\n[ 사번 등록/삭제 ]\n\n");
	num = get_checkRange("사번", 1, 9999);
	if (num == 0)  return;

	index = is_enroll_num(num, e_num, *e_cnt);     // 등록이 되어 있는지 확인

	if (index >= 0)                            // 등록된 사번이 있는 경우
	{
		*e_cnt = deleteID(index, e_num, e_pwd, *e_cnt);
	}
	else                                          	// 처음 등록하는 경우
	{
		*e_cnt = insertID(num, e_num, e_pwd, *e_cnt);
	}

}


int get_checkRange(char* what, int min, int max) {
	int input = 0;
	printf("> %s(%d-%d) : ", what, min, max); OUT;
	scanf("%d", &input);
	if ((input < min) || (input > max))     // 허용 범위의 숫자가 아니면 반환
	{
		printf("@ 유효한 번호가 아닙니다!\n");
		return 0;
	}
	return input;
}


int deleteFromIDList(int dno, int *e_num, char (*e_pwd)[11], int e_cnt) {
	int i=0;

	for (i = dno; i < (e_cnt - 1); i++)
	{
		e_num[i] = e_num[i + 1];
		strcpy(e_pwd[i] ,e_pwd[i + 1]);
	}
	e_cnt--;										// 등록된 사번 수 감소
	return e_cnt;
}

int insertToIDList(int id, char* pwd, int *e_num, char (*e_pwd)[11], int e_cnt) {
	e_num[e_cnt] = id;
	strcpy(e_pwd[e_cnt], pwd);
	e_cnt++;                                   // 등록된 사번 수 증가
	printf("# %d번이 등록되었습니다!\n", id);
	return e_cnt;
}

void printIDList(int *e_num, char (*e_pwd)[11], int e_cnt){
	int i=0;

	printf("\n>> 현재 등록된 사번(비밀번호) : ");
	for (i = 0; i < e_cnt; i++)
	{
		printf("%5d(%s)", e_num[i], e_pwd[i]);
	}
	printf("\n\n");
}

int deleteID(int dno, int *e_num, char (*e_pwd)[11], int e_cnt) {
	char yn = 0;
	char pwd[11]="";

	printf("@ 이미 등록되었습니다!\n");
	printf("@ 삭제 하시겠습니까(Y/N)?"); OUT;

	fflush(stdin);
	scanf("%c", &yn);

	if ((yn == 'Y') || (yn == 'y'))
	{
		//  비밀번호를 입력 받아 사번에 맞는 비밀번호인 경우 삭제 처리
		printf("> 비밀번호 입력 : "); OUT;
		my_gets(pwd, 10);    // 배열의 크기까지만 입력
		if (strcmp(pwd, e_pwd[dno]) != 0 ) {
			printf("@ 비밀번호가 다릅니다. 삭제할 수 없습니다.\n");
			return e_cnt;
		}
		printf("@ %d번이 삭제 되었습니다!\n", e_num[dno]);
		e_cnt = deleteFromIDList(dno, e_num, e_pwd, e_cnt);
		printIDList(e_num, e_pwd, e_cnt);
	} else {
		printf("@ 취소 되었습니다!\n");
	}
	return e_cnt;
}


int insertID(int id, int *e_num, char (*e_pwd)[11], int e_cnt){
	char pwd[11] = "";

	if (e_cnt == MAX_ARY)                          						// 등록인원 수가 최대 인원 수와 같으면 반환
	{
		printf("@ 등록 인원이 초과되었습니다!");
		return e_cnt;
	}
	input_password(pwd);

	e_cnt = insertToIDList(id, pwd, e_num, e_pwd, e_cnt);
	printIDList(e_num, e_pwd, e_cnt);
	return e_cnt;
}

// 등록된 번호인지 확인
int is_enroll_num(int num, int *e_num, int e_cnt)
{
	int i;

	for (i = 0; i < e_cnt; i++)
	{
		if (num == e_num[i]) return i;
	}
	return -1;
}

// 비밀번호 형식 검사
char *verify_pwd(char *sp)
{
	char *errmsg[] = {
			"5자 이상 입력해야 합니다!",
			"알파벳과 숫자만 가능합니다!"	};
	char *tp;
	char ch;

	if (my_strlen(sp) < 5 )
	{
		return errmsg[0];
	}

	for (tp = sp; *tp != '\0'; tp++)
	{
		ch = *tp;
		if(  !(ch >= 'a' && ch <= 'z') && !( ch >= 'A' && ch <= 'Z' ) && !(ch >='0' && ch <='9') )
		{
			return errmsg[1];
		}
	}
	return NULL;
}

// 비밀번호 입력
void input_password(char *pwd)
{
	char first[11];      		// 첫 번째 입력한 비밀번호 저장
	char second[11];       // 비밀번호 문자열 입력할 임시 배열
	char *err_msg;      	 // 입력 과정에서 형식이 맞지 않은 경우 출력할 에러 메시지

	do {
		while (1)
		{
			printf("> 비밀번호(5-10자) : "); OUT;
			my_gets(first, 10);    // 배열의 크기까지만 입력
			err_msg = verify_pwd(first);                 // 문자열 형식 검사 후 에러 메시지 반환
			if (err_msg == NULL) break;

			printf("@ %s\n", err_msg);
		}

		printf("> 한번 더 입력하세요 : "); OUT;
		my_gets(second, 10);
		if ( strcmp(first, second) == 0)   break;              // 첫 번째와 두번째 입력 문자열이 같은지 비교

		printf("@ 비밀번호가 일치하지 않습니다!\n");
	} while (1);
	my_strcpy(pwd, first);
}



// 배열에 저장된 문자열의 길이 반환
int my_strlen(char *sp)
{
	int cnt = 0;

	while (*sp++ != '\0')	{
		cnt++;
	}
	return cnt;
}

// 문자열 복사 함수
void my_strcpy(char *dp, char *sp)
{
	while ( (*dp++ = *sp++) != '\0');
}

// 배열의 크기까지만 문자열 입력
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


// 로그인 / 로그아웃
void login_out(int *e_num, char (*e_pwd)[11], int e_cnt, int *login_num)
{
	int num;
	char pwd[11]="";
	int index;

	if (*login_num != 0)
	{
		*login_num = 0;
		printf("# 로그아웃 되었습니다!\n");
		return;
	}

	printf("\n[ 로그인 ]\n\n");

	printf("> 사번 : "); OUT;
	scanf("%d", &num);
	index = is_enroll_num(num, e_num, e_cnt);            // 등록된 사번이면 배열의 등록 위치 반환, 아니면 -1 반환

	if (index == -1)
	{
		printf("@ %d번은 등록되지 않은 번호입니다!\n", num);
		return;
	}

	printf("> 비밀번호 : "); OUT;
	fflush(stdin); gets(pwd);
	if (strcmp(pwd, e_pwd[index]) != 0)
	{
		printf("@ 비밀번호가 틀렸습니다!\n");
		return;
	}
	*login_num = num;                       // 로그인 사번 저장
	printf("# 로그인 되었습니다!\n");
}

