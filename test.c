#include <stdio.h>
#include <string.h>

#define MAX 100

struct subject {
    char subName[MAX];
    float marks;
};

struct marks {
    float total, percent;
    const char *sch, *gr;
};

struct student {
    int sem;
    char name[MAX], addr[MAX], regNum[MAX], faculty[MAX];
    struct subject sub[5];
    struct marks m;
};

typedef struct student rec;

int main() {
    rec students[3];
    FILE *fp;
int i;
    // Initialize student data
    students[0].sem = 1;
strcpy(students[0].name, "Charlie");
strcpy(students[0].addr, "Addr1");
strcpy(students[0].regNum, "Reg1");
strcpy(students[0].faculty, "CSIT");

strcpy(students[0].sub[0].subName, "Math");
students[0].sub[0].marks = 12;

strcpy(students[0].sub[1].subName, "Physics");
students[0].sub[1].marks = 12;

strcpy(students[0].sub[2].subName, "IIT");
students[0].sub[2].marks = 12;

strcpy(students[0].sub[3].subName, "C");
students[0].sub[3].marks = 12;

strcpy(students[0].sub[4].subName, "DL");
students[0].sub[4].marks = 12;

students[0].m.total = 60.0;
students[0].m.percent = (students[0].m.total / 60.0) * 100;


    students[0].m.gr = "PASS";


    // Open file in binary write mode
    fp = fopen("record.txt", "wb");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write student data to file
    for ( i = 0; i < 3; i++) {
        fwrite(&students[i], sizeof(rec), 1, fp);
    }

    // Close file
    fclose(fp);

    printf("Student data written to students.dat successfully.\n");

    return 0;
}
