//
//  DiffEqAppDelegate.h
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GraphData.h"
#import "GraphView.h"
#import "GraphView2.h"

@interface DiffEqAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	GraphView *gView;
	GraphView2 *gView2;
	GraphData *gData;
	double  t0Value, x0Value, y0Value, intvValue;
	int     stepValue;
    double  tMax, tMin, xMax, xMin, yMax, yMin;
    BOOL    autoRange, dataActive;
}


@property (assign) IBOutlet NSWindow *window;
@property (retain) IBOutlet GraphView *gView;
@property (retain) IBOutlet GraphView2 *gView2;
@property (retain) GraphData *gData;
@property (assign) double  t0Value, x0Value, y0Value, intvValue;
@property (assign) int     stepValue;
@property (assign) double  tMax, tMin, xMax, xMin, yMax, yMin;
@property (assign) BOOL    autoRange, dataActive;


- (IBAction)calc:(id)sender;
- (IBAction)clear:(id)sender;
- (IBAction)redraw:(id)sender;

@end
