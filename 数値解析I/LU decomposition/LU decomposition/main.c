#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
    int i,j,k;
    int N, M;
    int L, iw;
    int mm[1000];
    double b[1000],x[1000],y[1000];
    double p, w;
    char buf[1024];
    FILE *fp;
        
    double **a, *ap;
        
    //ファイルオープン
    if((fp = fopen("matdata1000w.txt","r")) == NULL){
        printf("File open error.\n");
        return 1;
    }
        
    //行数の取得
    fgets(buf, 1024, fp);
    M = atoi(buf);
    //列数の取得
    fgets(buf, 1024, fp);
    N = atoi(buf);
        
    //2次元配列の領域確保
    if((a = (double **)malloc(sizeof(double *) * M)) == NULL){
        printf("Memory allocation error.\n");
        return 1;
    }
    if((ap = (double *)malloc(sizeof(double) * M * N)) == NULL){
        printf("Memory allocation error.\n");
        return 1;
    }
    
    for(i = 0; i < M; i++)
        a[i] = ap + N * i;
        
    //2次元配列aに要素を代入
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            fgets(buf, 1024, fp);
            a[i][j] = atof(buf);
        }
    }
    
    for(j = 0; j < M; j++){
        b[j] = a[j][N-1];
    }
    
    //LU分解
    for(i = 0; i < M; i++){
        mm[i] = i;
    }
    
    for(k = 0; k < M; k++){
        //ピボット選択
        L = k;
        p = a[k][k];
        for(j = k+1; j < M; j++){
            if(fabs(p) < fabs(a[j][k])){
                L = j;
                p = a[j][k];
            }
        }
        if(L != k){
            for(j = 0; j < M; j++){
                w = a[k][j];
                a[k][j] = a[L][j];
                a[L][j] = w;
            }
            iw = mm[k];
            mm[k] = mm[L];
            mm[L] = iw;
        }
        //ピボット選択終了
        
        for(j = k+1; j < M; j++){
            a[k][j] = a[k][j]/p;
        }
        for(i = k+1; i < M; i++){
            for(j = k+1; j < M; j++){
                a[i][j] = a[i][j]-a[i][k]*a[k][j];
            }
        }
    }
    
    //前進代入
    for(k = 0; k < M; k++){
        y[k] = b[mm[k]];
        for(j = 0; j < k; j++){
            y[k] = y[k] - a[k][j]*y[j];
        }
        y[k] = y[k]/a[k][k];
    }
    
    //後退代入
    for(k = M-1; k >= 0; k--){
        x[k] = y[k];
        for(j = k+1; j < M; j++){
            x[k] = x[k] - a[k][j]*x[j];
        }
    }
    
    //答えの表示
    for(i = 0; i < M; i++){
        printf("%lf\n", x[i]);
    }
    
}