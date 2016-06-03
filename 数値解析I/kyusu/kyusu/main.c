#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES

int main(void)
{
    double x, kai, beki, hugo, kou;
    double a = 0.0;
    double b = 1.0;
    double result = 0.0;
    double ensyu = M_PI;
    int n = 0;
    
    printf("xを入力してください：");
    scanf("%lf", &x);
    x = fmod(x, 2 * ensyu);
    
    if(x == 0){
        printf("n=1\n");
        return 0;
    }
    
    while (fabs(b) > 0.00000001){
        n++;
        int i, k;
        kai = 1;
        beki = 1;
        
        for(i = 1; i <= (2 * n - 1); i++){
            kai = kai * i;
        }
        
        hugo = pow(-1, (n % 2) + 1);
        
        for (k = 1; k <= (2 * n - 1); k++){
			beki = beki * x;
		}
        
        kou = (hugo * beki) / kai;
        result = result + kou;
        a = sin(x) - result;
        b = a / sin(x);
    }
    
    printf("n=%d\n", n);
    printf("絶対偏差：%30.30f\n", fabs(a));
    printf("相対偏差：%30.30f\n", fabs(b));
    
    return 0;
}