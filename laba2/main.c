#include <stdio.h>
#include <stdlib.h>

void inputNumbers(FILE *file, int amount);
void rewriteNumbers(FILE *f, FILE *g);
fpos_t negativePosition(FILE *f, fpos_t curPos);
fpos_t positivePosition(FILE *f, fpos_t curPos);

int main() {
    FILE *f, *g;
    if (!(f = fopen("/Users/dankulakovich/CLionProjects/laba2/input.txt", "w")) ||
    !(g = fopen("/Users/dankulakovich/CLionProjects/laba2/output.txt", "w"))){
        printf("Невозможно открыть файл\n");
        return 1;
    }
    int amount = 1;
    printf("Введите количество вводимых чисел\nЧисло должно быть кратно 20\n");
    while(amount < 1 || amount % 20 != 0){
        fflush(stdin);
        while(!scanf("%d", &amount)){
            fflush(stdin);
            printf("Ошибка: вы ввели не число!\n");
        }
        if(amount < 1 || amount % 20 != 0){
            printf("Ошибка: число должно быть кратно 20!\n");
        }
    }
    inputNumbers(f, amount);
    rewriteNumbers(f, g);
    fclose(f);
    fclose(g);
    return 0;
}

void inputNumbers(FILE *file, int amount){
    int number = 0, arr[20];
    printf("Вводите любые числа кроме нуля\n");
    for (int i = 0; i < amount; ++i) {
        number = 0;
        fflush(stdin);
        if((i / 10) % 2 == 0){
            printf("Введите положительное число\n");
        } else {
            printf("Введите отрицательное число\n");
        }
        while(number == 0) {
            fflush(stdin);
            while (!scanf("%d", &number)) {
                fflush(stdin);
                printf("Ошибка: вы ввели не число!\n");
            }
            if(number == 0){
                printf("Ошибка: число не должно быть равно нулю!\n");
            }
        }
        if(((i / 10) % 2 == 0 && number > 0) || ((i / 10) % 2 == 1 && number < 0)){
            fprintf(file, "%d", number);
            fprintf(file, "%c", ' ');
        } else {
            printf("Ошибка: вы ввели число не с противоположным знаком\n");
            i--;
        }
    }
    fclose(file);
}

fpos_t negativePosition(FILE *f, fpos_t curPos){
    f = fopen("/Users/dankulakovich/CLionProjects/laba2/input.txt", "r");
    int number;
    fsetpos(f, &curPos);
    fscanf(f, "%d", &number);
    while(number > 0 && !feof(f)){
        fgetpos(f, &curPos);
        fscanf(f, "%d", &number);
    }
    return curPos;
}

fpos_t positivePosition(FILE *f, fpos_t curPos){
    f = fopen("/Users/dankulakovich/CLionProjects/laba2/input.txt", "r");
    int number;
    fsetpos(f, &curPos);
    fscanf(f, "%d", &number);
    while(number < 0 && !feof(f)){
        fgetpos(f, &curPos);
        fscanf(f, "%d", &number);
    }
    fsetpos(f, &curPos);
    return curPos;
}

void rewriteNumbers(FILE *f, FILE *g){
    f = fopen("/Users/dankulakovich/CLionProjects/laba2/input.txt", "r");
    g = fopen("/Users/dankulakovich/CLionProjects/laba2/output.txt", "w");
    int number = 0;
    fpos_t posPos = positivePosition(f, 0), negPos = negativePosition(f, 0), endPos, curPos = 0;
    fseek(f, 0, 2);
    fgetpos(f, &endPos);
    fsetpos(f, &posPos);
    while (curPos != endPos - 1) {
        for (int i = 0; i < 2; ++i) {
            fsetpos(f, &posPos);
            for (int j = 0; j < 5; ++j) {
                fscanf(f, "%d", &number);
                fprintf(g, "%d ", number);
            }
            fgetpos(f, &posPos);
            fsetpos(f, &negPos);
            for (int j = 0; j < 5; ++j) {
                fscanf(f, "%d", &number);
                fprintf(g, "%d ", number);
            }
            fgetpos(f, &negPos);
        }
        fprintf(g, "%s", "\n");
        fgetpos(f, &curPos);
        negPos = negativePosition(f, curPos);
        posPos = positivePosition(f, curPos);
    }
}