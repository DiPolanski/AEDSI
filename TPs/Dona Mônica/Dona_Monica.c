#include <stdio.h>
#include <stdlib.h>

int main()
{


    int Monica, filho1, filho2;

    do{


    scanf("%i", &Monica);
    }while(Monica < 40 || Monica > 110);

    do{

    scanf("%i", &filho1);

    }while (filho1 < 1 || filho1 > Monica);

    do{

    scanf("%i", &filho2);

    }while (filho1 == filho2);

    int filho3;

    filho3= Monica - (filho1 + filho2) ;

    printf("%i", filho3);





    return 0;
}
