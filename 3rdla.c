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

struct marks
{
	float total,percent;
	char gr[5];
};

struct student
{
	int sem;
	char name[MAX],addr[MAX],regNum[MAX],faculty[MAX];
	struct subject sub[5];
	struct marks m; 
};

typedef struct student rec;

// Function prototypes
FILE* open(char [],char []);
rec add(FILE *);
char confirm(char []);
void create();
void del();
char* grade(struct subject []);
void printCheck(rec);
void prinHead();
void prinTab(rec [],int);
void prinTabFail(rec);
void prinTabPass(rec);
int passFail(rec [],char [],int);
void remo(char []);
void rena(char [],char []);
void save(char [],rec);
void search();
void sort(rec [],int,char);
void swap(rec *,rec *);
void update();
void view();
void viewFac(FILE *,char [],rec);

void main()
{
	char ch;
	int c;
	do
	{
		system("cls");
		printf("1. Add Student Record\n2. View Student Record\n3. Update Student Record\n4. Delete Student Record\n5. Search Student Record\n6. Exit\nEnter your choice : ");
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
				search();
				break;
			case 6:
				printf("Thank you for using the program.");
				exit(0);
				break;
			default:
				printf("Invalid choice. Please choose from 1 - 5.");
		}
		ch=confirm("\nDo you want to continue? [Y/N] : ");
	}while(ch=='y' || ch=='Y');
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
	strtok(s.name,"\n");
	printf("Faculty : ");
	fgets(s.faculty,sizeof(s.faculty),stdin);
	strtok(s.faculty,"\n");
	printf("Semester : ");
	scanf("%d",&s.sem);
	printf("Address : ");
	fflush(stdin);
	fgets(s.addr,sizeof(s.addr),stdin);
	strtok(s.addr,"\n");
	s.m.total=0;
	for(i=0;i<5;i++)
	{
		printf("Name of Subject %d : ",i+1);
		fflush(stdin);
		fgets(s.sub[i].subName,sizeof(s.sub[i].subName),stdin);
		strtok(s.sub[i].subName,"\n");
		printf("Marks : ");
		scanf("%f",&s.sub[i].marks);
		s.m.total+=s.sub[i].marks;
	}
	strcpy(s.m.gr,grade(s.sub));
	if(strcmp(s.m.gr,"PASS")==0)
		s.m.percent=s.m.total/5;
	return(s);
}

char* grade(struct subject s[])
{
	int i;
	for(i=0;i<5;i++)
	{
		if(s[i].marks<40)
			break;
	}
	if(i<5)
		return("FAIL");
	else
		return("PASS");
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
	printf("\n%s",s);
	return(getche());
}

void save(char fn[],rec s)
{
	FILE *fp;
	int i;
	fp=open(fn,"ab");
	if(fwrite(&s,sizeof(s),1,fp)!=1)
		printf("Error writing into file.");
	fclose(fp);
}

void printCheck(rec s)
{
	if(strcmp(s.m.gr,"PASS")==0)
		printf("%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %d\n%-17s: %s\n%-17s: %.2f %%\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Grade",s.m.gr,"Percentage",s.m.percent);
	else
		printf("%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %d\n%-17s: %s\n%-17s: N/A\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Grade",s.m.gr,"Percentage");
}

void sort(rec sfac[],int n,char c)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			switch(c)
			{
				case '2':
				case '6':
				case '7':
					if(strcmp((sfac+j)->name,(sfac+j+1)->name)>0)
						swap(&sfac[j],&sfac[j+1]);
					break;
				case '3':
					if(strcmp((sfac+j)->name,(sfac+j+1)->name)<0)
						swap(&sfac[j],&sfac[j+1]);
					break;
				case '4':
					if((sfac+j)->m.percent>(sfac+j+1)->m.percent)
						swap(&sfac[j],&sfac[j+1]);
					break;
				case '5':
					if((sfac+j)->m.percent<(sfac+j+1)->m.percent)
						swap(&sfac[j],&sfac[j+1]);
					break;		
			}
		}
	}
}

void viewFac(FILE *fp,char fac[],rec s)
{
	int c=0,ch,i,j,cpass;
	rec sfac[MAX],spass[MAX];
	strupr(fac);
	while(fread(&s,sizeof(rec),1,fp))
	{
		strupr(s.faculty);
		if(strcmp(s.faculty,fac)==0)
		{
			sfac[c]=s;
			c++;
		}
	}
	printf("\n1. View all Student Record\n2. Ascending by Name\n3. Descending by Name\n4. Ascending by Percentage\n5. Descending by Percentage\n6. Passed Students\n7. Failed Students");
	ch=confirm("\nEnter your choice : ");
	system("cls");
	switch(ch)
	{
		case '1':
			for(i=0;i<c;i++)
			{
				printCheck(sfac[i]);
			}
			break;
		case '2':
		case '3':
			sort(sfac,c,ch);
			prinTab(sfac,c);
			break;
		case '4':
		case '5':
			cpass=passFail(sfac,"PASS",c);
			sort(sfac,cpass,ch);
			prinTab(sfac,cpass);
			break;
		case '6':
			cpass=passFail(sfac,"PASS",c);
			sort(sfac,cpass,ch);
			prinHead();
			for(i=0;i<cpass;i++)
			{
				prinTabPass(sfac[i]);
			}
			break;
		case '7':
			cpass=passFail(sfac,"FAIL",c);
			sort(sfac,cpass,ch);
			prinHead();
			for(i=0;i<cpass;i++)
			{
				prinTabPass(sfac[i]);
			}
			break;
		default:
			printf("Invalid choice. Please choose from 1 - 5.");
	}
}



void swap(rec *a,rec *b)
{
	rec temp;
	temp=*a;
    *a=*b;
    *b=temp;
}

int passFail(rec sfac[],char grade[],int c)
{
	int i,cpass=0;
	for(i=0;i<c;i++)
	{
		if(strcmp(sfac[i].m.gr,grade)==0)
		{
			sfac[cpass]=sfac[i];
			cpass++;
		}
	}
	return(cpass);
}

void prinHead()
{
	int i;
	printf("| %-20s | %-15s | %-16s | %-7s | %-8s | %-5s | %-10s |\n","Student Name","Address","Registration No.","Faculty","Semester","Grade","Percentage");
	for(i=0;i<103;i++)
		printf("-");
}

void prinTabPass(rec s)
{
	printf("\n| %-20s | %-15s | %-16s | %-7s | %8d | %-5s | %8.2f %% |",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,s.m.percent);
}

void prinTabFail(rec s)
{
	printf("\n| %-20s | %-15s | %-16s | %-7s | %8d | %-5s | %10s |",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,"N/A");
}

void prinTab(rec s[],int n)
{
	int i;
	prinHead();
	for(i=0;i<n;i++)
	{
		if(strcmp(s[i].m.gr,"PASS")==0)
			prinTabPass(s[i]);
		else
			prinTabFail(s[i]);
	}
}

void view()
{
	FILE *fp;
	rec s;
	int c;
	char fac[5];
	fp=open("record.txt","rb");
	printf("1. View all Student Record\n2. View Student Record according to Faculty");
	c=confirm("\nEnter your choice : ");
	switch(c)
	{
		case '1':
			system("cls");
			while(fread(&s,sizeof(rec),1,fp))
			{
				printCheck(s);
			}
			break;
		case '2':
			printf("\n\nEnter Faculty : ");
            fflush(stdin);
            fgets(fac,sizeof(fac),stdin);
            strtok(fac,"\n");
            viewFac(fp,fac,s);
			break;
		default:
			printf("\nInvalid choice. Please choose between 1 & 2.");
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
			flag=1;	
			printf("Enter new details :\n");
			s1=add(fp2);	
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
		printf("Record successfully deleted.");
	}
	fclose(fp2);
	fclose(fp1);
	remo("record.txt");
	rena("temp.txt","record.txt");
}

void search()
{
	FILE *fp;
	rec s;
	char reg[100];
	int flag=0;
	fp=open("record.txt","rb");
	printf("Enter Registration No. of student record to be searched : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s,sizeof(rec),1,fp))
	{
		if(strcmp(reg,s.regNum)==0)
		{
			flag=1;
			printCheck(s);
		}
	}
	if(flag==0)
	{
		printf("Record not found.");
	}
	fclose(fp);
}
