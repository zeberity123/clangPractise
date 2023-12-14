#include <stdio.h>
void sub(char**);
int main()
{
	char *sary[4] = {"tromm", "dios", "whisen", "optimus"};
	sub(sary);
	return 0;
}
void sub(char **sp)
{
	printf("%s\n", sp[0]);
	printf("%s\n", *(sp+1));
	printf("%c\n", *(*(sp+2)+3));
	printf("%c\n", sp[0][4]);
}
