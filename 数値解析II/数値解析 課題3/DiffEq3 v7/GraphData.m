//
//  GraphData.m
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "GraphData.h"


@implementation GraphData

@synthesize tData;
@synthesize xData;
@synthesize yData;
@synthesize n_max;
@synthesize n_data, steps;
@synthesize t0, x0, y0, intv;
@synthesize region_x, region_y;

- (id)init 
{
	void	*tp, *xp, *yp;
	unsigned int	byteLength;
	
	n_max = 200000;
	byteLength = sizeof(double) * n_max;
	if ((tp = malloc(byteLength)) == NULL) {
		NSLog(@"Memory allocation error (t).\n");
		exit(1);
	}
	if ((xp = malloc(byteLength)) == NULL) {
		NSLog(@"Memory allocation error (x).\n");
		exit(1);
	}
	if ((yp = malloc(byteLength)) == NULL) {
		NSLog(@"Memory allocation error (y).\n");
		exit(1);
	}
	
	[super init];
	[self setTData:[NSData dataWithBytesNoCopy:tp length:byteLength freeWhenDone:YES]];
	[self setXData:[NSData dataWithBytesNoCopy:xp length:byteLength freeWhenDone:YES]];
	[self setYData:[NSData dataWithBytesNoCopy:yp length:byteLength freeWhenDone:YES]];
	n_data = 0;
	region_x = region_y = CGRectMake(0.0, 0.0, 1.0, 1.0);

    intv = 0.0001;
    steps = 5000;
    t0 = 0.0;
    x0 = 0.0;
    y0 = 0.0;

    
	return self;
}

- (void)findRegion
{
	int		i;
	double	tmin, tmax, xmin, xmax, ymin, ymax, ts, xys;
	double	*tp = (double *)[tData bytes];
	double	*xp = (double *)[xData bytes];
	double	*yp = (double *)[yData bytes];
	
	tmin = tmax = tp[0];
	xmin = xmax = xp[0];
	ymin = ymax = yp[0];
	for (i = 1; i <= n_data; i++) {

		if (tp[i] < tmin)
			tmin = tp[i];
		else if (tp[i] > tmax)
			tmax = tp[i];
		
		if (xp[i] < xmin)
			xmin = xp[i];
		else if (xp[i] > xmax)
			xmax = xp[i];

		if (yp[i] < ymin)
			ymin = yp[i];
		else if (yp[i] > ymax)
			ymax = yp[i];
	}
    
    if ((ts = tmax - tmin) == 0.0)
        ts = 1.0;
    if ((xys = xmax - xmin) == 0.0)
        xys = 1.0;
	region_x = CGRectMake(tmin, xmin, ts, xys);

    if ((xys = ymax - ymin) == 0.0)
        xys = 1.0;
	region_y = CGRectMake(tmin, ymin, ts, xys);
}

@end
