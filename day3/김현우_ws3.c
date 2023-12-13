#include <stdio.h>

// ��� ���, �α��� �޴� ���� �Լ��� ����
//---------------------------------------------------------------
int disp_menu(void);
void enroll_num(void);
void login_out(void);
int is_enroll_num(int num);

int e_num[5];           	// ���
int e_pwd[5];          		// ��й�ȣ
int e_cnt;              		// ����ο� ��
int login_num = 0;      	// �α��� �Ǹ� ��� ����
int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };   // �� ���� �ϼ�

//-----------------------------------------------------------------

// �޷� ��� ���� �Լ�
//-----------------------------------------------------------------
int leap_check(int year);
int get_days(int year, int month);
int get_weekday(int year, int month);
void disp_calendar(int year, int month);
//-----------------------------------------------------------------

// ������ ���, ��ȸ ���� �Լ��� ����
//-----------------------------------------------------------------
void input_schedule(void);
int on_schedule(int year, int month, int day);
void search_schedule(void);

int s_day[100][4];      // �ִ� 100���� ������ ��¥ ����, ���, ��, ��, ��
int s_cnt = 0;             // ������ ��� ��
//-----------------------------------------------------------------

int main(void)
{
	int num;

	while (1)
	{
		num = disp_menu();
		if (num == 0) break;

		switch (num)
		{
		case 1:
			enroll_num(); break;
		case 2:
			login_out(); break;
		case 3:
			input_schedule();	break;
		case 4:
			search_schedule(); break;
		default:
			printf("@ �޴� ��ȣ�� �ƴմϴ�!\n\n");
			break;
		}
	}
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

	printf("> ��ȣ ���� : ");
	scanf("%d", &num);

	return num;
}


int get_checkRange(char* what, int min, int max) {
	int input = 0;
	printf("> %s(%d-%d) : ", what, min, max);
	scanf("%d", &input);
	if ((input < min) || (input > max))     // ��� ������ ���ڰ� �ƴϸ� ��ȯ
	{
		printf("@ ��ȿ�� ��ȣ�� �ƴմϴ�!\n");
		return -1;
	}
	return input;
}

void deleteFromIDList(int dno) {
	int i=0;

	for (i = dno; i <= (e_cnt - 1); i++)
	{
		e_num[i] = e_num[i + 1];
		e_pwd[i] = e_pwd[i + 1];
	}
	e_cnt--;										// ��ϵ� ��� �� ����
}

void insertToIDList(int id, int pwd) {
	e_num[e_cnt] = id;
	e_pwd[e_cnt] = pwd;
	e_cnt++;                                   // ��ϵ� ��� �� ����
	printf("# %d���� ��ϵǾ����ϴ�!\n", id);
}

void printIDList(){
	int i=0;

	printf("\n>> ���� ��ϵ� ���(��й�ȣ) : ");
	for (i = 0; i < e_cnt; i++)
	{
		printf("%5d(%d)", e_num[i], e_pwd[i]);
	}
	printf("\n\n");
}


void deleteID(int dno) {
	char yn = 0;

	printf("@ �̹� ��ϵǾ����ϴ�!\n");
	printf("@ ���� �Ͻðڽ��ϱ�(Y/N)?");

	fflush(stdin); 
	scanf("%c", &yn);
	if ((yn == 'Y') || (yn == 'y'))
	{
		deleteFromIDList(dno);
		printf("@ %d���� ���� �Ǿ����ϴ�!\n", e_num[dno]);
		printIDList();
	}
	else printf("@ ��� �Ǿ����ϴ�!\n");
}


void insertID(int id){
	int pwd = 0;
	int cnt =  sizeof(e_num) / sizeof(e_num[0]);    	// �ִ� ����ο� �� ���
	if (e_cnt == cnt)                          						// ����ο� ���� �ִ� �ο� ���� ������ ��ȯ
	{
		printf("@ ��� �ο��� �ʰ��Ǿ����ϴ�!");
		return;
	}
	pwd = get_checkRange("��й�ȣ", 0, 9999);
	if (pwd == 0)  return;
	insertToIDList(id, pwd);
	printIDList();
}

// ��� ��� / ����
void enroll_num(void)
{
	int num;                          			// ���
	int index;                                  // ����� �ִ� �迭�� ��ġ

	if (login_num != 0)                   // �̹� �α��� �� ���¸� ��ȯ
	{
		printf("@ �α׾ƿ� �� ����� �� �ֽ��ϴ�!\n");
		return;
	}

	printf("\n[ ��� ���/���� ]\n\n");
    // todo: ��� ��� / ���� �ڵ� �ۼ�
    num = get_checkRange("���", 1, 9999); 
	index = is_enroll_num(num);
	if (index != -1) deleteID(index);
	else insertID(num);
		
}

// �α��� / �α׾ƿ�
void login_out(void)
{
	int num, pwd;
	int index;

	// todo: �α���, �α׾ƿ� �ڵ� �ۼ�
	if (login_num != 0)
	{
		printf("# �α׾ƿ� �Ǿ����ϴ�!\n");
		login_num = 0;
	}
	else
	{
		printf("\n[ �α��� ]\n\n"); 
		printf("> ��� : ");
		scanf("%d", &num);
		index = is_enroll_num(num);
		if (index == -1)
		{
			printf("@ %d���� ��ϵ��� ���� ��ȣ�Դϴ�!", num);
		}
		else
		{
			printf("\n>��й�ȣ : ");
			scanf("%d", &pwd);
			if (e_pwd[index] != pwd) printf("@ ��й�ȣ�� Ʋ�Ƚ��ϴ�!\n");
			else
			{
				login_num = num;
				printf("# �α��� �Ǿ����ϴ�!\n");
			}
		}
	}
}

// ��ϵ� ��ȣ���� Ȯ��
int is_enroll_num(int num)
{
	int i;
	// todo: ��ϵ� ��ȣ���� Ȯ�� �ڵ� �ۼ�
	for(i=0; i<sizeof(e_num); i++)
	{
		if (e_num[i] == num) return i;
	}

	return -1;
}

// ȸ�ǽ� ���� ���
void input_schedule(void)
{
	int year, month, day;    // �������� �Է��� ��

	if (login_num == 0)      // �α��ε��� �ʾҴٸ� ��ȯ
	{
		printf("@ �α��� �� ����� �� �ֽ��ϴ�!\n");
		return;
	}

	printf("\n[ ȸ�ǽ� ���� ]\n\n");

	printf("> ��, �� �Է� : ");
	scanf("%d%d", &year, &month);
	// todo: ȸ�ǽ� ���� ��� �ڵ� �ۼ�
	disp_calendar(year, month);
	printf("��¥�� �����ϼ��� : ");
	scanf("%d", &day);
	 
	s_day[s_cnt][0] = login_num;
	s_day[s_cnt][1] = year;
	s_day[s_cnt][2] = month;
	s_day[s_cnt][3] = day;
	s_cnt += 1; 
	
	printf("@ ȸ�ǽ� ������ ��ϵǾ����ϴ�!\n");

}

// �ش� ��¥�� ���� ������ �� Ȯ��, ���� ��� 0 ��ȯ
int on_schedule(int year, int month, int day)
{
	int cnt = 0;
	int i;
    // todo: year, month, day�� �ش��ϴ� ������ �� ��ȯ
	for(i=0; i<s_cnt; i++)
	{
		if (s_day[i][1] == year && s_day[i][2] == month && s_day[i][3] == day) cnt += 1;
	}
	return cnt;
}

// ȸ�ǽ� ���� ���� ��ȸ
void search_schedule(void)
{
	int year, month, day;    // ���� ���¸� �˻��� ��
	int cnt;                		    // ���� �� ��

	if (login_num == 0)      // �α��ε��� �ʾҴٸ� ��ȯ
	{
		printf("@ �α��� �� ����� �� �ֽ��ϴ�.\n");
		return;
	}

	printf("\n[ ȸ�ǽ� ���� ���� ��ȸ ]\n\n");

	printf("> ��, �� �Է� : ");
	
	scanf("%d%d", &year, &month);
	// todo: ȸ�ǽ� ���� ���� Ȯ�� �ڵ� �ۼ�
	disp_calendar(year, month);
	printf("��¥�� �����ϼ��� : ");
	scanf("%d", &day);
	cnt = on_schedule(year, month, day);
	printf("@ %d���� ����� �������� �ֽ��ϴ�!\n", cnt);

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


