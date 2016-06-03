#include <stdio.h>
#include <math.h>

double func1(double); //関数のプロトタイプ宣言

int main(void)
{
    int j; //ループ制御変数
    int n; //分割数
    double a; //積分範囲の始まり
    double b; //積分範囲の終わり
    double h;
    
    printf("積分範囲の始まりを入力してください：");
    scanf("%lf", &a);
    printf("積分範囲の終わりを入力してください：");
    scanf("%lf", &b);
    printf("分割数を入力してください：");
    scanf("%i", &n);
    
    h = (b-a)/(2*n);
    
    double sum1 = 0.0, sum2 = 0.0, sum;
    
    for (j=1; j <= n-1; j++){
        sum1 = sum1 + func1(a+h*(j*2-1));
        sum2 = sum2 + func1(a+h*j*2);
    }
    
    sum1 = sum1 + func1(a+h*(n*2-1));
    sum = func1(a) + func1(b) + sum1 * 4.0 + sum2 * 2.0;
    sum = sum * h/3.0;
    
    printf("N=%11i Answer=%21.18g Err=%g\n", n, sum, fabs(sum-0.2)/0.2); //結果の出力
}

double func1(double x)
{
    return x*x*x*x; //x^4
}
