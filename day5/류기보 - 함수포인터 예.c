#include <stdio.h>

void func(void(*)(int*,int*));

void chicken(int*, int*);
void pizza(int*, int*);
void bread(int*, int*);

void main(void)
{
	int menu;
	
	do
	{
		printf("1> 치킨\n");
		printf("2> 피자\n");
		printf("3> 빵\n");
		printf(">> 메뉴 선택 (0: 종료)> ");
		scanf("%d", &menu);
		switch (menu)
		{
			case 1: func(chicken); break;
			case 2: func(pizza); break;
			case 3: func(bread); break;
		}
	} while (menu != 0);
}

void func(void(*menu)(int*,int*))
{
	int price;
	int calorie;
	menu(&price, &calorie);
	printf("\n가격: %d (칼로리: %d)\n\n", price, calorie);
}

void chicken(int* price, int* calorie)
{
	*price = 15000;
	*calorie = 10;
}

void pizza(int* price, int* calorie)
{
	*price = 30000;
	*calorie = 500;
}

void bread(int* price, int* calorie)
{
	*price = 3000;
	*calorie = 50;
}
