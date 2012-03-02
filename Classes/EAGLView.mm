//
//  EAGLView.m
//  metaio Mobile SDK
//
//  Copyright metaio, GmbH 2011. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"

@interface EAGLView (PrivateMethods)
- (void)createFramebuffer;
- (void)deleteFramebuffer;
@end


@implementation EAGLView
@synthesize context;


// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)initWithCoder:(NSCoder*)coder
{
    self = [super initWithCoder:coder];
	if (self) {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
        
        self.contentScaleFactor = [UIScreen mainScreen].scale;
    }
    
    return self;
}

- (void)dealloc
{
    [self deleteFramebuffer];    
    [context release];
    
    [super dealloc];
}

- (void)setContext:(EAGLContext *)newContext
{
    if (context != newContext) {
        [self deleteFramebuffer];
        
        [context release];
        context = [newContext retain];
        
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)createFramebuffer
{
    if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext:context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        
        // create depth buffer
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT24_OES, framebufferWidth, framebufferHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
        
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
}

- (void)deleteFramebuffer
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer) {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
        
        if(depthRenderbuffer)
        {
            glDeleteRenderbuffersOES(1, &depthRenderbuffer);
            depthRenderbuffer = 0;
        }
        
    }
}

- (void)setFramebuffer
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer)
            [self createFramebuffer];
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (BOOL)presentFramebuffer
{
    BOOL success = FALSE;
    
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

- (void)layoutSubviews
{
    // The framebuffer will be re-created at the beginning of the next setFramebuffer method call.
    [self deleteFramebuffer];
}



- (UIImage*) getScreenshotImage
{
    // read image data from openGL
	unsigned char* imgData = new unsigned char[framebufferWidth * framebufferHeight * 4];
	glReadPixels(0, 0, framebufferWidth, framebufferHeight, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
	
	CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, imgData, framebufferWidth * framebufferHeight * 4, NULL);
	CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
	
	CGColorRenderingIntent intent = kCGRenderingIntentDefault;
	CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
	
	CGImageRef imgRef = CGImageCreate(framebufferWidth, framebufferHeight, 8, 32, framebufferWidth*4, space, bitmapInfo, provider, NULL, NO, intent);
	
	// Draw the image using the current graphics context
	UIGraphicsBeginImageContext(CGSizeMake(framebufferWidth, framebufferHeight));
	
	CGContextRef currContext = UIGraphicsGetCurrentContext();
	CGContextDrawImage(currContext, CGRectMake(0, 0, framebufferWidth, framebufferHeight), imgRef);
	
	// retrieve the screenshot from the current context
	UIImage* screenshot = UIGraphicsGetImageFromCurrentImageContext();	
	UIGraphicsEndImageContext();
	
	// release all used objects
	CGDataProviderRelease(provider);
	CGColorSpaceRelease(space);
	CGImageRelease(imgRef);
	delete[] imgData;
	
	return screenshot;
}


@end
