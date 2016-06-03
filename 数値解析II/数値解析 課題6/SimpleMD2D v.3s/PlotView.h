//
//  PlotView.h
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GraphView.h"
#import "MDData.h"

@interface PlotView : GraphView {
    NSMutableArray    *pData;
}

@property (retain) NSMutableArray *pData;


@end


