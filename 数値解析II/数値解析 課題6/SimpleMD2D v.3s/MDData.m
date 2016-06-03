//
//  MDData.m
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "MDData.h"
#import "SimpleMD.h"

@implementation MDData

@synthesize currentEns, prevEns, initted;

- (id)initEnsembleOfNumber: (int)pnum
{
    [super init];
    
    if (alloc_ensemble_array(&currentEns, pnum) == FALSE)
        return nil;

    currentEns.number = pnum;
    currentEns.v2Mean = 0.0;
    currentEns.mass = 1.0;

    if (alloc_ensemble_array(&prevEns, pnum) == FALSE)
        return nil;

    prevEns.number = pnum;
    prevEns.v2Mean = 0.0;
    prevEns.mass = 1.0;
    
    initted = NO;
    
	return self;
}

- (void)dealloc
{
	free_ensemble_array(&currentEns);
    free_ensemble_array(&prevEns);
	[super dealloc];
}
 

int alloc_ensemble_array(Ensemble *ens, int anum)
{
    double  *dp;
    
    if ((dp = (double *)malloc(sizeof(double) * anum)) == NULL) {
        return FALSE;
    }
    ens->rx = dp;
    if ((dp = (double *)malloc(sizeof(double) * anum)) == NULL) {
        return FALSE;
    }
    ens->ry = dp;
    if ((dp = (double *)malloc(sizeof(double) * anum)) == NULL) {
        return FALSE;
    }
    ens->fx = dp;
    if ((dp = (double *)malloc(sizeof(double) * anum)) == NULL) {
        return FALSE;
    }
    ens->fy = dp;
    
    return TRUE;
}

void free_ensemble_array(Ensemble *ens)
{
    free(ens->rx);
    free(ens->ry);
    free(ens->fx);
    free(ens->fy);
}

@end


