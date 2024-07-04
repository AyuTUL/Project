#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX 100

struct subject {
    float marks;
};

struct marks {
    float total, percent;
    char gr[5];
};

struct student {
    int sem, subNum;
    char name[MAX], addr[MAX], regNum[MAX], faculty[MAX];
    struct subject *sub;
    struct marks m;
};

typedef struct student rec;

// Function prototypes
FILE* openFile(char [], char []);
rec add(FILE *);
char confirm(char [], int *, int *);
void remo(char []);
void rena(char [], char []);
void save(char [], rec);

void update();
void gotoxy(int, int);
char* grade(struct subject [], int);

int *posx, *posy;

void main() {
    char ch,c;
    int x,y;
    posx=&x;
    posy=&y;
    do
    {
        system("cls");
        x=35;
        y=6;
        gotoxy(20,4);
        printf("-------------------------------\n");
        gotoxy(x,++y);
        printf("|\tStudent Record Management System\t|");
        gotoxy(x,++y);
        printf("-------------------------------\n");
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
        switch(c)
        {
            case '1':
                // create();
                break;
            case '2':
                // view();
                break;
            case '3':
                update();
                break;
            case '4':
                // del();
                break;
            case '5':
                // search();
                break;
            case '6':
                printf("Thank you for using the program.");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please choose from 1 - 5.");
        }
        (*posy)++;
        ch=confirm("Do you want to continue? [Y/N] : ",posx,posy);
    }while(ch=='y' || ch=='Y');
}

void update() {
    FILE *fp1, *fp2;
    rec s1;
    char reg[100];
    int flag = 0, x = 25, y = 6;
    
    fp1 = openFile("record.txt", "rb");
    fp2 = openFile("temp.txt", "wb");
    
    gotoxy(x, y);
    printf("Enter Registration No. of student record to be updated: ");
    fflush(stdin);
    fscanf(stdin, "%s", reg);
    
    while (fread(&s1, sizeof(rec), 1, fp1)) {
        if (strcmp(strupr(reg), strupr(s1.regNum)) == 0) {
            flag = 1;
            gotoxy(x, ++y);
            printf("Enter new details:\n\n");
            s1 = add(fp2);
        }
        save("temp.txt", s1);
    }
    
    if (flag == 0) {
        printf("Record not found.");
    } else {
        printf("File successfully saved.");
    }
    
    fclose(fp2);
    fclose(fp1);
    remo("record.txt");
    rena("temp.txt", "record.txt");
}

// Function to open a file and return the file pointer
FILE* openFile(char fn[], char mode[]) {
    FILE *fp;
    fp = fopen(fn, mode);
    if (fp == NULL) {
        printf("Error opening file.");
        exit(1);
    }
    return(fp);
}

// Function to add a new student record
rec add(FILE *fp) {
    rec s, temp;
    int i, x = 35, y = 9;
    
    gotoxy(x, y);
    printf("Registration No.: ");
    fscanf(stdin, "%s", s.regNum);
    
    while (fread(&temp, sizeof(rec), 1, fp)) {
        while (!strcmp(temp.regNum, s.regNum)) {
            gotoxy(x = 28, ++y);
            printf("Student record with registration no. %s already exists.", s.regNum);
            gotoxy(x = 35, ++y);
            printf("Enter registration no. again: ");
            fflush(stdin);
            fscanf(stdin, "%s", s.regNum);
            rewind(fp);
        }
    }
    
    fclose(fp);
    gotoxy(x, ++y);
    printf("Name: ");
    fflush(stdin);
    fgets(s.name, sizeof(s.name), stdin);
    strtok(s.name, "\n");
    gotoxy(x, ++y);
    printf("Faculty: ");
    fgets(s.faculty, sizeof(s.faculty), stdin);
    strtok(s.faculty, "\n");
    gotoxy(x, ++y);
    printf("Semester: ");
    scanf("%d", &s.sem);
    gotoxy(x, ++y);
    printf("Address: ");
    fflush(stdin);
    fgets(s.addr, sizeof(s.addr), stdin);
    strtok(s.addr, "\n");
    gotoxy(x, ++y);
    printf("Enter no. of subjects: ");
    scanf("%d", &s.subNum);
    
    s.m.total = 0;
    s.sub = (struct subject *)malloc(s.subNum * sizeof(struct subject));
    if (s.sub == NULL) {
        gotoxy(x, ++y);
        printf("Memory allocation failed.");
        exit(1);
    }
    
    gotoxy(x, ++y);
    printf("Enter marks in %d subjects:\n", s.subNum);
    for (i = 0; i < s.subNum; i++) {
        gotoxy(x, ++y);
        printf("For subject %d: ", i + 1);
        scanf("%f", &s.sub[i].marks);
        s.m.total += s.sub[i].marks;
    }
    
    strcpy(s.m.gr, grade(s.sub, s.subNum));
    if (strcmp(s.m.gr, "PASS") == 0)
        s.m.percent = s.m.total / s.subNum;
    
    y += 2;
    return(s);
}

// Function to determine the grade based on marks
char* grade(struct subject s[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (s[i].marks < 40)
            break;
    }
    if (i < n)
        return("FAIL");
    else
        return("PASS");
}

// Function to remove a file
void remo(char fn[]) {
    int err;
    err = remove(fn);
    if (err != 0) {
        printf("Error deleting file.");
        exit(1);
    }
}

// Function to rename a file
void rena(char old[], char newn[]) {
    int err;
    err = rename(old, newn);
    if (err != 0) {
        printf("Error renaming file.");
        exit(1);
    }
}

// Function to save a student record to a file
void save(char fn[], rec s) {
    FILE *fp;
    fp = openFile(fn, "ab");
    if (fwrite(&s, sizeof(s), 1, fp) != 1)
        printf("Error writing into file.");
    fclose(fp);
}

// Function to set the cursor position in the console
void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error getting console handle.");
        exit(1);
    }
    COORD cursorPos;
    cursorPos.X = x;
    cursorPos.Y = y;
    if (!SetConsoleCursorPosition(hConsole, cursorPos)) {
        printf("Error setting console cursor position.");
        exit(1);
    }
}

// Function to get confirmation from the user
char confirm(char s[], int *x, int *y) {
    char c;    
    gotoxy(*x, *y);
    printf("%s", s);
    scanf(" %c", &c);
    return(c);
}

