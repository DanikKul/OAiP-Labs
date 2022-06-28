#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{

    struct{
        char* lastName;
        char* firstName;
        char* middleName;
        int semester;
    };

    union{
        int ex[3];
        int res[8][3];
    } sems;

};


char* exams[8][3] = {
        "Linear algebra", "Politics", "Belarusian",
        "Mathematical analysis", "Basics of programming", "English",
        "Physics", "Discrete maths", "History",
        "AaLBoDD", "Operating systems", "Marketing",
        "Informatics", "AOKS", "TEC",
        "Chemistry", "TVIMS", "OSBD",
        "BD", "MMvP", "OZI",
        "OTS", "EP", "SAU"
};

int commandLineInput(char* argv[]);
int reserveInput();
int inputSemester();
void inputNames(struct person *student, int index);
void inputGrades(struct person *student, int index);
void output(struct person *student, int amountOfStudents);
void deleteEnter(char* string, int length);
void outputByName(char* name, struct person *student, int amountOfStudents);

void newLoop(struct person *student, int amountOfStudents){
    fflush(stdin);
    char *choose = (char *) calloc(20, sizeof(char));
    printf("if you want to continue write 'continue'\nif you want to exit program press any other key\n\n");
    fgets(choose, 20, stdin);
    deleteEnter(choose, 20);
    if(strcmp(choose, "continue") == 0){
        printf("\nif you want to add a student write 'add'\nif you want to choose semester again write 'semester'\nif you want to find a student by last name enter 'last name'\n\n");
        char *choose1 = (char *) calloc(20, sizeof(char));
        fflush(stdin);
        fgets(choose1, 20, stdin);
        deleteEnter(choose1, 20);
        printf("\n");

        if(strcmp(choose1, "semester") == 0){

            int semester = inputSemester();

            for (int i = 0; i < amountOfStudents; ++i) {
                student[i].semester = semester;
            }

            output(student, amountOfStudents);
        }

        if(strcmp(choose1, "last name") == 0){
            printf("enter last name\n");
            char *choose2 = (char *) calloc(20, sizeof(char));
            fflush(stdin);
            fgets(choose2, 20, stdin);
            deleteEnter(choose2, 20);
            outputByName(choose2, student, amountOfStudents);
        }

        if(strcmp(choose1, "add") == 0){

            student[amountOfStudents].firstName = (char*) calloc(20, sizeof (char));
            student[amountOfStudents].lastName = (char*) calloc(40, sizeof (char));
            student[amountOfStudents].middleName = (char*) calloc(40, sizeof (char));
            student[amountOfStudents].semester = student[amountOfStudents - 1].semester;

            inputNames(student, amountOfStudents);
            inputGrades(student, amountOfStudents);
            printf("\nadded\n");

            output(student, amountOfStudents + 1);

            amountOfStudents++;
        }
        newLoop(student, amountOfStudents);
    } else return;
}

int main(__attribute__((unused)) int argc, char* argv[]){

    int studentIndex = 0;
    int amountOfStudents = commandLineInput(argv);
    if (amountOfStudents <= 0){
        printf("you entered incorrect value\n");
        amountOfStudents = reserveInput();
    }

    int semester = inputSemester();

    struct person *student = NULL;
    student = (struct person*) calloc (100, sizeof (struct person));
    for (int i = 0; i < amountOfStudents; ++i) {
        student[i].firstName = (char*) calloc(20, sizeof (char));
        student[i].lastName = (char*) calloc(40, sizeof (char));
        student[i].middleName = (char*) calloc(40, sizeof (char));
        student[i].semester = semester;
    }

    if(!student){
        printf("memory error\n");
        return -1;
    }

    for (int i = 0; i < amountOfStudents; ++i) {
        inputNames(student, studentIndex);
        inputGrades(student, studentIndex);
        studentIndex++;
    }

    output(student, amountOfStudents);

    newLoop(student, amountOfStudents);

    return 0;
}

int commandLineInput(char* argv[]){
    int amountOfStudents = 0;
    if(argv[1] == NULL){
        return reserveInput();
    } else {
        for (int i = 0; i < strlen(argv[1]); ++i) {
            if (argv[1][i] < '0') {
                printf("error\n");
                return -1;
            } else {
                amountOfStudents += argv[1][i] - '0';
                amountOfStudents *= 10;
            }
        }
        amountOfStudents /= 10;
    }
    return amountOfStudents;
}

int reserveInput(){
    printf("enter amount of students\n");
    fflush(stdin);
    int amountOfStudents = -1;
    while(amountOfStudents <= 0){
        amountOfStudents = -1;
        while (!scanf("%d", &amountOfStudents)){
            fflush(stdin);
            printf("error\n");
        }
        if(amountOfStudents <= 0){
            printf("error\n");
        }
    }
    return amountOfStudents;
}

int inputSemester(){
    printf("enter semester\n");
    fflush(stdin);
    int semester = -1;
    while(semester <= 0 || semester >= 9){
        semester = -1;
        while (!scanf("%d", &semester)){
            fflush(stdin);
            printf("error\n");
        }
        if(semester <= 0 || semester >= 9){
            printf("error\n");
        }
    }
    return semester;
}

void deleteEnter(char* string, int length){
    int index = 0;
    while(string[index] != '\n' && index < length) index++;
    string[index] = '\0';
}

void inputNames(struct person *student, int index){
    fflush(stdin);
    printf("enter the student info\n");
    printf("enter the student's first name\n");
    fgets(student[index].firstName, 20, stdin);
    printf("enter the student's last name\n");
    fflush(stdin);
    fgets(student[index].lastName, 40, stdin);
    printf("enter the student's middle name\n");
    fflush(stdin);
    fgets(student[index].middleName, 40, stdin);
    deleteEnter(student[index].firstName, 20);
    deleteEnter(student[index].lastName, 40);
    deleteEnter(student[index].middleName, 40);
}

void inputGrades(struct person *student, int index){
    int counter = 1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; ++j, ++counter) {
            printf("enter grade #%d = ", counter);
            fflush(stdin);
            int grade = -1;
            while (grade < 0 || grade > 10) {
                grade = -1;
                while (!scanf("%d", &grade)) {
                    fflush(stdin);
                    printf("error\n");
                }
                if (grade < 0 || grade > 10) {
                    printf("error\n");
                }
            }
            student[index].sems.res[i][j] = grade;
            printf("\n");
        }
    }
}

void inputExams(struct person *student, int index){
    for (int i = 0; i < 3; ++i) {
        student[index].sems.ex[i] = i;
    }
}

void output(struct person *student, int amountOfStudents){
    int arr[3];
    int buff[3];
    for (int i = 0; i < amountOfStudents; ++i) {
        for (int j = 0; j < 3; ++j) {
            arr[j] = student[i].sems.res[student[i].semester - 1][j];
            buff[j] = student[i].sems.res[0][j];
        }
        printf("\n\n\tSTUDENT\nNAME: %s\nLAST NAME: %s\nMIDDLE NAME: %s\nSEMESTER: %d\n",
               student[i].firstName, student[i].lastName, student[i].middleName, student[i].semester);
        inputExams(student, i);
        printf("EXAMS: ");
        for (int j = 0; j < 3; ++j) {
            printf("[%s] ", exams[student[i].semester - 1][student[i].sems.ex[j]]);
        }
        printf("\nGRADES: ");
        for (int j = 0; j < 3; ++j) {
            printf(" %d  ", arr[j]);
            student[i].sems.res[0][j] = buff[j];
        }
        printf("\n\n");
    }
}

void outputByName(char* name, struct person *student, int amountOfStudents){
    int arr[3];
    int buff[3];
    for (int i = 0; i < amountOfStudents; ++i) {
        if(strcmp(name, student[i].lastName) == 0 || strcmp(name, "") == 0){
            for (int j = 0; j < 3; ++j) {
                arr[j] = student[i].sems.res[student[i].semester - 1][j];
                buff[j] = student[i].sems.res[0][j];
            }
            printf("\n\n\tSTUDENT\nNAME: %s\nLAST NAME: %s\nMIDDLE NAME: %s\nSEMESTER: %d\n",
                   student[i].firstName, student[i].lastName, student[i].middleName, student[i].semester);
            inputExams(student, i);
            printf("EXAMS: ");
            for (int j = 0; j < 3; ++j) {
                printf("[%s] ", exams[student[i].semester - 1][student[i].sems.ex[j]]);
            }
            printf("\nGRADES: ");
            for (int j = 0; j < 3; ++j) {
                printf(" %d  ", arr[j]);
                student[i].sems.res[0][j] = buff[j];
            }
            printf("\n\n");
        }
    }
}