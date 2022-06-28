#include <stdio.h>
#include <stdlib.h>
int main() {
    int b = 1;
    int amount=0;
    int x;
    int a=1;
    printf("Enter amount of values\n");
    scanf("%d",&x);
    int array[x];
    for (int i = 0; i < x; i++, b++) {
        printf("%s%d%s","Enter the ",b," number\n");
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < x; i++) {
        if(array[i]<0)
        {
            array[i]=0;
            amount++;
        }
    }
    int buff=amount;
    for(int i=0;i<buff;i++)
    {
        a*=amount--;
    }
    for (int i = 0; i < x; i++, b++) {
        printf("%d%s", array[i],"\n");
    }
    printf("%s%d%s","Your factorial is ",a,"\n");
    return 0;
}