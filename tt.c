#include<stdio.h>
void main()
{
	int *x,y=30;
	x=&y;
	printf("%d",*x);
	y=1;
	printf("%d",*x);
}
