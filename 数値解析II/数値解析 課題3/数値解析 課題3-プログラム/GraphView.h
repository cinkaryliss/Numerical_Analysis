//
//  GraphView.h
//  DiffEq
//
//  Created by tak on 15/11/02.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GraphData.h"

@interface GraphView : NSView {
	GraphData	*gData;
    NSMutableDictionary *tickLabelAttributes;
    NSMutableDictionary *charAttributes;
    NSMutableDictionary *redcharAttributes;
}

@property (retain) GraphData *gData;

- (void) prepareAttributes;

@end
