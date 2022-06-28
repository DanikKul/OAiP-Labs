#include <stdio.h>
#include <stdlib.h>
int main() {
    int array[10];
    int currentValue;
    int b = 1;
    for (int i = 0; i < 10; i++, b++) {
        printf("%s%d%s","Enter the ",b," number\n");
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < 5; i++) {
        currentValue = array[i];
        array[i] = array[9 - i];
        array[9 - i] = currentValue;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d", array[i]);
        printf("\n");
    }
    printf("The end of the program\n");
    system("pause");
}