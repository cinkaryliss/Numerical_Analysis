#include <stdio.h>
#include <math.h>
#include "calc_data.h"

#define N_DATA 7501

double xfunc(double, double);
double yfunc(double, double);
//double t[N_DATA], x[N_DATA], y[N_DATA];

unsigned int calc_data(unsigned int n_step, double h, double t[], double x[], double y[]){
    int i;
    //int n_step;
    //double h;
    
    //初期条件
    //t[0] = 0.0;
    //x[0] = 2.0;
    //y[0] = 0.0;
    
    //h = 0.002; //刻み幅
    //n_step = 7500;  //ステップ数
    
    //オイラー法の計算
    for(i = 0; i <= n_step; i++){
        y[i+1] = y[i] + h*yfunc(x[i], t[i]);
        x[i+1] = x[i] + h*xfunc(y[i], t[i]);
        t[i+1] = t[i] + h;
    }
    
    //計算結果の表示
    for(i = 0; i <= n_step; i += 50)
        //printf("%lf | %lf\n", t[i], x[i]);
    
    return n_step;
}

//dx/dt = y = f(x,t)
double yfunc(double x, double t){
    return -sin(x);
}

double xfunc(double y, double t){
    return y;
}