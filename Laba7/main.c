#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int main() {

    //объявление переменных и указателей

    int rows,columns;
    int **arr;
    int amountOfNegative=0;
    int *arrOfNeg;

    //ввод переменных

    printf("Enter amount of rows\n");
    scanf("%d",&rows);
    printf("Enter amount of columns\n");
    scanf("%d",&columns);

    //выделение памяти и ввод матрицы

    arr=(int**)malloc((rows)*sizeof (int*));
    for(int i=0;i<rows;i++)
    {
        arr[i]=(int*)malloc(columns*sizeof(int));
        for (int j = 0; j < columns; j++) {
            printf("array[%d][%d]=",i,j);
            scanf("%d",&arr[i][j]);
        }
    }
    printf("\n");

    //вывод начальной матрицы

    printf("Your matrix looks like that:\n");
    for(int i=0;i<rows;i++)
    {
        for (int j = 0; j < columns; j++) {
            printf(" %4d ",arr[i][j]);

        }
        printf("\n");
    }

    //нахождение количества отрицательных чисел

    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(arr[i][j]<0){
                amountOfNegative++;
            }
        }
    }

    //вывод количества отрицательных чисел в матрице и выделение памяти для буферного массива в котором
    //будут храниться и сортироваться отрицательные числа

    printf("Amount of negative: %d\n\n",amountOfNegative);
    arrOfNeg=(int*)malloc(amountOfNegative*sizeof(int));

    //замена отрицательных чисел нулями и запись отрицательных чисел в массив сортировки

    int b=0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(arr[i][j]<0){
                arrOfNeg[b]=arr[i][j];
                arr[i][j]=0;
                b++;
            }
        }
    }

    //вывод неотсортированного массива

    printf("Array of unsorted negative values looks like:\n");
    for(int i=0;i<amountOfNegative;i++)
    {
        printf(" %4d ",arrOfNeg[i]);
    }
    printf("\n\n");

    //сортировка чисел в массиве

    for(int i = 0 ; i < amountOfNegative - 1; i++) {
        for(int j = 0 ; j < amountOfNegative - i - 1 ; j++) {
            if(arrOfNeg[j] > arrOfNeg[j+1]) {
                int tmp = arrOfNeg[j];
                arrOfNeg[j] = arrOfNeg[j+1] ;
                arrOfNeg[j+1] = tmp;
            }
        }
    }

    //вывод отсортированного массива

    printf("Array of sorted negative values looks like:\n");
    for(int i=0;i<amountOfNegative;i++)
    {
        printf(" %4d ",arrOfNeg[i]);
    }
    printf("\n\n");

    //запись отсортированных чисел в матрицу

    int s=0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(arr[i][j]==0)
            {
                arr[i][j]=arrOfNeg[s];
                s++;
            }
        }
    }

    //вывод новой матрицы

    printf("New sorted matrix looks like that\n");
    for(int i=0;i<rows;i++)
    {
        for (int j = 0; j < columns; j++) {
            printf(" %4d ",arr[i][j]);
        }
        printf("\n");
    }
    free(arr);
    free(arrOfNeg);
    system("pause");
    return 0;
}