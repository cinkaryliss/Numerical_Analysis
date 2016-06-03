#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);

int main(void)
{
    int count, i, j, k;
    double a, b, c[8], x, y;
    double e = pow(10.0,-8.0); //許容誤差

    count = 0;
    
    while (count < 8){
        k = 1;
        while (k == 1){
            j = 1;
            do{
                x = ((double)rand()/RAND_MAX)*5;
                y = ((double)rand()/RAND_MAX)*5;
                if (x > y)
                    b = x, a = y;
                else
                    a = x, b = y;
            }while (f(a)*f(b) > 0);
            
            do{
                c[count] = (a+b)/2;
        
                if (f(c[count]) == 0){
                    printf("Answer=%lf\n", c[count]);
                    break;
                }
            
                else{
                    if (f(a)*f(c[count]) < 0)
                        b = c[count];
                    else
                        a = c[count];
                }
            }while (b-a > e);

            for (i = 0;i < count; i++){
                if(c[count] <= c[i]+e && c[count] >= c[i]-e)
                    j = 0;
            }
            
            if (j == 1){
                printf("Answer=%lf\n", c[count]);
                count++;
                k = 0;
            }
        }
    }
    return 0;
}

double f(double x)
{
    double s = sin(pow(x,2.0))-0.5;
    return s;
}