int mdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};

int main() {

	int year, month;
	int start;  		// 1일이 출력되는 시작위치를 맞추기 위한 변수  ( 0 ~ 6이 될 수 있으며, 0의 경우 일요일)
	int days;		// 각 월의 일 수를 저장할 변수

	// 입력 부분
	printf("# Input Year, Month : ");
	scanf("%d%d", &year, &month);


	// 출력할 년, 월에 해당하는 1일의 요일 계산
	start = get_weekday(year, month);
//	printf("%d", start);

	// 출력할 달의 일수 계산
	days = get_days(year, month);
//	printf("%d", days);

	// 달력 출력
	disp_calender(year, month, start, days);

	return 0;
}

int get_weekday(int year, int month)
{
	int ystart = 0;
	int i;
	for (i = 1; i < year; i++)
	{
		if (leap_check(i)) ystart += 2;
		else ystart += 1;
	}
	
	ystart += 1;
	ystart %= 7;
	
	for(i = 1; i < month; i++)
	{
		ystart += mdays[i-1] % 7;
	}
	if (month > 2 && leap_check(year) == 1) ystart += 1;
	return ystart % 7;
}

int get_days(int year, int month)
{
	if (month == 2 && (leap_check(year)) == 1) return 29;
	else return mdays[month - 1];
}

void disp_calender(int year, int month, int start, int days)
{
	printf("============< %d. %d >============\n", year, month);
	printf("------------------------------------\n");
	printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat \n");
	printf("------------------------------------\n");
	int i;
	int cnt = 0;
	cnt += start;
	
	for (i = 0; i < start; i++)
	{
		printf("     ");
	}
	for (i = 1; i <= days; i++)
	{
		printf("   %2d", i);
		cnt += 1;
		if (cnt == 7){
			printf("\n");
			cnt = 0;
		}
	}
	printf("\n------------------------------------\n");
}

// 윤년 검사 함수
int leap_check(int year)
{
	if(year%4!=0) return 0;
	else if(year%100!=0) return 1;
	else if(year%400==0) return 1;
	else return 0;
}

