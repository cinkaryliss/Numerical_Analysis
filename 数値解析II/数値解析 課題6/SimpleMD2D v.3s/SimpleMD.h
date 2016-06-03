/*
 *  SimpleMD.h
 *  SimpleMD2D
 *
 *  Created by Takao Inokuma on 15/12/09.
 *  Copyright 2015 Takao Inokuma. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define		PI		3.1415926535897932


typedef struct {
    int     number;
    double  *rx, *ry, *fx, *fy, mass;
    double  v2Mean;
} Ensemble;


void init_particles(double, double, double, double, Ensemble *, Ensemble *);
void move_particles(double, double, double, Ensemble *, Ensemble *);
int alloc_ensemble_array(Ensemble *, int);
void free_ensemble_array(Ensemble *);


void force(Ensemble *, double, double);
double move(Ensemble *, Ensemble *, double, double);


/***/