/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012年 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
#import "TiUIView.h"
#import <UnifeyeSDKMobile/AS_IUnifeyeMobileIPhone.h>
#import "EAGLView.h"

namespace metaio
{
    class IUnifeyeMobileIPhone;     // forward declaration
    class IUnifeyeMobileGeometry;   // forward declaration
}

@interface ComOtigaUnifeyeHelloView : TiUIView <UnifeyeMobileDelegate>{
metaio::IUnifeyeMobileIPhone*			unifeyeMobile;	
    
    EAGLContext *context;               // our OpenGL Context
    NSInteger animationFrameInterval;   // refresh interval
    CADisplayLink *displayLink;         // pointer to our displayLink
    
    EAGLView *glView;                   // our OpenGL View

}
@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;

@end
