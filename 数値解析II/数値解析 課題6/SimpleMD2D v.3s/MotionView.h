//
//  MotionView.h
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MDData.h"


@interface MotionView : NSView {
    MDData *mdData;
    NSMutableDictionary *tickLabelAttributes;
    NSMutableDictionary *charAttributes;
    NSMutableDictionary *redcharAttributes;
}

@property (retain) MDData *mdData;

- (void) prepareAttributes;
- (void) setUpGraphData;

@end
