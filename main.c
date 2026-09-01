#include <stdio.h>

int main() {
    char name[50];
    char mayor[50];
    int population;
    printf("---------------------------Welcome to Windhoek Municipality---------------------------\n");
    
    printf("Enter municipal Name :\n");
    scanf("%s",& name);

    printf("enter the mayors name :\n");
    scanf("%s",&mayor);
    
    printf("what is the population in whindhoek size :\n");
    scanf("%d",&population);

    //printf("hello %s",name);
    printf("\nmayor name is : %s and the poulation in windhoek is : %d", mayor,population );
    return 0;

}