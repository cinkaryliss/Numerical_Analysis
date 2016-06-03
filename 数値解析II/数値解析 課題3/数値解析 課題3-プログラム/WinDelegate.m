//
//  WinDelegate.m
//  DiffEq2
//
//  Created by kuma on 2015/11/05.
//  Copyright © 2015年 Takao Inokuma. All rights reserved.
//

#import "WinDelegate.h"

@implementation WinDelegate

- (BOOL)windowShouldClose:(id)sender {
    [NSApp terminate:self];
    return YES;
}

@end
