/*
 *  init_ensemble.c
 *  SimpleMD2D
 *
 *  Created by Takao Inokuma on 15/09/09.
 *  Copyright 2015 Takao Inokuma. All rights reserved.
 *
 */

#include "SimpleMD.h"

void mom_correct(int, double *, double *);
void alloc_v(int, double **, double **);
void free_v(double *, double *);


void init_particles(double l, double rc, double dt, double temp, Ensemble *c_ens, Ensemble *p_ens)
{
    int		i, j, n, close_flag = 0;
    double	rxij, ryij, rijsq, crx0, cry0, *vx, *vy;
    double  *rx0, *ry0, *rx, *ry, *fx, *fy;
    double  int_max, vms;
    unsigned int    rnd[2];
    FILE	*fpr;
    
    rx0 = p_ens->rx;
    ry0 = p_ens->ry;
    fx = p_ens->fx;
    fy = p_ens->fy;
    rx = c_ens->rx;
    ry = c_ens->ry;
    n = c_ens->number;
    
    if ((fpr = fopen("/dev/urandom", "rb")) == NULL) {
        fprintf(stderr, "File '/dev/urandom' not open.\n");
        exit(3);
    }

    if (sizeof(int) == 8)
        int_max = (double)((unsigned int)0xffffffffffffffff) + 1.0;
    else if (sizeof(int) == 4)
        int_max = (double)((unsigned int)0xffffffff) + 1.0;
    else
        exit(20);

    i = 0;
    while (i < n) {
        fread(rnd, sizeof(int), 2, fpr);
        crx0 = l * (rnd[0] / int_max - 0.5);
        cry0 = l * (rnd[1] / int_max - 0.5);
        if (i != 0) {
            for (close_flag = 0, j = 0; j < i; j++) {
                rxij = crx0 - rx0[j];
                ryij = cry0 - ry0[j];
                rxij -= round(rxij / l) * l;
                ryij -= round(ryij / l) * l;
                rijsq = rxij * rxij + ryij * ryij;
                if (rijsq < 1.0) {
                    close_flag = 1;
                    break;
                }
            }
        }
        if (i == 0 || close_flag == 0) {
            rx0[i] = crx0;
            ry0[i] = cry0;
            i++;
        }
    }

    double	hsq2, cc0, cc10, cc11;

    hsq2 = dt * dt / 2.0;
    cc0 = 1.0 / p_ens->mass;
    
    alloc_v(n, &vx, &vy);
    
    vms = 0.0;
    for (i = 0; i < n; i++) {
        fread(rnd, sizeof(int), 2, fpr);
        cc10 = sqrt(-2.0 * temp * cc0 * log(rnd[0] / int_max));
        cc11 = 2.0 * PI * rnd[1] / int_max;
        vx[i] = cc10 * cos(cc11);
        vy[i] = cc10 * sin(cc11);
        vms += vx[i] * vx[i] + vy[i] * vy[i];
    }
    c_ens->v2Mean = p_ens->v2Mean = vms / n;

    mom_correct(n, vx, vy);
    force(p_ens, l, rc);

    for (i = 0; i < n; i++) {
        rx[i] = rx0[i] + dt * vx[i] + hsq2 * fx[i] * cc0;
        ry[i] = ry0[i] + dt * vy[i] + hsq2 * fy[i] * cc0;
    }

    free_v(vx, vy);
    fclose(fpr);
}

// ----------------------------------------------------------------------


void mom_correct(int n, double *vx, double *vy)
{
    int		i;
    double	momx, momy;
    
    momx = momy = 0.0;
    for (i = 0; i < n; i++) {
            momx += vx[i];
            momy += vy[i];
    }
    momx /= (double)n;
    momy /= (double)n;
    
    for (i = 0; i < n; i++) {
        vx[i] -= momx;
        vy[i] -= momy;
    }
}

void alloc_v(int n, double **vx, double **vy)
{
    if ((*vx = (double *)malloc(sizeof(double) * n)) == NULL)
        exit(100);
    if ((*vy = (double *)malloc(sizeof(double) * n)) == NULL)
        exit(101);
}

void free_v(double *vx, double *vy)
{
    free(vx);
    free(vy);
}

