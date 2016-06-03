#include <stdio.h>
#include <math.h>

double f(double);

int main(void)
{
    double a, b, c;
    double e; //許容誤差
    
     do{
        printf("aを入力：");
        scanf("%lf", &a);
        printf("bを入力：");
        scanf("%lf", &b);
     }while (f(a)*f(b) > 0);
        
    //printf("許容誤差を入力：");
    //scanf("%lf", &e);
    e = pow(10.0,-6.0);
    
    do{
        c = (a+b)/2;
        
        if (f(c) == 0){
            printf("Answer=%lf\n", c);
            return 0;
        }
        
        else{
            if (f(a)*f(c) < 0)
                b = c;
            else
                a = c;
        }
        
        printf("c=%lf\n", b-a);
        
    }while (b-a > e);
    
    printf("Answer=%lf\n", (a+b)/2);
    
    return 0;
}

double f(double x)
{
    double s = sin(pow(x,2.0))-0.5;
    return s;
}