#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

int *posx, *posy;

// Function prototypes
FILE* openFile(char [], char []);
rec add(FILE *);
char confirm(char [], int *, int *);
void create();
void dash();
void dashTab();
void del();
void gotoxy(int, int);
char* grade(struct subject [], int);
void printCheck(rec, int);
void prinHead();
void prinTab(rec [], int);
void prinTabFail(rec);
void prinTabPass(rec);
int passFail(rec [], char [], int);
void remo(char []);
void rena(char [], char []);
void save(char [], rec);
void search();
void sort(rec [], int, char);
void swap(rec *, rec *);
void update();
void view();
void viewFac(FILE *, char [], rec);

int main() {
    char ch, c;
    int x, y;
    posx = &x;
    posy = &y;

    do {
        system("cls");
        x = 35;
        y = 6;
        gotoxy(20, 4);
        dash();
        gotoxy(x, ++y);
        printf("|\tStudent Record Management System\t|");
        gotoxy(x, ++y);
        dash();
        gotoxy(x, y += 3);
        printf("1. Add Student Record");
        gotoxy(x, ++y);
        printf("2. View Student Record");
        gotoxy(x, ++y);
        printf("3. Update Student Record");
        gotoxy(x, ++y);
        printf("4. Delete Student Record");
        gotoxy(x, ++y);
        printf("5. Search Student Record");
        gotoxy(x, ++y);
        printf("6. Exit program");
        y += 2;
        c = confirm("Which operation do you want to perform? [1-6] : ", &x, &y);
        system("cls");

        switch (c) {
            case '1':
                create();
                break;
            case '2':
                view();
                break;
            case '3':
                //update();
                break;
            case '4':
                del();
                break;
            case '5':
                //search();
                break;
            case '6':
                gotoxy(x, 8);
                dash();
                gotoxy(45, 12);
                printf("Thank you for using the program.");
                gotoxy(x, 14);
                dash();
                exit(0);
                break;
            default:
                gotoxy(15, 7);
                printf("Invalid choice. Please choose from 1 - 6.");
                *posy = 10;
        }

        (*posy)++;
        *posx = 15;
        ch = confirm("Do you want to continue? [Y/N] : ", posx, posy);
    } while (ch == 'y' || ch == 'Y');

    return 0;
}

void dash() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, i;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        printf("Error getting console screen buffer info.\n");
        return;
    }
    width = csbi.dwSize.X;
    putchar('\n');
    for (i = 0; i < width; i++) {
        putchar('-');
    }
    printf("\n\n");
    fflush(stdout);
}

void create() {
    FILE *fp;
    int x = 35, y = 5;
    rec s;

    fp = openFile("record.txt", "ab+");
    gotoxy(x, y);
    printf("Enter the following student details :");
    s = add(fp);
    save("record.txt", s);
    gotoxy(x, *posy);
    printf("File Successfully saved.");
    (*posy) += 2;
}

FILE* openFile(char fn[], char mode[]) {
    FILE *fp = fopen(fn, mode);
    if (fp == NULL) {
        printf("Error opening file.");
        exit(1);
    }
    return fp;
}

rec add(FILE *fp) {
    rec s, temp;
    int i, x = 35, y = 7;

    gotoxy(x, y);
    printf("Registration No. : ");
    fscanf(stdin, "%s", s.regNum);

    while (fread(&temp, sizeof(rec), 1, fp)) {
        while (!strcmp(temp.regNum, s.regNum)) {
            gotoxy(x = 28, y += 2);
            printf("Student record with Registration No. %s already exists.", s.regNum);
            gotoxy(x = 35, y += 2);
            printf("Enter registration no. again : ");
            fflush(stdin);
            fscanf(stdin, "%s", s.regNum);
            rewind(fp);
        }
    }
    fclose(fp);

    gotoxy(x, ++y);
    printf("Name : ");
    fflush(stdin);
    fgets(s.name, sizeof(s.name), stdin);
    strtok(s.name, "\n");

    gotoxy(x, ++y);
    printf("Faculty : ");
    fgets(s.faculty, sizeof(s.faculty), stdin);
    strtok(s.faculty, "\n");

    gotoxy(x, ++y);
    printf("Semester : ");
    scanf("%d", &s.sem);

    gotoxy(x, ++y);
    printf("Address : ");
    fflush(stdin);
    fgets(s.addr, sizeof(s.addr), stdin);
    strtok(s.addr, "\n");

    gotoxy(x, ++y);
    printf("Enter no. of subjects : ");
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
        printf("For subject %d : ", i + 1);
        scanf("%f", &s.sub[i].marks);
        s.m.total += s.sub[i].marks;
    }

    strcpy(s.m.gr, grade(s.sub, s.subNum));
    if (strcmp(s.m.gr, "PASS") == 0) {
        s.m.percent = s.m.total / s.subNum;
    }

    y += 3;
    *posy = y;
    *posx = x;

    return s;
}

char* grade(struct subject s[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (s[i].marks < 40) {
            return "FAIL";
        }
    }
    return "PASS";
}

void remo(char fn[]) {
    if (remove(fn) != 0) {
        printf("Error deleting file.");
        exit(1);
    }
}

void rena(char old[], char newn[]) {
    if (rename(old, newn) != 0) {
        printf("Error renaming file.");
        exit(1);
    }
}

char confirm(char s[], int *x, int *y) {
    char c;
    gotoxy(*x, *y);
    printf("%s", s);
    scanf(" %c", &c);
    return c;
}

void save(char fn[], rec s) {
    FILE *fp = openFile(fn, "ab");
    if (fwrite(&s, sizeof(s), 1, fp) != 1) {
        printf("Error writing into file.");
    }
    fclose(fp);
}

void printCheck(rec s, int y) {
    int x = 15;
    dash();
    gotoxy(x, ++y);
    printf("%-17s: %s", "Name", s.name);
    gotoxy(x, ++y);
    printf("%-17s: %s", "Address", s.addr);
    gotoxy(x, ++y);
    printf("%-17s: %s", "Registration No.", s.regNum);
    gotoxy(x, ++y);
    printf("%-17s: %s", "Faculty", s.faculty);
    gotoxy(x, ++y);
    printf("%-17s: %d", "Semester", s.sem);
    gotoxy(x, ++y);
    printf("%-17s: %s", "Grade", s.m.gr);
    gotoxy(x, ++y);
    if (strcmp(s.m.gr, "PASS") == 0) {
        printf("%-17s: %.2f %%", "Percentage", s.m.percent);
    }
    dash();
}

void del() {
    char reg[MAX];
    int x = 15, y = 7;
    FILE *fp, *fp2;
    rec s1;
    char c;
    int found = 0;

    fp = openFile("record.txt", "rb");
    fp2 = openFile("temp.txt", "wb");

    gotoxy(x, y);
    printf("Enter the registration number of student to be deleted : ");
    scanf("%s", reg);

    while (fread(&s1, sizeof(rec), 1, fp)) {
        if (strcmp(s1.regNum, reg) == 0) {
            printCheck(s1, y + 3);
            found = 1;
            y += 14;
            c = confirm("Are you sure you want to delete this record? [Y/N] : ", &x, &y);
            if (c == 'n' || c == 'N') {
                fwrite(&s1, sizeof(rec), 1, fp2);
            }
        } else {
            fwrite(&s1, sizeof(rec), 1, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    remo("record.txt");
    rena("temp.txt", "record.txt");
    gotoxy(x, ++y);
    if (found) {
        printf("Record successfully deleted.");
    } else {
        printf("Record not found.");
    }
    (*posy) = y;
}

void view() {
    FILE *fp;
    rec s;
    int y = 5, x = 3;
    char c;

    fp = openFile("record.txt", "rb");
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        printf("No records available.\n");
        fclose(fp);
        return;
    }
    rewind(fp);

    dash();
    gotoxy(x, ++y);
    printf("%-20s%-20s%-20s%-15s%-15s%-10s%-10s%-10s\n", "Name", "Address", "Reg No.", "Faculty", "Semester", "Grade", "Percentage", "Total Marks");
    dash();
    y += 2;

    while (fread(&s, sizeof(rec), 1, fp)) {
        gotoxy(x, y++);
        printf("%-20s%-20s%-20s%-15s%-15d%-10s%-10.2f%-10.2f\n", s.name, s.addr, s.regNum, s.faculty, s.sem, s.m.gr, s.m.percent, s.m.total);
    }
    fclose(fp);
    dash();

    c = confirm("Do you want to continue? [Y/N] : ", posx, posy);
    if (c == 'y' || c == 'Y') {
        view();
    }
}

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sort(rec students[], int n, char field) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            int cmp = 0;
            switch (field) {
                case 'n': // Sort by name
                    cmp = strcmp(students[j].name, students[j+1].name);
                    break;
                case 'r': // Sort by registration number
                    cmp = strcmp(students[j].regNum, students[j+1].regNum);
                    break;
                case 'p': // Sort by percentage
                    if (students[j].m.percent < students[j+1].m.percent) {
                        cmp = -1;
                    } else if (students[j].m.percent > students[j+1].m.percent) {
                        cmp = 1;
                    }
                    break;
                // Add other sorting criteria as needed
            }
            if (cmp > 0) {
                swap(&students[j], &students[j+1]);
            }
        }
    }
}

void swap(rec *a, rec *b) {
    rec temp = *a;
    *a = *b;
    *b = temp;
}

