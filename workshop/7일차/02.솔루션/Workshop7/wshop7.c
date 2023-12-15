
#include "wshop7.h"

typedef struct     //  ��¥ ����ü
{
	int year;			// ��
	int month;		// ��
	int day;				// ��
}DateT;

typedef struct     // ������ ����ü
{
	int num;       	// ���
	DateT date;
	int startT;			// ���� �ð�  ( 0 ~ 23 �Է�)
	int endT;           // ���� �ð�  (0 ~ 23 �Է�)
	char *note;      	// ������ ����
} Schedule;

Schedule s_ary[100];    	 // ������ �迭, �ִ� ��� �� 100��
int s_cnt = 0;         		 // ���� ������ ��� ��

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

// �޷� ��� ���� �Լ�
//-----------------------------------------------------------------
int leap_check(int year);
int get_days(int year, int month);
int get_weekday(int year, int month);
void disp_calendar(int year, int month);
//-----------------------------------------------------------------

// ���� ���, ��ȸ, ��� ���� ó�� �Լ�
//-----------------------------------------------------------------
void input_schedule(int login_num);
void search_schedule(void);
void delete_schedule(int login_num);
int on_schedule(int year, int month, int day);
void print_schedule(DateT dPrint);
void deleteFromScheduleList(int delIndex, int selNo);
char *get_str(void);
//-----------------------------------------------------------------

// ��������� ���� ó�� �Լ�
//-----------------------------------------------------------------
void readdataFromFile(void);
void writedataToFile(void);
//-----------------------------------------------------------------

// ���� ó�� �Լ�
void exit_routine();

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

#if 1
	// to test case 3, 4, 5
	e_num[0] = 1;
	strcpy(e_pwd[0],"123123");
	e_cnt = 1;
	login_num = 1;
#endif
	readdataFromFile();
	while (1)
	{
		num = disp_menu();
		if (num == 0) {
			break;
		}

		switch (num)
		{
		case 1:
			enroll_num(e_num, e_pwd, &e_cnt, login_num); break;   // Workshop4���� ����
		case 2:
			login_out(e_num, e_pwd, e_cnt, &login_num); break;   // Workshop4���� ����
		case 3:
			input_schedule(login_num);	break;
		case 4:
			search_schedule(); break;
		case 5:
			delete_schedule(login_num); break;
		default:
			printf("@ �޴� ��ȣ�� �ƴմϴ�!\n\n");
			break;
		}
	}
	exit_routine();
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
	printf("4. ȸ�ǽ� ���� ���� ��ȸ\n");
	printf("5. ȸ�ǽ� ���� ���\n");
	printf("0. ����\n");
	printf("---------------------------\n");

	printf("> ��ȣ ���� : "); OUT;
	scanf("%d", &num);

	return num;
}

void getDate(DateT *dt) {
	printf("> ��, �� �Է� : "); OUT;
	scanf("%d%d",&dt->year, &dt->month);
	disp_calendar(dt->year, dt->month);        // �Է��� ���� �޷� ���

	printf("# ��¥�� �����ϼ��� : "); OUT;
	scanf("%d", &dt->day);
}
// ȸ�ǽ� ���� ������ �Է�
void input_schedule(int login_num)
{
	Schedule newSchedule;

	if (login_num == 0)      // �α��ε��� �ʾҴٸ� ��ȯ
	{
		printf("@ �α��� �� ����� �� �ֽ��ϴ�.\n");
		return;
	}
	newSchedule.num = login_num;
	printf("\n[ ȸ�ǽ� ���� ]\n\n");

	getDate(&newSchedule.date);

	printf("# ���� ���� �ð��� �Է��ϼ���. (0~23) : "); OUT;
	scanf("%d", &newSchedule.startT);
	printf("# ���� �� �ð��� �Է��ϼ���. (0~23) : "); OUT;
	scanf("%d", &newSchedule.endT);

	printf("> ���� ���� ���� �Է�(�ѱ� �ִ� 400��) : "); OUT;
	newSchedule.note = get_str();

	s_ary[s_cnt] = newSchedule;
	s_cnt++;
	printf("@ ȸ�ǽ� ������ ��ϵǾ����ϴ�!\n");
}

// ȸ�ǽ� ���� ���� ��ȸ
void search_schedule(void)
{
	DateT dSearch;    // ���� ���¸� �˻��� ��
	int cnt;                		    // ���� �� ��

	printf("\n[ ȸ�ǽ� ���� ���� ��ȸ ]\n\n");

	getDate(&dSearch);

	cnt = on_schedule(dSearch.year, dSearch.month, dSearch.day);         // ������ ��¥�� ������ �� ��ȯ

	if (cnt >0 ) {
		print_schedule(dSearch);
		printf("@ %d���� ����� �������� �ֽ��ϴ�!\n", cnt);
	} else {
		printf("@ ����� �������� �����ϴ�.\n");
	}
}

// ȸ�ǽ� ���� ������ ����

#define ERR_ROUTINE(a) do { printf("%s\n", errmsg[a]); return; } while(0)
void delete_schedule(int login_num)
{
	DateT dDelete;    	// ���� �������� ������ ��
	DateT T;				// �ӽ� ���
	int cnt;                 			// ���� ������ ��
	int index_ary[24][2];  	// �˻��� ���� �������� ������ �� ��ġ ����
	int sel;                 			// ������ ���� ������ ��ȣ
	int i;
	char *errmsg[] = {
			"@ �α��� �� ����� �� �ֽ��ϴ�.\n",
			"@ ����� �������� �����ϴ�!\n",
			"@ ���� ��ȣ�Դϴ�!\n",
			"@ ������ ����ڰ� �ƴմϴ�!\n"

	};

	if (login_num == 0)      // �α��ε��� �ʾҴٸ� ��ȯ
		ERR_ROUTINE(0);

	printf("[ ȸ�ǽ� ���� ��� ]\n\n");

	getDate(&dDelete);

	cnt = on_schedule(dDelete.year, dDelete.month, dDelete.day);         // ������ ��¥�� ������ �� ��ȯ
	if(cnt == 0)
		ERR_ROUTINE(1);

	for (i = 0, cnt = 0; i < s_cnt; i++)
	{
		T = s_ary[i].date;
		if ( (T.day == dDelete.day) && (T.month == dDelete.month) && (T.year == dDelete.year))
		{
			printf("[%2d] %d - %s\n", cnt + 1, s_ary[i].num, s_ary[i].note);
			index_ary[cnt][0] = s_ary[i].num;	      // ������ ��� ���
			index_ary[cnt][1] = i;                          // ������ �迭������  ��ġ ���
			cnt++;
		}
	}

	printf("> ����� ���� ��ȣ (�α��� ���-%d) : ", login_num); OUT;
	scanf("%d", &sel);
	if((sel < 1) || (sel > cnt) )
		ERR_ROUTINE(2);

	if ( index_ary[sel-1][0] != login_num)
		ERR_ROUTINE(3);

	deleteFromScheduleList(index_ary[sel-1][1], sel);
}

// �ش� ��¥�� ���� ������ �� Ȯ��, ���� ��� 0 ��ȯ
int on_schedule(int year, int month, int day)
{
	DateT T;
	int cnt = 0;
	int i;

	for (i = 0; i < s_cnt; i++)
	{
		T = s_ary[i].date;
		if ((T.day == day) && (T.month == month) && (T.year == year))
		{
			cnt++;
		}
	}
	return cnt;
}


// �ش� ��¥�� ������ ���� ���
void print_schedule(DateT dPrint)
{
	DateT T;
	int i;
	int cnt;

	printf("-- %d�� %d�� %d�� ���� ��� --\n", dPrint.year, dPrint.month, dPrint.day);
	for (i = 0, cnt = 1; i < s_cnt; i++)
	{
		T = s_ary[i].date;
		if ((T.day == dPrint.day) && (T.month == dPrint.month) && (T.year == dPrint.year))
		{
			printf("[%2d] ������:%d, �ð�: %2d~%2d, �������: %s\n", cnt, s_ary[i].num,
					s_ary[i].startT, s_ary[i].endT, s_ary[i].note);
			cnt++;
		}
	}
}


void deleteFromScheduleList(int delIndex, int selNo) {
	int i =0;

	free(s_ary[delIndex].note);    //  ���� �Ҵ� �޾Ҵ� �޸� ��ȯ
	for (i =delIndex; i < (s_cnt - 1); i++)
	{
		s_ary[i] = s_ary[i + 1];
	}
	s_cnt--;
	printf("@ %d�� ������ ��� �Ǿ����ϴ�!\n", selNo);
}

// �Է��� ���ڿ��� �����Ҵ� ������ ���� �� ������ ��ȯ
char *get_str(void)
{
	char str[801];
	char *tp;

	my_gets(str, sizeof(str));
	tp = (char *)malloc(strlen(str) + 1);
	strcpy(tp, str);

	return tp;
}
// ���α׷� ���� - ������ �����͸� ���Ͽ� �����ϰ� �����Ҵ� ���� ��ȯ
void exit_routine(void)
{

	int i;
	writedataToFile();

	for (i = 0; i < s_cnt; i++)
	{
		free(s_ary[i].note);
	}

}

// ���Ͽ��� ������ ������ ����
void readdataFromFile(void)
{
	FILE *fp;
	int cnt, i;
	char temp[801];

	fp = fopen("schedule.txt", "a+");
	if (fp == NULL)
	{
		printf("@ ������ ���� ���߽��ϴ�!\n");
		PAUSE;
		exit(1);
	}

	cnt = sizeof(s_ary) / sizeof(s_ary[0]);   // �迭 ����� �� ���
	for (i = 0; i < cnt; i++)
	{
		fscanf(fp, "%d%d%d%d%d%d ", &s_ary[i].num,
				&s_ary[i].date.year, &s_ary[i].date.month, &s_ary[i].date.day, &s_ary[i].startT, &s_ary[i].endT);
		if (feof(fp))
		{
			break;
		}
		fgets(temp, sizeof(temp), fp);
		temp[strlen(temp) - 1] = '\0';
		s_ary[i].note = (char *)malloc(strlen(temp) + 1);
		strcpy(s_ary[i].note, temp);
	}
	printf("@ ���Ͽ��� %d���� �������� �о����ϴ�!\n\n", i);
	s_cnt = i;

	fclose(fp);
}

void writedataToFile(void)
{
	FILE *fp;
	int i;

	fp = fopen("schedule.txt", "w");
	if (fp == NULL)
	{
		printf("@ ������ ���� ���߽��ϴ�!\n");
		PAUSE;
		exit(1);
	}

	for (i = 0; i < s_cnt; i++)
	{
		fprintf(fp, "%d %d %d %d %d %d %s\n", s_ary[i].num,
				s_ary[i].date.year, s_ary[i].date.month, s_ary[i].date.day,
				s_ary[i].startT, s_ary[i].endT, s_ary[i].note);
	}
	fclose(fp);
	printf("@ ���Ϸ� %d���� �������� ����߽��ϴ�!\n\n", s_cnt);
}
//  ������� �ϴ��� workshop4,  workshop3 ���� �����ߴ� �Լ��̴�.

//=======< ��� ���/����, �α���/�α׾ƿ� ���� �Լ� >=================================================

//---------------------------------------------------------------------------------------------------------------------------------------
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

	index = is_enroll_num(num, e_num, *e_cnt);     // ����� �Ǿ� �ִ��� Ȯ��

	if (index >= 0)                            // ��ϵ� ����� �ִ� ���
	{
		*e_cnt = deleteID(index, e_num, e_pwd, *e_cnt);
	}
	else                                          	// ó�� ����ϴ� ���
	{
		*e_cnt = insertID(num, e_num, e_pwd, *e_cnt);
	}

}


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

	for (i = dno; i < (e_cnt - 1); i++)
	{
		e_num[i] = e_num[i + 1];
		strcpy(e_pwd[i] ,e_pwd[i + 1]);
	}
	e_cnt--;										// ��ϵ� ��� �� ����
	return e_cnt;
}

int insertToIDList(int id, char* pwd, int *e_num, char (*e_pwd)[11], int e_cnt) {
	e_num[e_cnt] = id;
	strcpy(e_pwd[e_cnt], pwd);
	e_cnt++;                                   // ��ϵ� ��� �� ����
	printf("# %d���� ��ϵǾ����ϴ�!\n", id);
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

	if ((yn == 'Y') || (yn == 'y'))
	{
		//  ��й�ȣ�� �Է� �޾� ����� �´� ��й�ȣ�� ��� ���� ó��
		printf("> ��й�ȣ �Է� : "); OUT;
		my_gets(pwd, 10);    // �迭�� ũ������� �Է�
		if (strcmp(pwd, e_pwd[dno]) != 0 ) {
			printf("@ ��й�ȣ�� �ٸ��ϴ�. ������ �� �����ϴ�.\n");
			return e_cnt;
		}
		e_cnt = deleteFromIDList(dno, e_num, e_pwd, e_cnt);
		printf("@ %d���� ���� �Ǿ����ϴ�!\n", e_num[dno]);
		printIDList(e_num, e_pwd, e_cnt);
	} else {
		printf("@ ��� �Ǿ����ϴ�!\n");
	}
	return e_cnt;
}


int insertID(int id, int *e_num, char (*e_pwd)[11], int e_cnt){
	char pwd[11] = "";

	if (e_cnt == MAX_ARY)                          						// ����ο� ���� �ִ� �ο� ���� ������ ��ȯ
	{
		printf("@ ��� �ο��� �ʰ��Ǿ����ϴ�!");
		return e_cnt;
	}
	input_password(pwd);

	e_cnt = insertToIDList(id, pwd, e_num, e_pwd, e_cnt);
	printIDList(e_num, e_pwd, e_cnt);
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

// ��й�ȣ �Է�
void input_password(char *pwd)
{
	char first[11];      		// ù ��° �Է��� ��й�ȣ ����
	char second[11];       // ��й�ȣ ���ڿ� �Է��� �ӽ� �迭
	char *err_msg;      	 // �Է� �������� ������ ���� ���� ��� ����� ���� �޽���

	do {
		while (1)
		{
			printf("> ��й�ȣ(5-10��) : "); OUT;
			my_gets(first, 10);    // �迭�� ũ������� �Է�
			err_msg = verify_pwd(first);                 // ���ڿ� ���� �˻� �� ���� �޽��� ��ȯ
			if (err_msg == NULL) break;

			printf("@ %s\n", err_msg);
		}

		printf("> �ѹ� �� �Է��ϼ��� : "); OUT;
		my_gets(second, 10);
		if ( strcmp(first, second) == 0)   break;              // ù ��°�� �ι�° �Է� ���ڿ��� ������ ��

		printf("@ ��й�ȣ�� ��ġ���� �ʽ��ϴ�!\n");
	} while (1);
	my_strcpy(pwd, first);
}


// �迭�� ����� ���ڿ��� ���� ��ȯ
int my_strlen(char *sp)
{
	int cnt = 0;

	while (*sp++ != '\0')	{
		cnt++;
	}
	return cnt;
}

// ���ڿ� ���� �Լ�
void my_strcpy(char *dp, char *sp)
{
	while ( (*dp++ = *sp++) != '\0');
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
	fflush(stdin); gets(pwd);
	if (strcmp(pwd, e_pwd[index]) != 0)
	{
		printf("@ ��й�ȣ�� Ʋ�Ƚ��ϴ�!\n");
		return;
	}
	*login_num = num;                       // �α��� ��� ����
	printf("# �α��� �Ǿ����ϴ�!\n");
}

//=======< ���⼭ ���ʹ� �޷� ��� ���� �Լ� >=================================================

// ���� �˻� �Լ�
int leap_check(int year)
{
	if(year%4!=0) return 0;
	else if(year%100!=0) return 1;
	else if(year%400==0) return 1;
	else return 0;
}

// ����� ���� �ϼ� ���
int get_days(int year, int month)
{
	int days =0;
	days=mdays[month-1];
	if(leap_check(year) && month==2) ++days;  // �����̰� 2���̸� 29�Ϸ� ���
	return days;
}

// ���� ���ϴ� �Լ�
int get_weekday(int year, int month)
{
	int i, tot=0;

	// 1����� year-1�⵵������ �� �ϼ� ����
	for(i=1; i<year; i++){
		if(leap_check(i)) tot+=366;
		else tot+=365;
	}

	// 1������ month-1�� ������ �� �ϼ� ����
	for(i=0; i<month-1; i++){
		tot+=mdays[i];
	}

	// �����̰� ���� 3�� �̻��̸� 2���� 29���̹Ƿ� �Ϸ縦 ���Ѵ�.
	if(leap_check(year) && month>=3) tot++;

	// ����� 1���� ����
	tot++;

	return tot%7;  // ���� ��ġ ��ȯ
}

// �޷� ���
void disp_calendar(int year, int month)
{
	int i=0;
	int cnt=0; 			 // ���� ������ �� �ٿ� 7���� ����ϱ� ���� ����
	int start;                // 1���� ��µ� ���� ���� ��ġ
	int days;                // ��� ���� ������ ��

	start = get_weekday(year, month);                                          // 1���� ��µ� ���� ���� ��ġ ���
	days =get_days(year, month);

	printf("\n============< %4d. %2d >============\n\n", year, month);
	printf("------------------------------------\n");
	printf("%5s%5s%5s%5s%5s%5s%5s\n", "Sun","Mon","Tue","Wed","Thu","Fri","Sat");
	printf("------------------------------------\n");

	// �տ������� ���� ��ġ���� ���� ���
	for(i=0; i<start; i++){
		printf("%5c", ' ');
		cnt++;  // ���鵵 �� ���� �Ϻη� ī��Ʈ�Ѵ�.
	}

	// ��¥ ��� (1 ~ �� ���� ����� �� ��)
	for(i=1; i<=days; i++){
		if (on_schedule(year, month, i) > 0)
			printf("%3c%2d", '*', i);
		else
			printf("%5d", i);
		cnt++;  // ����� ������ ī��Ʈ
		if(cnt%7==0) printf("\n");  // �� �ٿ� 7���� ��µǸ� �� �ٲ۴�.
	}
	printf("\n");
	printf("------------------------------------\n");

}
