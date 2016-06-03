//
//  GraphView2.h
//  DiffEq2
//
//  Created by tak on 15/11/04.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GraphData.h"

@interface GraphView2 : NSView {
	GraphData	*gData;
	NSMutableDictionary *tickLabelAttributes;
	NSMutableDictionary *charAttributes;
	NSMutableDictionary *redcharAttributes;
}

@property (retain) GraphData *gData;

- (void) prepareAttributes;

@end

