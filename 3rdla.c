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

struct marks
{
	float total,percent;
	char sch[5],gr[4];
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
void search();
void prin1(rec);
void prin2(rec);
void prin3(rec,int);
void prin4(rec,int);
void ascn(rec [],int);
void descn(rec [],int);
void prinTab(rec *,int);

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


void prin1(rec s)
{
	printf("%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %d\n%-17s: %s\n%-17s: %.2f %%\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Grade",s.m.gr,"Percentage",s.m.percent);
}

void prin2(rec s)
{
	printf("%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %s\n%-17s: %d\n%-17s: %s\n%-17s: N/A\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Grade",s.m.gr,"Percentage");
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
	strcpy(s.m.gr,"PASS");
	s.m.total=0;
	for(i=0;i<5;i++)
	{
		printf("Name of Subject %d : ",i+1);
		fflush(stdin);
		fgets(s.sub[i].subName,sizeof(s.sub[i].subName),stdin);
		printf("Marks : ");
		scanf("%f",&s.sub[i].marks);
		if(s.sub[i].marks<40)
		{
			strcpy(s.m.gr,"FAIL");
			s.m.percent=0;
			break;
		}
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
		if(strcmp(s.m.gr,"PASS")==0)
			prin1(s);
		else
			prin2(s);
	}
}

void viewFac(FILE *fp,char fac[],rec s)
{
	int c=0,ch,i;
	rec sfac[MAX];
	while(fread(&s,sizeof(rec),1,fp))
	{
		strupr(s.faculty);
		if(strcmp(s.faculty,fac)==0)
		{
			sfac[c]=s;
			c++;
		}
	}
	printf("1. View all Student Record\n2. Ascending by Name\n3. Descending by Name\n4. Ascending by Percentage\n5. Descending by Percentage");
	ch=confirm("\nEnter your choice : ");
	system("cls");
	switch(ch)
	{
		case '1':
			viewAll(fp,s);
			break;
		case '2':
			ascn(sfac,c);
			prinTab(sfac,c);
			break;
		case '3':
			descn(sfac,c);
			prinTab(sfac,c);
			break;
		case '4':
			//();
			break;
		case '5':
			//search();
			break;
		default:
			printf("Invalid choice. Please choose from 1 - 5.");
	}
}

void ascn(rec *s,int n)
{
	int i,j;
	rec temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(strcmp((s+j)->name,(s+j+1)->name)>0)
			{
				temp=*(s+j);
                *(s+j)=*(s+j+1);
                *(s+j+1)=temp;
			}
		}
	}
}

void descn(rec *s,int n)
{
	int i,j;
	rec temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(strcmp((s+j)->name,(s+j+1)->name)<0)
			{
				temp=*(s+j);
                *(s+j)=*(s+j+1);
                *(s+j+1)=temp;
			}
		}
	}
}

void prinTab(rec s[],int n)
{
	int i;
	printf("| %-20s | %-15s | %-16s | %-7s | %-8s | %-5s | %-10s |","Student Name","Address","Registration No.","Faculty","Semester","Grade","Percentage");
	for(i=0;i<n;i++)
	{
		if(strcmp(s[i].m.gr,"FAIL")==0)
			prin4(*(s+i),i);
		else
			prin3(*(s+i),i);
	}
}

void prin3(rec s,int i)
{
	printf("\n| %-20s | %-15s | %-16s | %-7s | %8d | %-5s | %8.2f %% |",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,s.m.percent);
}

void prin4(rec s,int i)
{
	printf("\n| %-20s | %-15s | %-16s | %-7s | %ds | %-5s | %8s |",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,"N/A");
}

void view()
{
	FILE *fp;
	rec s;
	int c,ch;
	fp=open("record.txt","rb");
	printf("1. View all Student Record\n2. View Student Record according to Faculty");
	c=confirm("\nEnter your choice : ");
	switch(c)
	{
		case '1':
			system("cls");
			viewAll(fp,s);
			break;
		case '2':
			printf("\n\n1. CSIT\n2. BIM\n3. BHM");
			ch=confirm("\nEnter your choice : ");
			system("cls");
			switch(ch)
			{
				case '1':
					viewFac(fp,"CSIT\n",s);
					break;
				case '2':
					viewFac(fp,"BIM\n",s);
					break;
				case '3':
					viewFac(fp,"BHM\n",s);
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
			printf("%-17s: %s%-17s: %s%-17s: %s\n%-17s: %s%-17s: %d\n%-17s: %.2f %%\n\n","Name",s.name,"Address",s.addr,"Registration No.",s.regNum,"Faculty",s.faculty,"Semester",s.sem,"Percentage",s.m.percent);	
		}
	}
	if(flag==0)
	{
		printf("Record not found.");
	}
	fclose(fp);
}
