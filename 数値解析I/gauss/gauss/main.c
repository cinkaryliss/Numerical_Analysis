#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pibot (int);

int n = 3;

double a[3][4]= {{4, 1, 1, 9},
    {1, 3, 1, 10},
    {2, 1, 5, 19}};

int main (void){
    int i, j, k;
    double p;
    
    //前進消去
    for (k = 0; k <= n-1; k++){
        p = pibot(k);
        for(j = k+1; j <= n; j++){
            a[k][j] = a[k][j]/p;
        }
        
        for(i = k+1; i <= n-1; i++){
            for(j = k+1; j <= n; j++){
                a[i][j] = a[i][j]-(a[i][k]*a[k][j]);
            }
        }
    }
    
    //交代代入
    for(k = n-2; k >= 0; k--){
        for(i = k+1; i <= n-1; i++){
            a[k][n] = a[k][n]-(a[k][i]*a[i][n]);
        }
    }
    
    //結果の表示
    for(k = 0; k < n; k++){
        for(i = 0; i < n+1; i++){
            printf("%f ", a[k][i]);
        }
        printf("\n");
    }
}

double pibot (int k){
    int j;
    int l = k;
    double p = a[k][k];
    for(j = k+1; j <= n-1; j++){
        if(fabs(p) < fabs(a[j][k])){
            l = j;
            p = a[j][k];
        }
    }
    if(l != k){
        for(j = k; j <= n; j++){
            double w = a[k][j];
            a[k][j] = a[l][j];
            a[l][j] = w;
        }
    }
    return p;
}