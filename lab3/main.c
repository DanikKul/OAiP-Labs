#include <stdio.h>
#include <stdlib.h>
int main() {

    int index;
    int a=1;
    int sum=0;
    int amount=0;

    printf("Enter the number of elements\n");
    scanf("%d",&index);

    int arrayOfElements[index];

    for(int i=0;i<index;i++,a++)
    {
        printf("Enter the ");
        printf("%d",a);
        printf(" member of the sequence\n");
        scanf("%d",&arrayOfElements[i]);
    }

    for (int i = 0; i < index; i++) {
        if((arrayOfElements[i]%5)==0 && (arrayOfElements[i]%7)!=0)
        {
            sum=sum+arrayOfElements[i];
            amount++;
        }
    }


    printf("%s""%d""%s","Your summed number is ",sum,"\n");
    printf("%s""%d""%s","Amount of numbers is ",amount,"\n");
    system("pause");
    return 0;
}

