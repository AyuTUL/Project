#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 100
void add();
void view();
void update();
void delete();
struct marks
{
	float c,iit,dl,phy,math;
};
struct student
{
	int roll;
	char name[MAX],addr[MAX],ph[MAX];
	struct marks m[MAX]; 
};
typedef struct student rec;
void main()
{
	char ch;
	int c;
	do
	{
		printf("Enter your choice :\n1. Add Student Record\n2. View Student Record\n3. Update Student Record\n4. Delete Student Record\n5. Exit\n");
		scanf("%d",c);
		switch(c)
		{
			case 1:
				add();
				break;
			case 2:
				view();
				break;
			case 3:
				update();
				break;
			case 4:
				delete();
				break;
			case 5:
				exit(0);
				break;
			default:
				printf("Invalid choice. Please choose from 1 - 5.");
		}
		printf("Do you want to continue? (Y/N) : ");
		ch=getche();
	}while(ch=='y' || ch=='Y');
}
