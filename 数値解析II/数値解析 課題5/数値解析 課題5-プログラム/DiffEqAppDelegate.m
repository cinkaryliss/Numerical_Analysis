//
//  DiffEqAppDelegate.m
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "DiffEqAppDelegate.h"
#include "calc_data.h"

@implementation DiffEqAppDelegate

@synthesize window;
@synthesize gView, gView2;
@synthesize gData;
@synthesize t0Value, x0Value, y0Value, intvValue, stepValue;
@synthesize tMax, tMin, xMax, xMin, yMax, yMin, autoRange, dataActive;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	
	gData = [[GraphData alloc] init];
	[gView setGData:gData];
	[gView2 setGData:gData];

	[self setValue:[NSNumber numberWithDouble:gData.t0] forKey:@"t0Value"];
	[self setValue:[NSNumber numberWithDouble:gData.x0] forKey:@"x0Value"];
	[self setValue:[NSNumber numberWithDouble:gData.y0] forKey:@"y0Value"];
	[self setValue:[NSNumber numberWithDouble:gData.intv] forKey:@"intvValue"];
	[self setValue:[NSNumber numberWithInteger:gData.steps] forKey:@"stepValue"];
	[self setValue:[NSNumber numberWithBool:YES] forKey:@"autoRange"];
	[self setValue:[NSNumber numberWithBool:NO] forKey:@"dataActive"];
}

- (IBAction)calc:(id)sender {
	
	double	*tp, *xp, *yp;
	
//	NSLog(@"'calc:' called.\n");
	
	tp = (double *)[[gData tData] bytes];
	xp = (double *)[[gData xData] bytes];
	yp = (double *)[[gData yData] bytes];
	tp[0] = [[self valueForKey:@"t0Value"] doubleValue];
	xp[0] = [[self valueForKey:@"x0Value"] doubleValue];
	yp[0] = [[self valueForKey:@"y0Value"] doubleValue];
	gData.intv = intvValue;

    if (stepValue >= 200000) {
		gData.steps = 199999;
		[self setValue:@199999 forKey:@"stepValue"];
	}
	else {
		gData.steps = stepValue;
	}
	
	gData.n_data = calc_data(stepValue, intvValue, tp, xp, yp);
	
	[gData findRegion];
	if (autoRange) {
		[self setValue:[NSNumber numberWithFloat:gData.region_x.origin.x] forKey:@"tMin"];
		[self setValue:[NSNumber numberWithFloat:(gData.region_x.origin.x +
												  gData.region_x.size.width)] forKey:@"tMax"];
		[self setValue:[NSNumber numberWithFloat:gData.region_x.origin.y] forKey:@"xMin"];
		[self setValue:[NSNumber numberWithFloat:(gData.region_x.origin.y +
												  gData.region_x.size.height)] forKey:@"xMax"];
		[self setValue:[NSNumber numberWithFloat:gData.region_y.origin.y] forKey:@"yMin"];
		[self setValue:[NSNumber numberWithFloat:(gData.region_y.origin.y +
												  gData.region_y.size.height)] forKey:@"yMax"];
	}
	[gView setNeedsDisplay:YES];
	[gView2 setNeedsDisplay:YES];
	
	[self setValue:[NSNumber numberWithBool:YES] forKey:@"dataActive"];
}

- (IBAction)clear:(id)sender {
	
//	NSLog(@"'erase:' called.\n");

	gData.n_data = 0;
	gData.region_x = gData.region_y = CGRectMake(0.0, 0.0, 1.0, 1.0);
	[gView setNeedsDisplay:YES];
	[gView2 setNeedsDisplay:YES];

	[self setValue:[NSNumber numberWithBool:NO] forKey:@"dataActive"];
}

- (IBAction)redraw:(id)sender {
	[gView setNeedsDisplay:YES];
	[gView2 setNeedsDisplay:YES];
}

@end

