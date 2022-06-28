#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int main()
{
    //объявление переменных и указателей

    int rows;
    int absMaxValue=0;
    int buffer_i;
    int buffer_j;

    //ввод порядка матрицы

    printf("Enter amount of rows in array: ");
    scanf("%d", &rows);
    int *arr[rows];

    //ввод матрицы и выделение памяти

    for (int i = 0; i < rows; ++i)
    {
        arr[i]=(int*) malloc(rows*sizeof(int));
        for (int j = 0; j < rows; ++j)
        {
            printf("array[%d][%d]=",i,j);
            scanf("%d",&arr[i][j]);
        }
    }

    //вывод начальной матрицы


    printf("Current matrix looks like that:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            if(abs(absMaxValue)<abs(arr[i][j]))
            {
                absMaxValue=arr[i][j];
                buffer_i=i;
                buffer_j=j;
            }
            printf(" %4d ",arr[i][j]);
        }
        printf("\n");
    }

    //замена строк и стобцов нулями(показывает какие строку и столбец удаляем)

    for(int i=0;i<rows;i++)
    {
        arr[buffer_i][i]=0;
        arr[i][buffer_j]=0;
    }

    //вывод информации о макс значении в матрице

    printf("%s%d%s","\nAbsolute maximal value in matrix is ",absMaxValue,"\n");
    printf("%s%d%s","Row: ",buffer_i,"\n");
    printf("%s%d%s","Column: ",buffer_j,"\n");

    //вывод промежуточной матрицы

    printf("\nMiddle matrix looks like that \n");
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<rows; j++)
        {
            printf("%3d" , arr[i][j]);
        }
        printf("\n");
    }

    //объявление и выделение памяти

    int *arrNext[rows-1];
    for (int i = 0; i<(rows-1); i++)
    {
        arrNext[i] = (int*)malloc((rows-1)*sizeof(int));
    }

    //удаление строки и столбца

    int x = 0;
    for( int i = 0; i<rows; ++i ) {
        int y = 0;
        if( i != buffer_i ) {
            for( int j = 0; j<rows; ++j ) {
                if( j != buffer_j ) {
                    arrNext[x][y] = arr[i][j];
                    ++y;
                }
            }
            ++x;
        }
    }

    //вывод конечной матрицы

    int rows2=rows-1;
    printf("\nNew matrix looks like that: \n");
    for (int i = 0; i<rows2; i++) {
        for (int j = 0; j < rows2; j++) {
            printf("%4d", arrNext[i][j]);
        }
        printf("\n");
    }
    free(*arr);
    free(*arrNext);
    system("pause");
    return 0;
}