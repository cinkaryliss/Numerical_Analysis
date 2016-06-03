#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);

int main(void){
    double x , x0;
    double dx = 0.001;
    double epa = 1.0*exp(-4) , epr = 1.0*exp(-8);
    double err , fd;
    int kaisu = 0;
    
    printf("初期値を入力してください：");
    scanf("%lf", &x);
    
    do{
        x0 = x;
        fd = (f(x0+dx) - f(x0))/dx;
        x = x0 -f(x0)/fd;
        err = fabs(x-x0)/(epa + epr * (fabs(x0)+fabs(x)));
        printf("x：%lf      err：%lf\n", x, err);
        kaisu ++;
    }while(err > 1);
    
    printf("繰り返し回数：%d\n", kaisu);
    
    return 0;
}

double f(double a){
    double b;
    b = (a+2)*(a-1)*(a-1);
    return b;
}