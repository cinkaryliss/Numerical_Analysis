//
//  GraphView.m
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//


#import "GraphView.h"


@implementation GraphView

@synthesize td, xd, numData, dRegion, tLabel, xLabel, lineColor;

- (id)initWithFrame:(NSRect)frame
{
	self = [super initWithFrame:frame];
	if (self) {
		// Initialization code here.
        [self setUpGraphData];
		[self prepareAttributes];
	}
	return self;
}

- (void)drawRect:(NSRect)dRect
{
	CGContextRef theContext = [[NSGraphicsContext currentContext] graphicsPort];
	CGRect	viewRect = [self bounds];
	CGPoint	tickPos1, tickPos2, stringOrigin, cPoint;
	CGSize	stringSize;
	CGAffineTransform   xform;
	NSString	*labelString;
	
	double	a, tb, xb, c;
	float	t_st, t_ed, t_tk, x_st, x_ed, x_tk,
            ttl = 2.0, xtl = 2.0, mgn_l = 15.0, mgn_b = 15.0,
            t_scale, x_scale, t_offset, x_offset;
	int		i, j;
	
    [self setUpGraphData];

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
	
	CGContextSetRGBFillColor(theContext, 1, 1, 1, 1);
	CGContextSetLineJoin(theContext, kCGLineJoinRound);
	CGContextSetLineCap(theContext, kCGLineCapRound);
	CGContextFillRect(theContext, viewRect);
	
	CGContextSetRGBStrokeColor(theContext, 0.5, 0.5, 0.5, 1);
	CGContextSetLineWidth(theContext, 1.0);
	CGContextMoveToPoint(theContext, viewRect.origin.x, mgn_b);
	CGContextAddLineToPoint(theContext, viewRect.origin.x + viewRect.size.width, mgn_b);
	CGContextMoveToPoint(theContext, mgn_l, viewRect.origin.y);
	CGContextAddLineToPoint(theContext, mgn_l, viewRect.origin.y + viewRect.size.height);
	CGContextStrokePath(theContext);
	
	if (numData > 0) {
		
		t_scale = (viewRect.size.width-mgn_l)/dRegion.size.width;
		x_scale = (viewRect.size.height-mgn_b)*0.9/dRegion.size.height;
		t_offset = -dRegion.origin.x * t_scale + mgn_l;
		x_offset = (-dRegion.origin.y + 0.05*dRegion.size.height) * x_scale + mgn_b;
		xform = CGAffineTransformMake(t_scale, 0.0, 0.0, x_scale, t_offset, x_offset);

		CGContextSetRGBStrokeColor(theContext, 0.5, 0.5, 0.5, 1);
		for (a = t_st; a <= t_ed + t_tk; a += t_tk) {
			tickPos1 = CGPointApplyAffineTransform(CGPointMake(a, dRegion.origin.y-0.05*dRegion.size.height), xform);
			tickPos2 = CGPointApplyAffineTransform(CGPointMake(a, dRegion.origin.y-0.05*dRegion.size.height + ttl/x_scale), xform);
			CGContextMoveToPoint(theContext, tickPos1.x, tickPos1.y);
			CGContextAddLineToPoint(theContext, tickPos2.x, tickPos2.y);
			CGContextStrokePath(theContext);
			labelString = [NSString stringWithFormat:@"%.2G", a];
			stringSize = [labelString sizeWithAttributes:tickLabelAttributes];
			stringOrigin = CGPointMake(tickPos1.x - (stringSize.width / 2.0), tickPos1.y - (stringSize.height + 1.5));
			[labelString drawAtPoint:stringOrigin withAttributes:tickLabelAttributes];
			if (tb < 0.30) {
				for (j = 1; j <= 9; j++) {
					tickPos1 = CGPointApplyAffineTransform(CGPointMake(a + j * t_tk/10.0, dRegion.origin.y-0.05*dRegion.size.height), xform);
					tickPos2 = CGPointApplyAffineTransform(CGPointMake(a + j * t_tk/10.0, dRegion.origin.y-0.05*dRegion.size.height + 0.5*ttl/x_scale), xform);
					CGContextMoveToPoint(theContext, tickPos1.x, tickPos1.y);
					CGContextAddLineToPoint(theContext, tickPos2.x, tickPos2.y);
					CGContextStrokePath(theContext);
				}
			}
		}

		for (a = x_st; a <= x_ed + x_tk; a += x_tk) {
			tickPos1 = CGPointApplyAffineTransform(CGPointMake(dRegion.origin.x, a), xform);
			tickPos2 = CGPointApplyAffineTransform(CGPointMake(dRegion.origin.x + xtl/t_scale, a), xform);
			CGContextMoveToPoint(theContext, tickPos1.x, tickPos1.y);
			CGContextAddLineToPoint(theContext, tickPos2.x, tickPos2.y);
			CGContextStrokePath(theContext);
			labelString = [NSString stringWithFormat:@"%.2G", a];
			stringSize = [labelString sizeWithAttributes:tickLabelAttributes];
			stringOrigin = CGPointMake(tickPos1.x - (stringSize.width + 2.0), tickPos1.y - (stringSize.height / 2.0));
			[labelString drawAtPoint:stringOrigin withAttributes:tickLabelAttributes];
			if (xb < 0.30) {
				for (j = 1; j <= 4; j++) {
					tickPos1 = CGPointApplyAffineTransform(CGPointMake(dRegion.origin.x, a + j * x_tk/5.0), xform);
					tickPos2 = CGPointApplyAffineTransform(CGPointMake(dRegion.origin.x + 0.5*xtl/t_scale, a + j * x_tk/5.0), xform);
					CGContextMoveToPoint(theContext, tickPos1.x, tickPos1.y);
					CGContextAddLineToPoint(theContext, tickPos2.x, tickPos2.y);
					CGContextStrokePath(theContext);
				}
			}
		}
		
		CGContextSetStrokeColorWithColor(theContext, lineColor);
		CGContextSetLineWidth(theContext, 1.5);
		cPoint = CGPointApplyAffineTransform(CGPointMake(td[0], xd[0]), xform);
		CGContextMoveToPoint(theContext, cPoint.x, cPoint.y);
		for (i = 1; i < numData; i++) {
			cPoint = CGPointApplyAffineTransform(CGPointMake(td[i], xd[i]), xform);
			CGContextAddLineToPoint(theContext, cPoint.x, cPoint.y);
		}
		CGContextStrokePath(theContext);
	}
	
	stringSize = [tLabel sizeWithAttributes:redcharAttributes];
	stringOrigin.x = viewRect.origin.x + viewRect.size.width - stringSize.width - 5.0;
	stringOrigin.y = viewRect.origin.y + 2.0;
	[tLabel drawAtPoint:stringOrigin withAttributes:redcharAttributes];
	
	stringSize = [xLabel sizeWithAttributes:redcharAttributes];
	stringOrigin.x = viewRect.origin.x + 3.0;
	stringOrigin.y = viewRect.origin.y + viewRect.size.height - stringSize.height - 3.0;
	[xLabel drawAtPoint:stringOrigin withAttributes:redcharAttributes];

}

- (void) setUpGraphData {
    // Set up the data for draw.
    // The following is default values, which should be overridden.
/*
    numData = 0;
    td = NULL;
    xd = NULL;
    dRegion = CGRectMake(0.0, 0.0, 1.0, 1.0);
    tLabel = @"x";
    xLabel = @"y";
    lineColor = CGColorCreateGenericRGB(0.0, 0.0, 0.0, 1.0);
*/    
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
