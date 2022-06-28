#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info{
    char* filmName;
    char* filmType;
    int year;
};

void deleteEnter(char* string, int length){
    int index = 0;
    while(string[index] != '\n' && index < length) index++;
    string[index] = '\0';
}

void inputInFile(FILE *f, struct info film, char *argv[]){
    if(!(f = fopen(argv[1], "wb+"))){
        printf("Unable to open file\n");
        exit(1);
    }
    fwrite(&film, sizeof(film), 1, f);
    fclose(f);
}

int isInt(char* string){
    if(string == NULL || strlen(string) == 0){
        return 1;
    }
    for (int i = 0; i < strlen(string); ++i) {
        if((string[i] < '0' || string[i] > '9')){
            return 1;
        }
    }
    return 0;
}

void inputInfo(struct info *film){
    film->filmName = (char*) calloc(100, sizeof(char));
    film->filmType = (char*) calloc(100, sizeof(char));
    fflush(stdin);
    printf("\nEnter name of a film\n");
    fgets(film->filmName, 100, stdin);
    fflush(stdin);
    printf("\nEnter type of a film\n");
    fgets(film->filmType, 100, stdin);
    fflush(stdin);
    film->year = -1;
    printf("\nEnter year of release date\n");
    while(film->year < 0){
        fflush(stdin);
        while(!fscanf(stdin, "%d", &film->year)){
            printf("\nYou entered not a year\n");
            fflush(stdin);
        }
        if(film->year < 0){
            printf("\nYou entered number less than 0\n");
        }
    }
    deleteEnter(film->filmName, 100);
    deleteEnter(film->filmType, 100);
}

fpos_t outputFromFile(FILE *f, struct info *film, char *argv[], fpos_t curPos, char* userAnswer, char* criteria){
    if(!(f = fopen(argv[1], "rb+"))){
        printf("Unable to open file\n");
        exit(1);
    }
    fsetpos(f, &curPos);
    fread(film, sizeof(struct info), 1, f);
    if(!(strcmp(film->filmName, "UNDEFINED") == 0)) {
        printf("\n");
        if (strcmp(userAnswer, "all") == 0) {
            printf("\tFILM\nNAME: %s\nTYPE: %s\nYEAR: %d\n\n",
                   film->filmName, film->filmType, film->year);
        } else if (strcmp(userAnswer, "name") == 0) {
            if (strcmp(criteria, film->filmName) == 0) {
                printf("\tFILM\nNAME: %s\nTYPE: %s\nYEAR: %d\n\n",
                       film->filmName, film->filmType, film->year);
            }
        } else if (strcmp(userAnswer, "type") == 0) {
            if (strcmp(criteria, film->filmType) == 0) {
                printf("\tFILM\nNAME: %s\nTYPE: %s\nYEAR: %d\n\n",
                       film->filmName, film->filmType, film->year);
            }
        } else if (strcmp(userAnswer, "year") == 0) {
            if (isInt(criteria) == 0) {
                if (film->year == atoi(criteria)) {
                    printf("\tFILM\nNAME: %s\nTYPE: %s\nYEAR: %d\n\n",
                           film->filmName, film->filmType, film->year);
                }
            } else {
                printf("\nSomething went wrong...\n\n");
            }
        }
    }
    fgetpos(f, &curPos);
    fclose(f);
    return curPos;
}

int deleteFromFile(FILE *f, char *argv[], int amount){

    if(!(f = fopen(argv[1], "rb+"))){
        printf("Unable to open file\n");
        exit(1);
    }
    struct info *list = (struct info*) calloc(1000, sizeof(struct info));
    for (int i = 0; i < amount; ++i) {
        fread(&list[i], sizeof(struct info), 1, f);
    }
    fclose(f);

    if(!(f = fopen(argv[1], "ab+"))){
        printf("Unable to open file\n");
        exit(1);
    }
    fseek(f, 0, SEEK_SET);
    int diff = 0;
    char* ans = (char*) calloc(100, sizeof(char));
    char* userAnswer = (char*) calloc(100, sizeof(char));
    printf("\n'name' - delete by name\n"
           "'type' - delete by type\n"
           "'year' - delete by year\n"
           "'duplicates' - delete all duplicates\n");
    fflush(stdin);
    fgets(ans, 100, stdin);
    deleteEnter(ans, 100);
    if (strcmp(ans, "name") == 0){
        printf("\nEnter criteria\n");
        fflush(stdin);
        fgets(userAnswer, 100, stdin);
        deleteEnter(userAnswer, 100);
        printf("\n");
        for (int i = 0; i < amount; ++i) {
            if (strcmp(userAnswer, list[i].filmName) == 0){
                printf("deleted: %s\n", list[i].filmName);
                diff++;
                continue;
            } else {
                fwrite(&list[i], sizeof(struct info), 1, f);
            }
        }
    } else if (strcmp(ans, "type") == 0){
        printf("\nEnter criteria\n");
        fflush(stdin);
        fgets(userAnswer, 100, stdin);
        deleteEnter(userAnswer, 100);
        printf("\n");
        for (int i = 0; i < amount; ++i) {
            if (strcmp(userAnswer, list[i].filmType) == 0){
                printf("deleted: %s\n", list[i].filmName);
                diff++;
                continue;
            } else {
                fwrite(&list[i], sizeof(struct info), 1, f);
            }
        }
    } else if (strcmp(ans, "year") == 0) {
        printf("\nEnter criteria\n");
        fflush(stdin);
        fgets(userAnswer, 100, stdin);
        deleteEnter(userAnswer, 100);
        printf("\n");
        for (int i = 0; i < amount; ++i) {
            if (list[i].year == atoi(userAnswer)) {
                printf("deleted: %s\n", list[i].filmName);
                diff++;
                continue;
            } else {
                fwrite(&list[i], sizeof(struct info), 1, f);
            }
        }
    } else if(strcmp(ans, "duplicates") == 0){
        int* dupl = (int*) calloc(amount + 1, sizeof (int));
        for (int i = 0; i < amount; ++i) {
            dupl[i] = 0;
        }
        for (int i = 0; i < amount; ++i) {
            for (int j = i + 1; j < amount; ++j) {
                if (strcmp(list[i].filmName, list[j].filmName) == 0 &&
                        strcmp(list[i].filmType, list[j].filmType) == 0 &&
                        list[i].year == list[j].year) {
                    dupl[j] = 1;
                }
            }
        }
        for (int i = 0; i < amount; ++i) {
            if (dupl[i] == 0){
                fwrite(&list[i], sizeof(struct info), 1, f);
            } else {
                diff++;
            }
        }
    } else {
        printf("\nNo that criteria...\n");
        diff = -1;
    }

    printf("\n");
    if (diff == 0){
        printf("No films found\n");
    } else if (diff == 1){
        printf("Deleted 1 film\n");
    } else if (diff > 1){
        printf("Deleted %d films\n", diff);
    } else {
        diff = 0;
    }
    printf("\n");
    fclose(f);
    return diff;
}

void loop(FILE *f, struct info film, char* argv[]){
    char *userAnswer = (char*) calloc (100, sizeof(char));
    int filmsAmount = 0;
    fpos_t curPos;
    while (1){
        curPos = 0;
        printf("'add' - creates new film\n"
               "'delete' - removes a film\n"
               "'show' - shows films via criteria\n"
               "'exit' - ends program\n");
        fflush(stdin);
        fgets(userAnswer, 100, stdin);
        deleteEnter(userAnswer, 100);
        if (strcmp(userAnswer, "exit") == 0){
            printf("\nClosing...\n");
            break;
        } else if (strcmp(userAnswer, "add") == 0){
            printf("\nAdd a new film\n");
            inputInfo(&film);
            inputInFile(f, film, argv);
            filmsAmount++;
        } else if (strcmp(userAnswer, "delete") == 0){
            printf("\nDeleting file\n");
            int diff = deleteFromFile(f, argv, filmsAmount);
            filmsAmount -= diff;
        } else if (strcmp(userAnswer, "show") == 0){
            printf("\nSelect criteria\n"
                   "'all' - shows all films\n"
                   "'name' - show films by name\n"
                   "'type' - show films by type\n"
                   "'year' - show films by release year\n\n");
            fflush(stdin);
            fgets(userAnswer, 100, stdin);
            deleteEnter(userAnswer, 100);
            char *criteria = (char *) calloc(100, sizeof(char));
            if (!(strcmp(userAnswer, "all") == 0)) {
                fflush(stdin);
                printf("\nEnter criteria\n");
                fgets(criteria, 100, stdin);
                deleteEnter(criteria, 100);
            }
            if (strcmp(userAnswer, "all") == 0 ||
            strcmp(userAnswer, "name") == 0 ||
            strcmp(userAnswer, "type") == 0 ||
            strcmp(userAnswer, "year") == 0){
                for (int i = 0; i < filmsAmount; ++i) {
                    curPos = outputFromFile(f, &film, argv, curPos, userAnswer, criteria);
                }
            }
        } else {
            printf("\nSomething went wrong... Try again\n");
        }
    }
}

int main(__attribute__((unused)) int argc, char *argv[]){
    FILE *f = NULL;
    if(argv[1] == NULL){
        printf("\nYou entered nothing in command line\n");
        return 1;
    }
    if(!(f = fopen(argv[1], "ab+"))){
        printf("\nUnable to open file\n");
        exit(1);
    }
    fclose(f);
    struct info film = {};
    loop(f, film, argv);
}
