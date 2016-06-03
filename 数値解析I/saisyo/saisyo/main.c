#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void){
    int i = 0;
    int j, l, m;
    int ret;
    int n;
    double a , b;
    double p, w;
    double k[3][4] = {};
    char buf[1024];
    FILE *fp;
    
    double *x, *y;
    
    //ファイルオープン
    if((fp = fopen("xydata2014.txt","r")) == NULL){
        printf("File open error.\n");
        return 1;
    }
    
    //データの組数の取得
    fgets(buf, 1024, fp);
    n = atoi(buf);
    
    //1次元配列の領域確保
    if((x = (double *)malloc(sizeof(double) * n)) == NULL){
        printf("Memory allocation error.\n");
        return 1;
    }
    if((y = (double *)malloc(sizeof(double) * n)) == NULL){
        printf("Memory allocation error.\n");
        return 1;
    }
    
    //1次元配列x,yに要素を代入
    while((ret = fscanf(fp, "%lf %lf", &a , &b)) != EOF){
        x[i] = a;
        y[i] = b;
        //printf("%lf %lf\n", x[i], y[i]);
        i++;
    }
    
    //2次式の最小二乗法
    //係数決め
    for(i = 0; i < n; i++){
        k[0][0] += pow(x[i],4);
        k[0][1] += pow(x[i],3);
        k[0][2] += pow(x[i],2);
        k[0][3] += pow(x[i],2)*y[i];
        k[1][0] = k[0][1];
        k[1][1] = k[0][2];
        k[1][2] += x[i];
        k[1][3] += x[i]*y[i];
        k[2][0] = k[0][2];
        k[2][1] = k[1][2];
        k[2][2] = n;
        k[2][3] += y[i];
    }
    
    //ガウスの消去法
    //前進消去
    for (j = 0; j < 3; j++){
        //ピボット選択
        l = j;
        p = k[j][j];
        //部分ピボット選択
        for(m = j+1; m < 3; m++){
            if(fabs(p) < fabs(k[m][j])){
                l = m;
                p = k[m][j];
            }
        }
        //列の入れ替え（lが行数）
        if(l != j){
            for(m = j; m < 4; m++){
                w = k[j][m];
                k[j][m] = k[l][m];
                k[l][m] = w;
            }
        }
        //ピボット選択終了
        
        for(m = j+1; m < 4; m++){
            k[j][m] = k[j][m]/p;
        }
        
        for(i = j+1; i < 3; i++){
            for(m = j+1; m < 4; m++){
                k[i][m] = k[i][m]-(k[i][j]*k[j][m]);
            }
        }
    }
    
    //後退代入
    for(m = 2; m >= 0; m--){
        for(i = m+1; i < 3; i++){
            k[m][3] = k[m][3]-(k[m][i]*k[i][3]);
        }
    }
    
    //答えの表示
    printf("answer = %lfx^2 + %lfx + %lf\n", k[0][3],k[1][3],k[2][3]);
    
    fclose(fp);
    free(x);
    free(y);
    return 0;
}