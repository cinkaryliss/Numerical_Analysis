//
//  GraphView.m
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import "GraphView.h"
#import "DiffEqAppDelegate.h"


@implementation GraphView

@synthesize gData;

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        [self prepareAttributes];
    }
    return self;
}

- (void)drawRect:(NSRect)dRect
{
    CGRect	viewRect = [self bounds];
	CGRect	dRegion = gData.region_x;
	CGPoint	tickPos1, tickPos2, stringOrigin;
	CGSize	stringSize;
	NSBezierPath	*lPath1;
	NSAffineTransform	*xform = [NSAffineTransform transform];
	NSString	*labelString;
    DiffEqAppDelegate *appDelegate = [NSApp delegate];
    
    double	*td, *xd, a, tb, xb, c;
    float	t_st, t_ed, t_tk, x_st, x_ed, x_tk,
    ttl = 4.0, xtl = 4.0, mgn_l = 45.0, mgn_b =25,
    t_scale, x_scale, t_offset, x_offset;
    int		i, j;
    BOOL    autoRange = appDelegate.autoRange;
    double  xMin = appDelegate.xMin,
            xMax = appDelegate.xMax,
            tMin = appDelegate.tMin,
            tMax = appDelegate.tMax;
    
    if (!autoRange) {
        dRegion.origin.x = tMin;
        dRegion.origin.y = xMin;
        if (tMin != tMax)
            dRegion.size.width = fabs(tMax - tMin);
        if (xMin != xMax)
            dRegion.size.height = fabs(xMax - xMin);
    }
    
    c = log10(dRegion.size.width);
    a = floor(c);
    tb = c - a;
    t_tk = (float)pow(10, a);
    t_st = (floor(dRegion.origin.x/t_tk) * t_tk);
    t_ed = dRegion.origin.x + dRegion.size.width;
    c = log10(dRegion.size.height);
    a = floor(c);
    xb = c - a;
    x_tk = (float)pow(10, a);
    x_st = (floor(dRegion.origin.y/x_tk) * x_tk);
    x_ed = dRegion.origin.y + dRegion.size.height;
	
	[[NSColor whiteColor] set];
	[NSBezierPath setDefaultLineCapStyle:NSRoundLineCapStyle];
    [NSBezierPath setDefaultLineJoinStyle:NSRoundLineJoinStyle];
    [NSBezierPath fillRect:viewRect];
	[[NSColor grayColor] set];
	[NSBezierPath strokeLineFromPoint:CGPointMake(viewRect.origin.x, mgn_b) 
							  toPoint:CGPointMake(viewRect.origin.x + viewRect.size.width, mgn_b)];
	[NSBezierPath strokeLineFromPoint:CGPointMake(mgn_l, viewRect.origin.y)
							  toPoint:CGPointMake(mgn_l, viewRect.origin.y + viewRect.size.height)];
	
	if (gData.n_data > 0) {
		
		t_scale = (viewRect.size.width-mgn_l)/dRegion.size.width;
		x_scale = (viewRect.size.height-mgn_b)*0.9/dRegion.size.height;
		t_offset = -dRegion.origin.x + mgn_l/t_scale;
		x_offset = -dRegion.origin.y + 0.05*dRegion.size.height + mgn_b/x_scale;
		[xform scaleXBy:t_scale	yBy:x_scale];
		[xform translateXBy:t_offset yBy:x_offset];

        for (a = t_st; a <= t_ed + t_tk; a += t_tk) {
            tickPos1 = CGPointMake(a, dRegion.origin.y-0.05*dRegion.size.height);
            tickPos2 = CGPointMake(a, dRegion.origin.y-0.05*dRegion.size.height + ttl/x_scale);
            [[NSColor grayColor] set];
            [NSBezierPath strokeLineFromPoint:[xform transformPoint:tickPos1]
                                      toPoint:[xform transformPoint:tickPos2]];
            labelString = [NSString stringWithFormat:@"%.2G", a];
            stringSize = [labelString sizeWithAttributes:tickLabelAttributes];
            stringOrigin.x = tickPos1.x - (stringSize.width / 2.0)/t_scale;
            stringOrigin.y = tickPos1.y - (stringSize.height + 1.5)/x_scale;
            [labelString drawAtPoint:[xform transformPoint:stringOrigin] withAttributes:tickLabelAttributes];
            if (tb < 0.30) {
                for (j = 1; j <= 9; j++) {
                    tickPos1 = CGPointMake(a + j * t_tk/10.0, dRegion.origin.y-0.05*dRegion.size.height);
                    tickPos2 = CGPointMake(a + j * t_tk/10.0, dRegion.origin.y-0.05*dRegion.size.height + 0.5*ttl/x_scale);
                    [NSBezierPath strokeLineFromPoint:[xform transformPoint:tickPos1]
                                              toPoint:[xform transformPoint:tickPos2]];
                }
            }
        }
        for (a = x_st; a <= x_ed + x_tk; a += x_tk) {
            tickPos1 = CGPointMake(dRegion.origin.x, a);
            tickPos2 = CGPointMake(dRegion.origin.x + xtl/t_scale, a);
            [[NSColor grayColor] set];
            [NSBezierPath strokeLineFromPoint:[xform transformPoint:tickPos1]
                                      toPoint:[xform transformPoint:tickPos2]];
            labelString = [NSString stringWithFormat:@"%.2G", a];
            stringSize = [labelString sizeWithAttributes:tickLabelAttributes];
            stringOrigin.x = tickPos1.x - (stringSize.width + 2.0)/t_scale;
            stringOrigin.y = tickPos1.y - (stringSize.height / 2.0)/x_scale;
            [labelString drawAtPoint:[xform transformPoint:stringOrigin] withAttributes:tickLabelAttributes];
            if (xb < 0.30) {
                for (j = 1; j <= 4; j++) {
                    tickPos1 = CGPointMake(dRegion.origin.x, a + j * x_tk/5.0);
                    tickPos2 = CGPointMake(dRegion.origin.x + 0.5*xtl/t_scale, a + j * x_tk/5.0);
                    [NSBezierPath strokeLineFromPoint:[xform transformPoint:tickPos1]
                                              toPoint:[xform transformPoint:tickPos2]];
                }
            }
        }
        
		td = (double *)[[gData tData] bytes];
		xd = (double *)[[gData xData] bytes];
		
		[[NSColor blueColor] set];
		lPath1 = [NSBezierPath bezierPath];
		[lPath1 moveToPoint:[xform transformPoint: CGPointMake(td[0], xd[0])]];
		for (i = 1; i < gData.n_data; i++)
			[lPath1 lineToPoint:[xform transformPoint: CGPointMake(td[i], xd[i])]];
		[lPath1 setLineWidth:1.5];
        [lPath1 stroke];
		
	}
	
	labelString = @"t";
    stringSize = [labelString sizeWithAttributes:redcharAttributes];
    stringOrigin.x = viewRect.origin.x + viewRect.size.width - stringSize.width - 5.0;
    stringOrigin.y = viewRect.origin.y + 2.0;
    [labelString drawAtPoint:stringOrigin withAttributes:redcharAttributes];
	
	labelString = @"x";
    stringSize = [labelString sizeWithAttributes:redcharAttributes];
    stringOrigin.x = viewRect.origin.x + 3.0;
    stringOrigin.y = viewRect.origin.y + viewRect.size.height - stringSize.height - 3.0;
    [labelString drawAtPoint:stringOrigin withAttributes:redcharAttributes];

}

- (void) prepareAttributes
{
    tickLabelAttributes = [[NSMutableDictionary alloc] init];
    charAttributes = [[NSMutableDictionary alloc] init];
    redcharAttributes = [[NSMutableDictionary alloc] init];
    
    [tickLabelAttributes setObject:[NSFont fontWithName:@"Helvetica" size:10]
							forKey: NSFontAttributeName];
    [tickLabelAttributes setObject:[NSColor colorWithCalibratedRed:0.2 green:0.2 blue:0.2 alpha:1.0]
							forKey: NSForegroundColorAttributeName];
    [tickLabelAttributes setObject:[NSColor whiteColor]
							forKey: NSBackgroundColorAttributeName];
	
    [charAttributes setObject:[NSFont fontWithName:@"Helvetica" size:10]
					   forKey: NSFontAttributeName];
    [charAttributes setObject:[NSColor colorWithCalibratedRed:0.0 green:0.0 blue:0.0 alpha:1.0]
					   forKey: NSForegroundColorAttributeName];

    [redcharAttributes setObject:[NSFont fontWithName:@"Helvetica Bold" size:14]
					   forKey: NSFontAttributeName];
    [redcharAttributes setObject:[NSColor colorWithCalibratedRed:0.8 green:0.3 blue:0.3 alpha:1.0]
					   forKey: NSForegroundColorAttributeName];
}

@end
