#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX 100

struct subject {
	float marks;
};

struct marks {
	float total,percent;
	char gr[5];
};

struct student {
	int sem,subNum;
	char name[MAX],addr[MAX],regNum[MAX],faculty[MAX];
	struct subject *sub;
	struct marks m; 
};

typedef struct student rec;

// Cursor Position
int *posx,*posy;

// Function prototypes
FILE* openFile(char [],char []);
rec add(FILE *);
char confirm(char [],int *,int *);
void create();
void dash();
void dashTab();
void del();
void gotoxy(int,int);
char* grade(struct subject [],int);
void printCheck(rec,int);
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

void main() {
	char ch,c;
	int x,y;
	posx=&x;
	posy=&y;
	do {
		system("cls");
		x=35;
		y=6;
		gotoxy(20,4);
		dash();
		gotoxy(x,++y);
		printf("|\tStudent Record Management System\t|");
		gotoxy(x,++y);
		dash();
		gotoxy(x,y+=3);
		printf("1. Add Student Record");
		gotoxy(x,++y);
		printf("2. View Student Record");
		gotoxy(x,++y);
		printf("3. Update Student Record");
		gotoxy(x,++y);
		printf("4. Delete Student Record");
		gotoxy(x,++y);
		printf("5. Search Student Record");
		gotoxy(x,++y);
		printf("6. Exit program");
		y+=2;
		c=confirm("Which operation do you want to perform? [1-6] : ",&x,&y);
		system("cls");
		switch(c) {
			case '1':
				create();
				break;
			case '2':
				view();
				break;
			case '3':
				update();
				break;
			case '4':
				del();
				break;
			case '5':
				search();
				break;
			case '6':
				gotoxy(x,8);
				dash();
				gotoxy(45,12);
				printf("Thank you for using the program.");
				gotoxy(x,14);
				dash();
				exit(0);
				break;
			default:
				gotoxy(15,7);
				printf("Invalid choice. Please choose from 1 - 5.");
				*posy=10;
		}
		(*posy)++;
		*posx=15;
		ch=confirm("Do you want to continue? [Y/N] : ",posx,posy);
	}while(ch=='y' || ch=='Y');
}

void dash() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width,i;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi)) {
        printf("Error getting console screen buffer info.\n");
        return;
    }
    width=csbi.dwSize.X;
    putchar('\n');
    for (i=0;i<width;i++) {
        putchar('-');
    }
    printf("\n\n");
    fflush(stdout);
}

void create() {
	FILE *fp;
	int x=35,y=5;
	rec s;
	fp=openFile("record.txt","ab+");
	gotoxy(x,y);
	printf("Enter the following student details :");
	s=add(fp);
	save("record.txt",s);
	gotoxy(x,*posy);
	printf("File Successfully saved.");
	*(posy)+=2;
}

FILE* openFile(char fn[],char mode[]) {
	FILE *fp;
	fp=fopen(fn,mode);
	if(fp==NULL) {
		printf("Error opening file.");
		exit(1);
	}
	return(fp);
}

rec add(FILE *fp)
{
	rec s,temp;
	int i,x=35,y=7;
	gotoxy(x,y);
	printf("Registration No. : ");
	fscanf(stdin,"%s",s.regNum);
	while(fread(&temp,sizeof(rec),1,fp)) {
		while(!strcmp(temp.regNum,s.regNum)) {
			gotoxy(x=28,y+=2);
			printf("Student record with Registration No. %s already exists.",s.regNum);
			gotoxy(x=35,y+=2);
			printf("Enter registration no. again : ");
			fflush(stdin);
			fscanf(stdin,"%s",s.regNum);
			rewind(fp);
		}
	}
	fclose(fp);
	gotoxy(x,++y);
	printf("Name : ");
	fflush(stdin);
	fgets(s.name,sizeof(s.name),stdin);
	strtok(s.name,"\n");
	gotoxy(x,++y);
	printf("Faculty : ");
	fgets(s.faculty,sizeof(s.faculty),stdin);
	strtok(s.faculty,"\n");
	gotoxy(x,++y);
	printf("Semester : ");
	scanf("%d",&s.sem);
	gotoxy(x,++y);
	printf("Address : ");
	fflush(stdin);
	fgets(s.addr,sizeof(s.addr),stdin);
	strtok(s.addr,"\n");
	gotoxy(x,++y);
	printf("Enter no. of subjects : ");
	scanf("%d",&s.subNum);
	s.m.total=0;
	s.sub=(struct subject *)malloc(s.subNum*sizeof(struct subject));
	if(s.sub==NULL) {
		gotoxy(x,++y);
		printf("Memory allocation failed.");
		exit(1);
	}
	gotoxy(x,++y);
	printf("Enter marks in %d subjects:\n",s.subNum);
	for(i=0;i<s.subNum;i++) {
		gotoxy(x,++y);
		printf("For subject %d : ",i+1);
		scanf("%f",&s.sub[i].marks);
		s.m.total+=s.sub[i].marks;
	}
	strcpy(s.m.gr,grade(s.sub,s.subNum));
	if(strcmp(s.m.gr,"PASS")==0)
		s.m.percent=s.m.total/s.subNum;
	y+=3;
	*posy=y;
	*posx=x;
	return(s);
}

char* grade(struct subject s[],int n) {
	int i;
	for(i=0;i<n;i++) {
		if(s[i].marks<40)
			break;
	}
	if(i<n)
		return("FAIL");
	else
		return("PASS");
}

void remo(char fn[]) {
	if(remove(fn)!=0) {
		printf("Error deleting file.");
		exit(1);
	}
}

void rena(char old[],char newn[]) {
	if(rename(old,newn)!=0) {
		printf("Error renaming file.");
		exit(1);
	}
}

char confirm(char s[],int *x,int *y) {
	char c;	
	gotoxy(*x,*y);
	printf("%s",s);
	scanf(" %c",&c);
	return(c);
}

void save(char fn[],rec s) {
	FILE *fp;
	fp=openFile(fn,"ab");
	if(fwrite(&s,sizeof(s),1,fp)!=1)
		printf("Error writing into file.");
	free(s.sub);
	fclose(fp);
}

void printCheck(rec s,int y) {
	int x=15;
	dash();
	gotoxy(x,++y);
	printf("%-17s: %s","Name",s.name);
	gotoxy(x,++y);
	printf("%-17s: %s","Address",s.addr);
	gotoxy(x,++y);
	printf("%-17s: %s","Registration No.",s.regNum);
	gotoxy(x,++y);
	printf("%-17s: %s","Faculty",s.faculty);
	gotoxy(x,++y);
	printf("%-17s: %d","Semester",s.sem);
	gotoxy(x,++y);
	printf("%-17s: %s","Grade",s.m.gr);
	gotoxy(x,++y);
	if(strcmp(s.m.gr,"PASS")==0)
		printf("%-17s: %.2f %%\n","Percentage",s.m.percent);
	else
		printf("%-17s: N/A\n","Percentage");
}

void sort(rec sfac[],int n,char c) {
	int i,j;
	for(i=0;i<n;i++) {
		for(j=0;j<n-i-1;j++) {
			switch(c) {
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

void viewFac(FILE *fp,char fac[],rec s) {
	int c=0,i,j,cpass,x=35,y=6;
	char ch;
	rec sfac[MAX],spass[MAX];
	strupr(fac);
	while(fread(&s,sizeof(rec),1,fp)) {
		strupr(s.faculty);
		if(strcmp(s.faculty,fac)==0)
		{
			sfac[c]=s;
			c++;
		}
	}
	gotoxy(x,y);
	printf("1. View all Student Record");
	gotoxy(x,++y);
	printf("2. Ascending by Name");
	gotoxy(x,++y);
	printf("3. Descending by Name");
	gotoxy(x,++y);
	printf("4. Ascending by Percentage");
	gotoxy(x,++y);
	printf("5. Descending by Percentage");
	gotoxy(x,++y);
	printf("6. Passed Students");
	gotoxy(x,++y);
	printf("7. Failed Students");
	y+=2;
	ch=confirm("Enter your choice : ",&x,&y);
	system("cls");
	switch(ch) {
		case '1':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty :\n",fac);
			y=-6;
			for(i=0;i<c;i++)
			{
				printCheck(sfac[i],y+=10);
			}
			dash();
			y+=2;
			*posy=y;
			break;
		case '2':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty in ascending order by name :\n",fac);
			goto sortName;
		case '3':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty in descending order by name :\n",fac);
			sortName:
			sort(sfac,c,ch);
			prinTab(sfac,c);
			break;
		case '4':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty in ascending order by percentage :\n",fac);
			cpass=passFail(sfac,"PASS",c);
			goto Sort;
		case '5':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty in descending order by percentage :\n",fac);
			cpass=passFail(sfac,"PASS",c);
			goto Sort;
			break;
		case '6':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty who passed :\n",fac);
			cpass=passFail(sfac,"PASS",c);
			goto Sort;
		case '7':
			gotoxy(15,1);
			printf("Displaying all student records of %s faculty who failed :\n",fac);
			cpass=passFail(sfac,"FAIL",c);
			Sort:
			sort(sfac,cpass,ch);
			prinTab(sfac,cpass);
			break;
		default:
			gotoxy(15,7);
			printf("Invalid choice. Please choose from 1 - 5.");
			*posy=2;
	}
}

void gotoxy(int x,int y) {
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole==INVALID_HANDLE_VALUE) {
        printf("Error getting console handle.");
        exit(1);
	}
    COORD cursorPos;
    cursorPos.X=x;
    cursorPos.Y=y;
    if(!SetConsoleCursorPosition(hConsole,cursorPos)) {
        printf("Error setting console cursor position.");
        exit(1);
    }
}

void swap(rec *a,rec *b) {
	rec temp;
	temp=*a;
    *a=*b;
    *b=temp;
}

int passFail(rec sfac[],char grade[],int c) {
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

void dashTab() {
	int i;
	for(i=0;i<103;i++)
		printf("-");
	printf("\n");
}

void prinHead() {
	printf("| %-20s | %-15s | %-16s | %-7s | %-8s | %-5s | %-10s |\n","Student Name","Address","Registration No.","Faculty","Semester","Grade","Percentage");	
}

void prinTabPass(rec s) {
	printf("| %-20s | %-15s | %-16s | %-7s | %8d | %-5s | %8.2f %% |\n",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,s.m.percent);
}

void prinTabFail(rec s) {
	printf("| %-20s | %-15s | %-16s | %-7s | %8d | %-5s | %10s |\n",s.name,s.addr,s.regNum,s.faculty,s.sem,s.m.gr,"N/A");
}

void prinTab(rec s[],int n) {
	int i,y=6,x=8;
	gotoxy(x,3);
	dashTab();
	gotoxy(x,4);
	prinHead();
	gotoxy(x,5);
	dashTab();
	for(i=0;i<n;i++) {
		gotoxy(x,y);
		if(strcmp(s[i].m.gr,"PASS")==0)
			prinTabPass(s[i]);
		else
			prinTabFail(s[i]);
		y++;
	}
	gotoxy(x,y);
	dashTab();
	y-=7;
	*posy=y;
}

void view() {
	FILE *fp;
	rec s;
	int x=35,y=6;
	char c,fac[5];
	fp=openFile("record.txt","rb");
	gotoxy(x,++y);
	printf("1. View all Student Record");
	gotoxy(x,++y);
	printf("2. View Student Record according to Faculty");
	fflush(stdin);
	y+=2;
	c=confirm("Enter your choice [1-2]: ",&x,&y);
	system("cls");
	switch(c) {
		case '1':
			y=1;
			gotoxy(15,y);
			printf("Displaying all student records :\n");
			y=-6;
			while(fread(&s,sizeof(rec),1,fp)) {
				printCheck(s,y+=10);
			}
			y+=10;
			dash();
			*posy=y;
			break;
		case '2':
			gotoxy(35,4);
			printf("Enter Faculty : ");
            fflush(stdin);
            fgets(fac,sizeof(fac),stdin);
            strtok(fac,"\n");
            viewFac(fp,fac,s);
            *(posy)+=8;
			break;
		default:
			gotoxy(15,7);
			printf("Invalid choice. Please choose from 1 & 2.");
			*posy=10;
	}
	*posx=25;
	fclose(fp);
}

void update()
{
	FILE *fp1,*fp2;
	rec s1;
	char reg[100];
	int flag=0,x=25,y=4;
	fp1=openFile("record.txt","rb");
	fp2=openFile("temp.txt","wb");
	gotoxy(x,y);
	printf("Enter Registration No. of student record to be updated : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s1,sizeof(rec),1,fp1)) {
		if(strcmp(strupr(reg),strupr(s1.regNum))==0) {
			flag=1;
			gotoxy(x,++y);	
			printf("Enter new details :\n\n");
			s1=add(fp2);	
		}
		save("temp.txt",s1);
	}
	if(flag==0) {
		gotoxy(x,y+=3);
		printf("Record not found.");
	}
	else {
		gotoxy(x,y+=15);
		printf("File successfully saved.");
	}
	fclose(fp2);
	fclose(fp1);
	remo("record.txt");
	rena("temp.txt","record.txt");
	y+=2;
	*posy=y;
	*posx=x;	
}

void del()
{
	FILE *fp1,*fp2;
	rec s1;
	char reg[100];
	int flag=0,x=25,y=9;
	char ch;
	fp1=openFile("record.txt","rb");
	fp2=openFile("temp.txt","wb");
	gotoxy(x,6);
	printf("Enter Registration No. of student record to be deleted : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s1,sizeof(rec),1,fp1)) {
		if(strcmp(strupr(reg),strupr(s1.regNum))==0) {
			flag=1;
			printCheck(s1,y);
			dash();
			y=20;
			ch=confirm("Do you want to delete this record ? [Y/N] : ",&x,&y);
			if(ch=='y' || ch=='Y') {
				flag=2;
				continue;
			}			
		}
		save("temp.txt",s1);
	}
	if(flag==0) {
		gotoxy(x,y-=1);
		printf("Record not found.");
	}
	else if(flag==2) {
		gotoxy(x,y+=3);
		printf("Record successfully deleted.");
	}
	else if(flag==1) {
		gotoxy(x,y+=3);
		printf("Record not deleted.");
	}
	fclose(fp2);
	fclose(fp1);
	remo("record.txt");
	rena("temp.txt","record.txt");
	y+=2;
	*posy=y;
	*posx=x;
}

void search()
{
	FILE *fp;
	rec s;
	char reg[100];
	int flag=0,x=25,y=10;
	fp=openFile("record.txt","rb");
	gotoxy(x,6);
	printf("Enter Registration No. of student record to be searched : ");
	fflush(stdin);
	fscanf(stdin,"%s",reg);
	while(fread(&s,sizeof(rec),1,fp)) {
		if(strcmp(strupr(reg),strupr(s.regNum))==0) {
			flag=1;
			printCheck(s,y);
			dash();
			y=19;
			x=40;
			break;
		}
	}
	if(flag==0) {
		y-=2;
		gotoxy(x,y);
		y+=4;
		x=40;
		printf("Record not found.");
	}
	*posy=y;
	*posx=x;
	fclose(fp);
}
