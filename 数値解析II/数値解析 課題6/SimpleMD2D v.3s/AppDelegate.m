//
//  SimpleMD2DAppDelegate.m
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/06.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "AppDelegate.h"
#import "SimpleMD.h"
#import "PlotData.h"

@implementation AppDelegate

@synthesize window, mView, pView, currentData, plotMode;
@synthesize initButton, startButton, stopButton;
@synthesize nAtom, maxStep, stepCount;
@synthesize dt, cellSize, rc, startTemp, targetTemp, raiseRate;


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application

//    [self setValue:[NSNumber numberWithDouble:0.001] forKey:@"dt"];
    [self setValue:[NSNumber numberWithDouble:5.0  ] forKey:@"startTemp"];
    [self setValue:[NSNumber numberWithDouble:5.0  ] forKey:@"targetTemp"];
    [self setValue:[NSNumber numberWithDouble:0.001] forKey:@"raiseRate"];
    [self setValue:[NSNumber numberWithInt:100] forKey:@"nAtom"];
    [self setValue:[NSNumber numberWithInt:10000] forKey:@"maxStep"];
    [self setValue:[NSNumber numberWithInt:0] forKey:@"plotMode"];
    cellSize = 20.0;
    rc = 3.0;
    dt = 0.001;
    
    currentData = [[MDData alloc] initEnsembleOfNumber:nAtom];
    [mView setMdData:currentData];
    
}

- (IBAction) initialize:(id)sender
{
    Ensemble ce = currentData.currentEns, pe = currentData.prevEns;
    NSMutableArray  *parray = [pView pData];
    PlotData    *pd;
    
    [initButton setEnabled:NO];
    
	ce.number = pe.number = nAtom;
	
    init_particles(cellSize, rc, dt, startTemp, &ce, &pe);

    pd = [[PlotData alloc] init];
    [pd setPoint: CGPointMake(0, sqrt(ce.v2Mean))];
    [parray removeAllObjects];
    [parray addObject:pd];
    
    currentData.initted = YES;
    [mView setNeedsDisplay:YES];
    [initButton setEnabled:YES];
}

- (IBAction) startSim:(id)sender
{
    int     step, plot_intv = 40, disp_intv = 20;
    double  time;
    PlotData    *pd;
    NSMutableArray  *parray = [pView pData];

    if (currentData.initted == NO)
        return;
    
    [startButton setEnabled:NO];
    
    Ensemble    ce = currentData.currentEns,
                pe = currentData.prevEns;
    double      vms, vav = 0.0;
    
    [parray removeAllObjects];
    
    for (step = 1; step <= maxStep; step++) {
        
        force(&ce, cellSize, rc);
        vms = move(&ce, &pe, cellSize, dt);
        
        if (step % disp_intv == 0) {
            [mView display];
        }
        vav += vms;
        if (step % plot_intv == 0) {
            time = dt * (double)step;
            // printf("%lf\t%lf\t%lf\t%lf\n", time, ce.rx[0], ce.ry[0], vav / plot_intv);
            pd = [[PlotData alloc] init];
            [pd setPoint: CGPointMake(step, vav * 0.5 / plot_intv)];
            [parray addObject:pd];
            vav = 0.0;
        }
		if (step % (plot_intv * 5) == 0) {
            [pView display];			
		}
    }
    
    [startButton setEnabled:YES];
}

- (IBAction) stopSim:(id)sender
{
	
}

- (IBAction) graphModeChanged:(id)sender
{
	
}

@end
