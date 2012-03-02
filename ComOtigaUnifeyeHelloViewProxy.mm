/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012年 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "ComOtigaUnifeyeHelloViewProxy.h"
#import "TiUtils.h"

@implementation ComOtigaUnifeyeHelloViewProxy
-(void)open:(id)args{
    NSLog(@"[Proxy] open");
    [[self view] performSelector:@selector(open:)];
}
@end
