#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void){
    int i, j, k, l;
    int N, M;
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
    
    //前進消去
    for (k = 0; k < M; k++){
        //ピボット選択
        l = k;
        p = a[k][k];
        //部分ピボット選択
        for(j = k+1; j < M; j++){
            if(fabs(p) < fabs(a[j][k])){
                l = j;
                p = a[j][k];
            }
        }
        //列の入れ替え（lが行数）
        if(l != k){
            for(j = 0; j < N; j++){
                w = a[k][j];
                a[k][j] = a[l][j];
                a[l][j] = w;
            }
        }
        //ピボット選択終了
        
        for(j = k+1; j < N; j++){
            a[k][j] = a[k][j]/p;
        }
        
        for(i = k+1; i < M; i++){
            for(j = k+1; j < N; j++){
                a[i][j] = a[i][j]-(a[i][k]*a[k][j]);
            }
        }
    }
    
    //後退代入
    for(k = N-2; k >= 0; k--){
        for(i = k+1; i < M; i++){
            a[k][N-1] = a[k][N-1]-(a[k][i]*a[i][N-1]);
        }
    }
    
    //計算結果の表示
    for(i = 0; i < M; i++){
        printf("%lf\n", a[i][N-1]);
    }
}