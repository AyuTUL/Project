#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Include time.h for randomization

// Define the structure for student records
struct subject {
    char subName[100];
    float marks;
};

struct marks {
    float total, percent;
    char gr[5];
};

struct student {
    int sem;
    char name[100], addr[100], regNum[100], faculty[100];
    struct subject sub[5];
    struct marks m; 
};

int main() {
    FILE *fp;
    struct student records[30]; // Sample data for 30 students
    int i, j, k;

    // Initialize random seed
    srand(time(NULL));

    // Initialize sample student records
    for (i = 0; i < 30; i++) {
        sprintf(records[i].regNum, "REG%d", i + 1);
        strcpy(records[i].name, "Student Name");
        strcpy(records[i].addr, "Address");
        
        // Randomly assign faculty
        int facultyIndex = rand() % 4;
        switch (facultyIndex) {
            case 0:
                strcpy(records[i].faculty, "CSIT");
                break;
            case 1:
                strcpy(records[i].faculty, "BHM");
                break;
            case 2:
                strcpy(records[i].faculty, "BIM");
                break;
            case 3:
                strcpy(records[i].faculty, "BBM");
                break;
            default:
                strcpy(records[i].faculty, "CSIT"); // Default to CSIT
        }

        records[i].sem = (i % 8) + 1; // Random semester between 1 and 8

        // Generate random subject names and marks
        for (j = 0; j < 5; j++) {
            sprintf(records[i].sub[j].subName, "Subject%d", j + 1);
            records[i].sub[j].marks = (rand() % 71) + 30; // Random marks between 30 and 100
        }

        strcpy(records[i].m.gr, "PASS"); // Default grade
        records[i].m.total = 0;
        for (k = 0; k < 5; k++) {
            if (records[i].sub[k].marks < 40) {
                strcpy(records[i].m.gr, "FAIL");
                break;
            }
            records[i].m.total += records[i].sub[k].marks;
        }
        records[i].m.percent = records[i].m.total / 5.0;
    }

    // Open file in binary write mode
    fp = fopen("record.txt", "wb");

    // Write data to the binary file
    fwrite(records, sizeof(struct student), 30, fp);

    // Close the file
    fclose(fp);

    printf("Data written to record.bin.\n");

    return 0;
}

