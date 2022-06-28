#include <stdio.h>
#include <stdlib.h>
int main() {
    printf("Enter the variable x\n");
    float x;
    float y;
    scanf("%f",&x);
    if(x>0.2)
    {
        y=(float)((x*x)+(0.5*x)+0.2);
    }
    if (x<=0.2)
    {
        y=1;
        printf("You entered number less then 0.2!\n");
    }
    printf("%s""%f""%s""%f""%s","Value of your function with x = ",x," is ",y,"\n");
    system("pause");
    return 0;
}
