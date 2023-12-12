#include <stdio.h>

int main(void)
{
	int kor, eng, mat;
	kor = 3;
	eng = 5;
	mat = 4;
	
	int credits;
	int res;
	
	double kscore, escore, mscore;
	kscore = 3.8;
	escore = 4.4;
	mscore = 3.9;
	
	double grade;
	
	credits = kor + eng + mat;
	
	grade = (kscore + escore + mscore)/3;
	
	if(grade >= 4.0 && credits >= 10){
		res = 1;
	}
	else {
		res = 0;
	}
	
	return 0;
}
