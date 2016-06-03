//
//  MDData.h
//  SimpleMD2D
//
//  Created by Takao Inokuma on 15/09/07.
//  Copyright 2015 Takao Inokuma. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "SimpleMD.h"

@interface MDData : NSObject {
    Ensemble currentEns, prevEns;
    BOOL    initted;
}

@property (assign) Ensemble currentEns, prevEns;
@property (assign) BOOL initted;

- (id)initEnsembleOfNumber: (int)num;

@end
