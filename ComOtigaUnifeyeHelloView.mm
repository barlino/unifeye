/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012年 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "ComOtigaUnifeyeHelloView.h"
#import <QuartzCore/QuartzCore.h>
#import <UnifeyeSDKMobile/AS_IUnifeyeMobileGeometry.h>
#import "EAGLView.h"
#import "TiUtils.h"

// Define your License here
// for more information, please visit http://docs.metaio.com
#define UNIFEYE_LICENSE "LLVMA/d0+x862jdnA79Wz32Gv7l3Vx4011SQa6GY6S8="
#if !defined (UNIFEYE_LICENSE)
#error Please provide the license string for your application
#endif

@implementation ComOtigaUnifeyeHelloView

@synthesize glView;
@synthesize context, displayLink;

- (id)init
{
    NSLog(@"[Proxy] init");
	if ((self = [super init]))
	{
        if( !context )
        {
            EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
            
            if (!aContext) {
                NSLog(@"Failed to create ES context");
            } else if (![EAGLContext setCurrentContext:aContext]) {
                NSLog(@"Failed to set ES context current");
            }
            self.context = aContext;
            [aContext release];
        }
        
        
        // set the openGL context
        [glView setContext:context];
        [glView setFramebuffer];

        self.displayLink = nil;
        
        // limit OpenGL framerate to 30FPS, as the camera has a maximum of 30FPS anyway
        animationFrameInterval = 2;
        
        // create unifeye instance
        unifeyeMobile = metaio::CreateUnifeyeMobileIPhone(UNIFEYE_LICENSE);
        if( !unifeyeMobile )
        {
            NSLog(@"Unifeye instance could not be created. Please verify the signature string");
            return;
        }
        
        // Create our Unifeye instance
        float scaleFactor = [UIScreen mainScreen].scale;	
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        {
            // don't limit framerate on iPad
            unifeyeMobile->initializeRenderer(768, 1024);
            NSLog(@"iPad mode");
        }
        else
        {
            // Note: the dimensions of the EAGLView should match the dimensions below (360x480)
            // the camera image has an aspect ratio of 360/480, the screen has an aspect ratio of 320/480
            unifeyeMobile->initializeRenderer(360 * scaleFactor, 480 * scaleFactor);
        }
        
        // register our callback method for animations
        //unifeyeMobile->registerDelegate(self);

        
	}
	return self;
}
-(BOOL)proxyHasTapListener
{
    // The TiUIView only sets multipleTouchEnabled to YES if we have a tap listener.
    // So... let's make it think that we do! (Note that we don't actually need one.)
	return YES;
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }

    if (unifeyeMobile) {
        delete unifeyeMobile;
        unifeyeMobile = NULL;
    }

    [context release];
    [glView release];
	[super dealloc];
}

-(id)open:(id)args{
    NSLog(@"[View]open Camera");     
    if( unifeyeMobile )
    {
        unifeyeMobile->activateCamera(0, 480, 360);
    }
 
    // if we start up in landscape mode after having portrait before, we want to make sure that the renderer is rotated correctly
//    UIInterfaceOrientation interfaceOrientation = self.interfaceOrientation;    
//    [self willAnimateRotationToInterfaceOrientation:interfaceOrientation duration:0];
//    
    // load our tracking configuration
//    NSString* trackingDataFile = [[NSBundle mainBundle] pathForResource:@"TrackingData_MarkerlessFast" ofType:@"xml" inDirectory:@"Assets"];	
//	if(trackingDataFile)
//	{
//        NSLog(@"Load Tracking Data");
//        bool success = unifeyeMobile->setTrackingData([trackingDataFile UTF8String]);
//		if( !success)
//			NSLog(@"No success loading the tracking configuration");
//	}
//    
    
    // load content
    NSString* metaioManModel = [[NSBundle mainBundle] pathForResource:@"metaioman" ofType:@"md2" inDirectory:@"Assets"];
    
	if(metaioManModel)
	{
        NSLog(@"Load 3D Modal");
		// if this call was successful, theLoadedModel will contain a pointer to the 3D model
        metaio::IUnifeyeMobileGeometry* theLoadedModel =  unifeyeMobile->loadGeometry([metaioManModel UTF8String]);			
        if( theLoadedModel )
        {
            // scale it a bit down
            theLoadedModel->setMoveScale(metaio::Vector3d(0.8,0.8,0.8));
        }
        else
        {
            NSLog(@"error, could not load %@", metaioManModel);            
        }
    }

    

    return self;
}

@end
