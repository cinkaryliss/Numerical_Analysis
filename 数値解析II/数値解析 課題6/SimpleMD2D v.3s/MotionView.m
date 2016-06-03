//
//  MotionView.m
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "MotionView.h"

@implementation MotionView

@synthesize mdData;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setUpGraphData];
        [self prepareAttributes];
    }
    return self;
}

- (void)drawRect:(NSRect)dRect
{
    CGContextRef theContext = [[NSGraphicsContext currentContext] graphicsPort];
    CGRect	viewRect = [self bounds];
    CGRect	cellRect;
    CGPoint cpoint;
    CGAffineTransform   xform;
    Ensemble    c_ens = [mdData currentEns];
    float   radius;
    int     i;
    
    int     numData = [[self mdData] currentEns].number;
    float   x_scale, y_scale, x_offset, y_offset;
    
    CGContextSetRGBFillColor(theContext, 1, 1, 1, 1);
    CGContextSetLineJoin(theContext, kCGLineJoinRound);
    CGContextSetLineCap(theContext, kCGLineCapRound);
    CGContextFillRect(theContext, viewRect);
    cellRect = CGRectMake(-10.0, -10.0, 20.0, 20.0);
    
    if ([mdData initted] == YES && numData > 0) {
        
        x_scale = viewRect.size.width / cellRect.size.width;
        y_scale = viewRect.size.height / cellRect.size.height;
        x_offset = -cellRect.origin.x * x_scale;
        y_offset = -cellRect.origin.y * y_scale;
        xform = CGAffineTransformMake(x_scale, 0.0, 0.0, y_scale, x_offset, y_offset);
        radius = 0.5 * x_scale;
        
        CGContextSetRGBFillColor(theContext, 0, 0.5, 0, 1);
        for (i = 0; i < numData; i++) {
            cpoint = CGPointApplyAffineTransform(CGPointMake(c_ens.rx[i], c_ens.ry[i]), xform);
            CGContextFillEllipseInRect(theContext, CGRectMake(cpoint.x - radius, cpoint.y - radius, radius * 2, radius * 2));
        }

    }
}

- (void)prepareAttributes
{
    tickLabelAttributes = [[NSMutableDictionary alloc] init];
    charAttributes = [[NSMutableDictionary alloc] init];
    redcharAttributes = [[NSMutableDictionary alloc] init];
    
    [tickLabelAttributes setObject:[NSFont fontWithName:@"Helvetica" size:8]
                            forKey: NSFontAttributeName];
    [tickLabelAttributes setObject:[NSColor colorWithCalibratedRed:0.2 green:0.2 blue:0.2 alpha:1.0]
                            forKey: NSForegroundColorAttributeName];
    [tickLabelAttributes setObject:[NSColor whiteColor]
                            forKey: NSBackgroundColorAttributeName];
    
    [charAttributes setObject:[NSFont fontWithName:@"Helvetica" size:8]
                       forKey: NSFontAttributeName];
    [charAttributes setObject:[NSColor colorWithCalibratedRed:0.0 green:0.0 blue:0.0 alpha:1.0]
                       forKey: NSForegroundColorAttributeName];
    
    [redcharAttributes setObject:[NSFont fontWithName:@"Helvetica Bold" size:10]
                          forKey: NSFontAttributeName];
    [redcharAttributes setObject:[NSColor colorWithCalibratedRed:0.8 green:0.3 blue:0.3 alpha:1.0]
                          forKey: NSForegroundColorAttributeName];

}

- (void)setUpGraphData
{

}

@end
