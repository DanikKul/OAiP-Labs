#include <stdio.h>
#include <stdlib.h>
int main() {
    int rows;      //variables & initializing variables
    int columns;
    int b=1;
    int sum=0;
    printf("Enter amount of rows\n");
    scanf("%d",&rows);
    printf("Enter amount of columns\n");
    scanf("%d",&columns);
    int array[rows][columns];
    for (int i = 0; i < rows; i++) { //Enter the matrix
        for(int j=0;j<columns;j++,b++) {
            printf("%s%d%s", "Enter the ", b, " number\n");
            scanf("%d", &array[i][j]);
        }
    }
    for (int i = 0; i < rows; i++) {  //Show matrix
        for(int j=0;j<columns;j++,b++) {
            printf("%s%4d%s"," ", array[i][j]," ");
        }
        printf("\n");
    }
    for(int i=0;i<rows;i++)  //checking every variable for its value and its position in matrix
    {                        //task is not full because it is confusing from what position program should start 1 or 0
        for(int j=0;j<columns;j++) //program starts from 1
        {
            if(i%2!=0 && j%2!=0 && array[i][j]%2!=0)
            {
                sum+=array[i][j]; //calculating sum
            }
        }
    }
    if(sum==0) //if returns 0 then message about exception
    {
        printf("Array doesn't have elements which fits to the condition\n");
    }
    if(sum!=0) //returns sum
    {
        printf("%s%d%s","Your sum is ",sum,"\n");
    }
    system("pause");
    return 0;
}
