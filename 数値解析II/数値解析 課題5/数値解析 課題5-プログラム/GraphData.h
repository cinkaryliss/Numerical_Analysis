//
//  GraphData.h
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface GraphData : NSObject {
	NSData	*tData;
	NSData	*xData;
	NSData	*yData;
	unsigned int n_max;
	unsigned int n_data, steps;
	double	t0, x0, y0, intv;
	CGRect	region_x, region_y;
}

@property (readwrite, retain)  NSData *tData;
@property (readwrite, retain)  NSData *xData;
@property (readwrite, retain)  NSData *yData;
@property (readwrite, assign)  unsigned int n_max;
@property (readwrite, assign)  unsigned int n_data, steps;
@property (readwrite, assign)  double t0, x0, y0, intv;
@property (readwrite, assign)  CGRect region_x, region_y;

- (void)findRegion; 

@end
