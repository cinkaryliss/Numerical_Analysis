//
//  PlotView.m
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "PlotView.h"
#import "PlotData.h"
#import "AppDelegate.h"

#define     MAXDATA     10000

@implementation PlotView

@synthesize pData;


- (void) awakeFromNib {
    pData = [[NSMutableArray alloc] init];
    if ((td = (double *)malloc(sizeof(double) * MAXDATA)) == NULL) {
        pData = nil;
        return;
    }
    if ((xd = (double *)malloc(sizeof(double) * MAXDATA)) == NULL) {
        pData = nil;
        return;
    }
}

- (void) setUpGraphData
{
    AppDelegate *appDelegate = [NSApp delegate];
//  BOOL	autoRange = appDelegate.autoRange;
    double  xMin, xMax, xs;
    CGPoint    point;
    int     i;
    
    numData = [pData count];
    if (numData > 0) {
        if (numData >= MAXDATA)
            numData = MAXDATA;
        xMax = xMin = [[pData objectAtIndex:0] point].y;
        for (i = 0; i < numData; i++) {
            point = [[pData objectAtIndex:i] point];
            td[i] = point.x;
            xd[i] = point.y;

            if (xd[i] < xMin)
                xMin = xd[i];
            else if (xd[i] > xMax)
                xMax = xd[i];
        }
        if ((xs = xMax - xMin) == 0.0)
            xs = 1.0;
        dRegion = CGRectMake(0.0, 0.0, appDelegate.maxStep, xMax * 1.3);
    }
    else {
        dRegion = CGRectMake(0.0, 0, appDelegate.maxStep, 1.0);
    }
    tLabel = @"Step";
    xLabel = @"Temp.";
    lineColor = CGColorCreateGenericRGB(0.0, 0.0, 1.0, 1.0);
    
/*  
    if (!autoRange) {
        dRegion.origin.x = tMin;
        dRegion.origin.y = xMin;
        if (tMin != tMax)
            dRegion.size.width = fabs(tMax - tMin);
        if (xMin != xMax)
            dRegion.size.height = fabs(xMax - xMin);
    }
*/

}

- (void) prepareAttributes
{
    tickLabelAttributes = [[NSMutableDictionary alloc] init];
    charAttributes = [[NSMutableDictionary alloc] init];
    redcharAttributes = [[NSMutableDictionary alloc] init];
    
    [tickLabelAttributes setObject:[NSFont fontWithName:@"Helvetica" size:7]
                            forKey: NSFontAttributeName];
    [tickLabelAttributes setObject:[NSColor colorWithCalibratedRed:0.2 green:0.2 blue:0.2 alpha:1.0]
                            forKey: NSForegroundColorAttributeName];
    [tickLabelAttributes setObject:[NSColor whiteColor]
                            forKey: NSBackgroundColorAttributeName];
    
    [charAttributes setObject:[NSFont fontWithName:@"Helvetica" size:7]
                       forKey: NSFontAttributeName];
    [charAttributes setObject:[NSColor colorWithCalibratedRed:0.0 green:0.0 blue:0.0 alpha:1.0]
                       forKey: NSForegroundColorAttributeName];
    
    [redcharAttributes setObject:[NSFont fontWithName:@"Helvetica Bold" size:10]
                          forKey: NSFontAttributeName];
    [redcharAttributes setObject:[NSColor colorWithCalibratedRed:0.8 green:0.3 blue:0.3 alpha:1.0]
                          forKey: NSForegroundColorAttributeName];
}

@end
