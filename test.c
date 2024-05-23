#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure for subject marks
struct subject {
    float marks;
};

// Define the structure for student records
struct student {
    int sem, subNum;
    char name[100], addr[100], regNum[100], faculty[100];
    struct subject *sub; // Pointer to array of subjects
    float totalMarks, percent;
    char grade[5];
};

// Function to generate random marks for subjects
void generateRandomMarks(struct subject *sub, int subNum) {
    int i;
    for (i = 0; i < subNum; i++) {
        sub[i].marks = (rand() % 81) + 20; // Random marks between 30 and 100
    }
}

// Function to calculate total marks, percentage, and grade
void calculateResults(struct student *s) {
    int i;
    s->totalMarks = 0;
    for (i = 0; i < s->subNum; i++) {
        s->totalMarks += s->sub[i].marks;
    }
    s->percent = (s->totalMarks / (s->subNum * 100)) * 100;
    strcpy(s->grade, (s->percent >= 40) ? "PASS" : "FAIL");
}

// Function to generate a random name
void generateRandomName(char *name) {
    static const char *firstNames[] = {"John", "Emma", "Michael", "Sophia", "William", "Olivia", "James", "Ava"};
    static const char *lastNames[] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis"};

    strcpy(name, firstNames[rand() % (sizeof(firstNames) / sizeof(firstNames[0]))]);
    strcat(name, " ");
    strcat(name, lastNames[rand() % (sizeof(lastNames) / sizeof(lastNames[0]))]);
}

int main() {
    FILE *fp;
    struct student records[30]; // Sample data for 30 students
    int i;

    // Initialize random seed
    srand(time(NULL));

    // Initialize sample student records
    for (i = 0; i < 30; i++) {
        sprintf(records[i].regNum, "REG%d", i + 1);
        generateRandomName(records[i].name);
        sprintf(records[i].addr, "Address %d", i + 1);
        
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
        records[i].subNum = (rand() % 4) + 5; // Random number of subjects between 5 and 8
        records[i].sub = (struct subject *)malloc(records[i].subNum * sizeof(struct subject));

        // Generate random marks for subjects
        generateRandomMarks(records[i].sub, records[i].subNum);

        // Calculate total marks, percentage, and grade
        calculateResults(&records[i]);
    }

    // Open file in binary write mode
    fp = fopen("record.txt", "wb");

    // Write data to the binary file
    fwrite(records, sizeof(struct student), 30, fp);

    // Close the file
    fclose(fp);

    printf("Data written to record.txt.\n");

    return 0;
}

