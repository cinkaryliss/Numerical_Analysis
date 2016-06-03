//
//  AppDelegate.h
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/06.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MotionView.h"
#import "PlotView.h"
#import "MDData.h"
#include "SimpleMD.h"

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	MotionView *mView;
	PlotView *pView;
    NSButton *initButton, *startButton, *stopButton;
	MDData *currentData;
    int nAtomValue, maxStep, stepCount, plotMode;

    double  dt, cellSize, rc;
    double  startTemp, targetTemp;
    double  raiseRate;
}

- (IBAction) initialize:(id)sender;
- (IBAction) startSim:(id)sender;
- (IBAction) stopSim:(id)sender;
- (IBAction) graphModeChanged:(id)sender;

@property (assign) IBOutlet NSWindow *window;
@property (retain) IBOutlet MotionView *mView;
@property (retain) IBOutlet PlotView *pView;
@property (assign) IBOutlet NSButton *initButton, *startButton, *stopButton;
@property (retain) MDData *currentData;
@property (assign) int nAtom, maxStep, stepCount, plotMode;
@property (assign) double dt, cellSize, rc, startTemp, targetTemp, raiseRate;


@end
