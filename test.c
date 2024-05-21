//Student Record Management System

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

struct subject
{
	char subName[MAX];
	float marks;
};

struct marks {
	float total;
	float percent;
};

struct student
{
	int sem;
	char name[MAX],addr[MAX],regNum[MAX],faculty[MAX];
	struct subject *sub;
	struct marks m; 
};

typedef struct student rec;

char confirm(char []);
void add();
void view();
void update();
void del();
void save(char [],rec);


void main()
{
	char ch;
	int c;
	do
	{
		system("cls");
		printf("1. Add Student Record\n2. View Student Record\n3. Update Student Record\n4. Delete Student Record\n5. Exit\nEnter your choice : ");
		scanf("%d",&c);
		system("cls");
		switch(c)
		{
			case 1:
				add();
				break;
			case 2:
				view();
				break;
			case 3:
				//update();
				break;
			case 4:
				//delete();
				break;
			case 5:
				printf("Thank you for using the program.");
				exit(0);
				break;
			default:
				printf("Invalid choice. Please choose from 1 - 5.");
		}
		ch=confirm("Do you want to continue? [Y/N] : ");
	}while(ch=='y' || ch=='Y');
}

char confirm(char s[])
{
	char ch;
	printf("\n%s",s);
	return(getche());
}

void add()
{
	FILE *fp;
	rec s1,s;
	int i,n;
	fp=fopen("record.txt","rb+");
	if(fp==NULL)
	{
		printf("Error opening file.");
		exit(1);
	}
	printf("Enter the following student details :\n");
	fflush(stdin);
	printf("Registration No. : ");
	gets(s.regNum);
	while(fread(&s1,sizeof(rec),1,fp))
	{
		printf("Existing Registration No.: %s\n", s1.regNum); // Diagnostic message
        printf("Entered Registration No.: %s\n", s.regNum);
		while(!strcmp(s1.regNum,s.regNum))
		{
			printf("Student record with registration no. %s already exists. ",s1.regNum);
			printf("Enter registration no. again : ");
			fflush(stdin);
			gets(s.regNum);
			rewind(fp);
		}
	}
	fclose(fp);
	printf("Name : ");
	fflush(stdin);
	gets(s.name);
	printf("Faculty : ");
	fflush(stdin);
	gets(s.faculty);
	printf("Semester : ");
	scanf("%d",&s.sem);
	printf("Address : ");
	fflush(stdin);
	gets(s.addr);
	printf("Enter no. of subjects : ");
	scanf("%d",&n);
	s.sub=(struct subject *)calloc(n,sizeof(struct subject));
	if(s.sub==NULL)
	{
        printf("Memory allocation failed.");
        exit(1);
    }
	for(i=0;i<n;i++)
	{
		printf("Name of Subject %d : ",i+1);
		fflush(stdin);
		gets(s.sub[i].subName);
		printf("Marks : ");
		scanf("%f",&s.sub[i].marks);
		s.m.total+=s.sub[i].marks;
	}
	s.m.percent=s.m.total/n;
	save("record.txt",s);
	for (i = 0; i < n; i++) 
	{
    free(s.sub[i].subName);
	}
	free(s.sub);
}

void save(char fn[],rec s)
{
	FILE *fp;
	int i;
	fp=fopen(fn,"ab");
	if(fp==NULL) 
	{
		printf("Error opening file.");
		exit(1);
	}
	if(fwrite(&s,sizeof(s),1,fp))
	{
		printf("Successfully saved to file.");
	} else 
	{
		printf("Error writing into file.");
	}
	fclose(fp);
}

void view()
{
	FILE *fp;
	rec s1;
	fp=fopen("record.txt","r");
	if(fp==NULL) 
	{
		printf("Error opening file.");
		exit(1);
	}
	while(fread(&s1,sizeof(rec),1,fp))
	{
		printf("%s",s1.addr);
		printf("%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %d\n%-17s: %.2f %%\n","Name",s1.name,"Address",s1.addr,"Registration No.",s1.regNum,"Faculty",s1.faculty,"Semester",s1.sem,"Percentage",s1.m.percent);
	}
	fclose(fp);
}