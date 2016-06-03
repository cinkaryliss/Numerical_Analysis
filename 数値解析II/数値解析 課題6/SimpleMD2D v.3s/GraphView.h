//
//  GraphView.h
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GraphView : NSView {

    int         numData;
    double      *td, *xd;
    CGRect      dRegion;
    NSString     *tLabel, *xLabel;
    CGColorRef   lineColor;
    NSMutableDictionary *tickLabelAttributes;
    NSMutableDictionary *charAttributes;
    NSMutableDictionary *redcharAttributes;

}

@property (assign) int      numData;
@property (assign) double  *td, *xd;
@property (assign) CGRect  dRegion;
@property (retain) NSString *tLabel, *xLabel;
@property (assign) CGColorRef lineColor;

- (void) prepareAttributes;
- (void) setUpGraphData;

@end
