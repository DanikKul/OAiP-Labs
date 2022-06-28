#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int array[10];
    int arrayHelp[10];
    int b = 1;
    for (int i = 0; i < 10; i++, b++) {
        printf("Enter the ");
        printf("%d", b);
        printf(" number\n");
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < 10; i++) {
        arrayHelp[i]=array[9-i];
    }

    for (int i = 0; i < 10; i++) {
        printf("%d", arrayHelp[i]);
        printf("\n");
    }
    printf("The end of the program\n");
    system("pause");

}