#include<stdio.h>
void main()
{
	int a[]={-23,-124,-0,234,-234,-3,-5,5};
	int i,s,l;
	l=s=a[0];
	for(i=1;i<8;i++)
	{
		if(a[i]>l)
		{
			s=l;
			l=a[i];
		}
		else if(a[i]>s && a[i]!=l)
		{
			s=a[i];
		}
	}
	printf("%d",s);
}
