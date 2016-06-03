/*
 *  move.c
 *  SimpleMD2D
 *
 *  Created by Takao Inokuma on 16/01/06.
 *  Copyright 2016 Takao Inokuma. All rights reserved.
 *
 */

#include "SimpleMD.h"

double move(Ensemble *current_ens, Ensemble *prev_ens, double l, double dt)
{

//   戻り値 : 粒子の速度の2乗の平均値 -> vms/n

//   current_ens : 粒子の現在の座標等
//   prev_ens    : 粒子の１ステップ前の座標等
//   l           : 正方形スーパーセルの1辺の長さ
//   dt          : 時間ステップ幅
        
    double  *rx0, *ry0, *rx, *ry, *fx, *fy;
    double  vms, m;
    int     i, n;

    rx0 = prev_ens->rx;         //   rx0[i] : i番目の粒子の1ステップ前のx座標
    ry0 = prev_ens->ry;         //   ry0[i] : i番目の粒子の1ステップ前のy座標
    rx = current_ens->rx;       //   rx[i]  : i番目の粒子の現在のx座標
    ry = current_ens->ry;       //   ry[i]  : i番目の粒子の現在のy座標
    fx = current_ens->fx;       //   fx[i]  : i番目の粒子に働く力のx方向成分
    fy = current_ens->fy;       //   fy[i]  : i番目の粒子に働く力のy方向成分
    n = current_ens->number;    //     n    : 粒子数
    m = current_ens->mass;      //     m    : 粒子の質量
    
	vms = 0.0;
    double rxnext, rynext, vx, vy;
    for (i = 0; i < n; i++) {
        rxnext = 2.0*rx[i]-rx0[i]+pow(dt, 2.0)*fx[i]/m;
        rynext = 2.0*ry[i]-ry0[i]+pow(dt, 2.0)*fy[i]/m;
        
        rx0[i] = rx[i];
        ry0[i] = ry[i];
        
        rx[i] = rxnext;
        ry[i] = rynext;
        
        rx[i] = rx[i] - round(rx[i]/l)*l;
        ry[i] = ry[i] - round(ry[i]/l)*l;
        
        vx = rx[i] - rx0[i];
        vy = ry[i] - ry0[i];
        
        vms += (pow((vx-round(vx/l)*l)/dt, 2.0) + pow((vy-round(vy/l)*l)/dt, 2.0));
    }
    
    return vms/n;
}