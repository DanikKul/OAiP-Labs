#include <stdio.h>
#include <stdlib.h>
void repeatvoid(int size)
{

    //ввод значений
    printf("Enter a value\n");
    int i;
    scanf("%d", &i);

    //логическое условие т.е. пока size не станет равным 1 идет рекурсия уменьшая size
    //когда логическое условие не выполнится рекурсия будет выполнять себя size раз

    if (size > 1) repeatvoid(size - 1);
    printf("%d number is %d\n", size, i);
}

int main()
{

    //ввод количества переменных

    printf("Enter amount of numbers\n");
    int amOfValues;
    scanf("%d", &amOfValues);

    //вызов рекурсивной функции

    repeatvoid(amOfValues);
    system("pause");
    return 0;
}