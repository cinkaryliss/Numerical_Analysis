//
//  main.c
//  daikei
//
//  Created by 上坂佳史 on 2014/06/27.
//  Copyright (c) 2014年 上坂佳史. All rights reserved.
//

#include <stdio.h>

double func1(double); //関数のプロトタイプ宣言

int main(void)
{
    int i, nmax;
    int n; //分割数
    double a; //積分範囲の始まり
    double b; //積分範囲の終わり
    double h, sum, x;
    
    printf("積分範囲の始まりを入力してください：");
    scanf("%lf", &a);
    printf("積分範囲の終わりを入力してください：");
    scanf("%lf", &b);
    printf("分割数を入力してください：");
    scanf("%i", &nmax);
    
    for (n = 2; n <= nmax; n++){
        h = (b-a)/n;
        sum = 0.0;
        
        for (i = 1; i <= n-1; n++){
        x = a + h * i;
        sum += func1(x);
        }
    
        sum += (func1(a) + func1(b))/2.0;
        sum *= h;
    
        printf("N=%3i Answer = %g\n", n, sum);
    }
}

double func1(double x)
{
    return x * x; //関数の定義（x^2）
}