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
void add(rec *);
void view(rec *);
void update();
void delete();
void save(rec *);


void main()
{
	rec s;
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
				add(&s);
				break;
			case 2:
				view(&s);
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

void add(rec *s)
{
	FILE *fp;
	rec s1;
	int i,n;
	fp=fopen("record.txt","ab+");
	if(fp==NULL)
	{
		printf("Error opening file.");
		exit(1);
	}
	printf("Enter the following student details :");
	printf("\nName : ");
	fflush(stdin);
	fgets(s->name,sizeof(s->name),stdin);
	fflush(stdin);
	printf("\nRegistration No. : ");
	fscanf(stdin,"%s",s->regNum);
	while(fread(&s1,sizeof(s1),1,fp))
	{
		if(strcmp(s1.regNum,s->regNum)==0)
		{
			printf("Student record with registration no. %s already exists. ",s1.regNum);
			printf("Enter registration no. again : ");
			fflush(stdin);
			fscanf(stdin,"%s",s->regNum);
			rewind(fp);
		}
	}
	fclose(fp);
	printf("\nFaculty : ");
	fflush(stdin);
	fgets(s->faculty,sizeof(s->faculty),stdin);
	printf("\nSemester : ");
	scanf("%d",&s->sem);
	printf("\nAddress : ");
	fflush(stdin);
	fgets(s->addr,sizeof(s->addr),stdin);
	printf("Enter no. of subjects : ");
	scanf("%d",&n);
	s->sub=(struct subject *)calloc(n,sizeof(struct subject));
	if(s->sub == NULL)
	{
        printf("Memory allocation failed.");
        exit(1);
    }
	for(i=0;i<n;i++)
	{
		printf("\nName of Subject %d : ",i+1);
		fflush(stdin);
		fgets(((s->sub)+i)->subName,sizeof(((s->sub)+i)->subName),stdin);
		printf("\nMarks : ");
		scanf("%f",&((s->sub)+i)->marks);
		s->m.total+=(((s->sub)+i)->marks);
	}
	s->m.percent=s->m.total/n;
	save(s);
	free(s->sub);
}

void save(rec *s)
{
	FILE *fp;
	int i;
	fp=fopen("record.txt","ab");
	if(fp==NULL) 
	{
		printf("Error opening file.");
		exit(1);
	}
	if(fwrite(s,sizeof(s),1,fp))
	{
		printf("Successfully saved to file.");
	} else 
	{
		printf("Error writing into file.");
	}
	fclose(fp);
}

void view(rec *s)
{
	printf("%s\n%s",s->name,s->regNum);
}
