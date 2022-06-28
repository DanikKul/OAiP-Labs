#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
int main() {

    //объявление переменных и локализация

	setlocale(LC_ALL,"Russian");
	char* line;
	int amOfSym;
    int amOfSym2,j;

    //ввод и объявление чара с помощью указателей (динамическая строка)

	printf("Enter amount of symbols, human\n");
	scanf("%d",&amOfSym);
	line = (char*)calloc(amOfSym,sizeof(char));
    printf("Enter encrypted text, human\n");
	getchar();
	gets(line);
    amOfSym2= strlen(line);

    //подсчет размера новой строки

    for(int i=0;i<amOfSym;i++)
    {
        if(line[i]=='#')
        {
            amOfSym2=amOfSym2-2;
        }
    }

    //создание новой строчки и замена всех удаляемых символов на #

    char* line2;
    line2 = (char*)calloc(amOfSym2,sizeof(char));
    for (int k = 0; k < strlen(line); ++k) {
        if (line[k] == '#' && line[k-1]=='#') {
            for(j=k;;j--)
            {
                if(line[j]!='#')
                {
                    line[j]='#';
                    break;
                }
            }
        }
        if(line[k]=='#'){
            line[k-1]='#';
        }
    }

    //запись отсортированной строчки в новую

    j=0;
    for(int i=0;i<strlen(line);i++)
    {
        if(line[i]!='#'){
            line2[j]=line[i];
            j++;
        }
    }

    //вывод и освобождение памяти

    printf("Here your decrypted text:\n");
    puts(line2);
    free(line);
    free(line2);
    system("pause");
    return 0;
}