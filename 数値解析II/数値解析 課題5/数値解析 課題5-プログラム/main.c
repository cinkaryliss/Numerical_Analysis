#include <stdio.h>
#include <math.h>
#include "calc_data.h"

#define R 2
#define L 0.01
#define C 63.3E-6

double yfunc(double, double, double);
double xfunc(double, double, double);

unsigned int calc_data(unsigned int n_step, double h, double t[], double x[], double y[])
{
    int i;
    double k1, k2, k3, k4, l1, l2, l3, l4;
    
    //4次ルンゲクッタ法の計算
    for(i = 0; i <= n_step; i++){
        k1 = yfunc(y[i], x[i], t[i]);
        l1 = xfunc(y[i], x[i], t[i]);
        k2 = yfunc(y[i]+k1*(h/2.0), x[i]+l1*(h/2.0), t[i]+h/2.0);
        l2 = xfunc(y[i]+k1*(h/2.0), x[i]+l1*(h/2.0), t[i]+h/2.0);
        k3 = yfunc(y[i]+k2*(h/2.0), x[i]+l2*(h/2.0), t[i]+h/2.0);
        l3 = xfunc(y[i]+k2*(h/2.0), x[i]+l2*(h/2.0), t[i]+h/2.0);
        k4 = yfunc(y[i]+k3*h, x[i]+l3*h, t[i]+h);
        l4 = xfunc(y[i]+k3*h, x[i]+l3*h, t[i]+h);
        
        y[i+1] = y[i] + (h/6.0)*(k1+2.0*k2+2.0*k3+k4);
        x[i+1] = x[i] + (h/6.0)*(l1+2.0*l2+2.0*l3+l4);
        t[i+1] = t[i] + h;
    }
    
    return n_step;
}

double yfunc(double y, double x, double t){
    double tmp;
    if (t >= 0.1 && t <= 0.2)
        tmp = -(R/L)*y - (1/(L*C))*x + sin(200*M_PI*t);
    else
        tmp = -(R/L)*y - (1/(L*C))*x;
    
    return tmp;
}

double xfunc(double y, double x, double t){
    return y;
}