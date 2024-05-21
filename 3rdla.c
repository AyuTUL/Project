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
	struct subject sub[5];
	struct marks m; 
};

typedef struct student rec;

char confirm(char []);
void create();
rec add(FILE *);
void view();
void update();
void del();
void save(char [],rec);
FILE* open(char [],char []);
void remo(char []);
void rena(char [],char []);
void viewAll(FILE *,rec);
void viewFac(FILE *,char [],rec);

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
				create();
				break;
			case 2:
				view();
				break;
			case 3:
				update();
				break;
			case 4:
				del();
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

void remo(char fn[])
{
	int err;
	err=remove("record.txt");
	if(err!=0)
	{
		printf("Error deleting file.");
		exit(1);
	}
}

void rena(char old[],char newn[])
{
	int err;
	err=rename(old,newn);
	if(err!=0)
	{
		printf("Error renaming file.");
		exit(1);
	}
}

char confirm(char s[])
{
	char ch;
	printf("\n%s",s);
	return(getche());
}

FILE* open(char fn[],char mode[])
{
	FILE *fp;
	fp=fopen(fn,mode);
	if(fp==NULL)
	{
		printf("Error opening file.");
		exit(1);
	}
	return(fp);
}

void create()
{
	FILE *fp;
	rec s;
	fp=open("record.txt","ab+");
	printf("Enter the following student details :\n");
	s=add(fp);
	save("record.txt",s);
	printf("File Successfully saved.");
}

rec add(FILE *fp)
{
	rec s,temp;
	int i;
	printf("Registration No. : ");
	fscanf(stdin,"%s",s.regNum);
	while(fread(&temp,sizeof(rec),1,fp))
	{
		while(!strcmp(temp.regNum,s.regNum))
		{
			printf("Student record with registration no. %s already exists.\nEnter registration no. again : ",s.regNum);
			fflush(stdin);
			fscanf(stdin,"%s",s.regNum);
			rewind(fp);
		}
	}
	fclose(fp);
	printf("Name : ");
	fflush(stdin);
	fgets(s.name,sizeof(s.name),stdin);
	printf("Faculty : ");
	fflush(stdin);
	fgets(s.faculty,sizeof(s.faculty),stdin);
	printf("Semester : ");
	scanf("%d",&s.sem);
	printf("Address : ");
	fflush(stdin);
	fgets(s.addr,sizeof(s.addr),stdin);
	for(i=0;i<5;i++)
	{
		printf("Name of Subject %d : ",i+1);
		fflush(stdin);
		fgets(s.sub[i].subName,sizeof(s.sub[i].subName),stdin);
		printf("Marks : ");
		scanf("%f",&s.sub[i].marks);
		s.m.total+=s.sub[i].marks;
	}
	s.m.percent=s.m.total/5;
	return(s);
}

void save(char fn[],rec s)
{
	FILE *fp;
	int i;
	fp=open(fn,"ab");
	if(!fwrite(&s,sizeof(s),1,fp))
		printf("Error writing into file.");
	fclose(fp);
}

void viewAll(FILE *fp,rec s)
{
	while(fread(&s,sizeof(rec),1,fp))
	{
		printf("%-17s: %s%-17s: %s%-17s: %s\n%-17s: %s%-17s: %d\n%-17s: %.2f %%\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Percentage",s.m.percent);
	}
}

void viewFac(FILE *fp,char fac[],rec s)
{
	puts(fac);
	while(fread(&s,sizeof(rec),1,fp))
	{
		//strupr(s.faculty);
		puts(s.faculty);
		if(strcmp(s.faculty,fac)==0)
		{
			puts("goo");
			printf("%-17s: %s%-17s: %s%-17s: %s\n%-17s: %s%-17s: %d\n%-17s: %.2f %%\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Percentage",s.m.percent);
		}
	}
}
void view()
{
	FILE *fp;
	rec s;
	int c,ch;
	fp=open("record.txt","rb");
	printf("1. View all Student Record\n2. View Student Record according to Faculty\nEnter your choice : ");
	scanf("%d",&c);
	system("cls");
	switch(c)
	{
		case 1:
			viewAll(fp,s);
			break;
		case 2:
			printf("1. CSIT\n2. BIM\n3. BHM\nEnter your choice : ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					viewFac(fp,"CSIT",s);
					break;
				case 2:
					viewFac(fp,"BIM",s);
					break;
				case 3:
					viewFac(fp,"BHM",s);
					break;
				default:
					printf("Invalid choice. Please choose between 1-3.");
			}
			break;
		default:
			printf("Invalid choice. Please choose between 1 & 2.");
	}
	fclose(fp);
}

void update()
{
	FILE *fp1,*fp2;
	rec s1;
	char reg[100];
	int flag=0;
	fp1=open("record.txt","rb");
	fp2=open("temp.txt","wb");
	printf("Enter Registration No. of student record to be updated : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s1,sizeof(rec),1,fp1))
	{
		if(strcmp(reg,s1.regNum)==0)
		{
			printf("Enter new details :\n");
			s1=add(fp2);
			flag=1;		
		}
		save("temp.txt",s1);
	}
	if(flag==0)
	{
		printf("Record not found.");
	}
	else
	{
		printf("File successfully saved.");
	}
	fclose(fp2);
	fclose(fp1);
	remo("record.txt");
	rena("temp.txt","record.txt");
}

void del()
{
	FILE *fp1,*fp2;
	rec s1;
	char reg[100];
	int flag=0;
	fp1=open("record.txt","rb");
	fp2=open("temp.txt","wb");
	printf("Enter Registration No. of student record to be deleted : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s1,sizeof(rec),1,fp1))
	{
		if(strcmp(reg,s1.regNum)==0)
		{
			flag=1;
			continue;	
		}
		save("temp.txt",s1);
	}
	if(flag==0)
	{
		printf("Record not found.");
	}
	else
	{
		printf("File successfully deleted.");
	}
	fclose(fp2);
	fclose(fp1);
	remo("record.txt");
	rena("temp.txt","record.txt");
}
