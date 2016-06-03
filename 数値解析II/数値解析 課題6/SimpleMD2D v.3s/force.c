/*
 *  force.c
 *  SimpleMD2D
 *
 *  Created by Takao Inokuma on 16/01/06.
 *  Copyright 2016 Takao Inokuma. All rights reserved.
 *
 */

#include "SimpleMD.h"

void force(Ensemble *ens, double l, double rc)
{

//   戻り値 : なし

//   ens   : 粒子の現在の座標等
//   l     : 正方形スーパーセルの1辺の長さ
//   rc    : 臨界円の半径（粒子間力を計算する範囲）
        
    double  *fx, *fy, *rx, *ry;
    int		i, j, n;
    
    fx = ens->fx;      //   fx[i]  : i番目の粒子に働く力のx方向成分
    fy = ens->fy;      //   fy[i]  : i番目の粒子に働く力のy方向成分
    rx = ens->rx;      //   rx[i]  : i番目の粒子の現在のx座標
    ry = ens->ry;      //   ry[i]  : i番目の粒子の現在のy座標
    n = ens->number;   //     n    : 粒子数
    
    for (i = 0; i < n; i++)
        fx[i] = fy[i] = 0.0;
    
    double r2, rxx, ryy;
    
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if(i != j){
                rxx = (rx[i]-rx[j])-round((rx[i]-rx[j])/l)*l;
                ryy = (ry[i]-ry[j])-round((ry[i]-ry[j])/l)*l;
                r2 = pow(rxx, 2.0)+pow(ryy, 2.0);
                if(sqrt(r2) < rc){
                    fx[i] += 24.0*(2.0*pow(1.0/r2, 6.0)-pow(1.0/r2, 3.0))*(rxx/r2);
                    fy[i] += 24.0*(2.0*pow(1.0/r2, 6.0)-pow(1.0/r2, 3.0))*(ryy/r2);
                    fx[j] -= 24.0*(2.0*pow(1.0/r2, 6.0)-pow(1.0/r2, 3.0))*(rxx/r2);
                    fy[j] -= 24.0*(2.0*pow(1.0/r2, 6.0)-pow(1.0/r2, 3.0))*(ryy/r2);
                }
            }
		}
    }
}
