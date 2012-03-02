/*
 *  UnifeyeSDKMobile
 *	Version 3.0
 *
 *  Copyright 2011 metaio GmbH. All rights reserved.
 *
 */
#ifndef ___AS_IUNIFYEMOBILEIPHONE_H_INCLUDED___
#define ___AS_IUNIFYEMOBILEIPHONE_H_INCLUDED___


#include "AS_IUnifeyeMobile.h"
#import <CoreGraphics/CoreGraphics.h>

@class AVCaptureVideoPreviewLayer;
@class IUnifeyeMobileGeometry;
@class NSString;
@class NSObject;

/** Set to of functions to handle Unifeye SDK Mobile callbacks
*/
@protocol UnifeyeMobileDelegate

@optional
/** This function will be triggered, when an animation has ended
 * \param geometry the geometry which has finished animating
 * \param animationName the name of the just finished animation
 * \return void
 */
- (void) onAnimationEnd: (metaio::IUnifeyeMobileGeometry*) geometry  andName:(NSString*) animationName;

/**
 * \brief Request a callback that delivers the next camera image.
 *
 * The image will have the  dimensions of the current capture resolution.
 * To request this callback, call requestCameraFrame()
 *
 * \param cameraFrame the latest camera image
 * 
 * \note you must copy the ImageStuct::buffer, if you need it for later. 
 */
- (void) onNewCameraFrame: ( metaio::ImageStruct*)  cameraFrame;


@end


namespace metaio
{

	/** 
	 * \brief Specialized interface for iPhone.
	 * 
	 */
	class IUnifeyeMobileIPhone : public virtual IUnifeyeMobile
	{
	public:
		
        virtual ~IUnifeyeMobileIPhone() {};
        
        /**
         * \brief Initialize the renderer
         *
         * \relates IUnifeyeMobileIPhone
         * \param width width of the renderer
         * \param height height of the renderer
         * \param renderSystem specify which renderer should be used
         */
        virtual void initializeRenderer( int width, int height,  const ERENDER_SYSTEM renderSystem=ERENDER_SYSTEM_OPENGL_ES_2_0) = 0;
        
        /** \brief Register the delegate object that will receive callbacks
         * \param delegate the object
         * \return void
         */
        virtual void registerDelegate( NSObject<UnifeyeMobileDelegate>* delegate ) = 0;
        
        /**
		 * \brief Get a camera preview layer from the active camera session
		 *
		 * Use this to get a pointer to a AVCaptureVideoPreviewLayer that 
		 * is created based on the current camera session. You can use this 
		 * to draw the camera image in the background and add a transparent
		 * EAGLView on top of this. To prevent Unifeye from drawing the 
		 * background in OpenGL you can activate the see-through mode.
		 *
		 * \code 	
		 *			[glView setBackgroundColor:[UIColor clearColor]];
		 *			unifeyeMobile->setSeeThrough(1);
		 *
		 *			AVCaptureVideoPreviewLayer* previewLayer = 
		 *					glView.unifeyeMobile->getCameraPreviewLayer();
		 *			previewLayer.frame = myUIView.bounds;
		 *			[myUIView.layer addSublayer:previewLayer];
		 * \endcode
		 *
		 * \sa Set Unifeye to see through mode using setSeeThrough ( 1 )
		 * \sa Start capturing using activateCamera ( index )
		 * \sa You can deactivate the capturing again with stopCamera()
		 *
		 * \note Only available on iOS >= 4.0. If you call this on 3.x nothing will happen.
		 * \note Not available on iPhone Simulator.
		 */
		virtual AVCaptureVideoPreviewLayer* getCameraPreviewLayer() = 0;    
        
        /**
         * @brief Specialized function for iPhone
         *
         * @param textureName name that should be assigned to the texture 
         *	(for reuse).
         * @param image image to set
         * @return pointer to geometry
         */
        virtual IUnifeyeMobileGeometry* loadImageBillboard( const std::string& textureName, CGImageRef image ) = 0;
    };

    /** Provides access to raw image data of a CGImage.
     * This is e.g. needed when setting an MD2 texture from memory.
     *
	 * \relates IUnifeyeMobileIPhone
	 *
     * \code
     * ImageStruct imageContent;
     * CGContextRef context = nil;
     * 
     * beginGetDataForCGImage(image, &imageContent, &context);
     * 
     *  // use data
     *  // ....
     * endGetData(&context);
     *
     * \endcode
     *
     * \param image the source image
     * \param[out] imageContent after the call this will point to a struct containing the image content
     * \param[out] context after the call this will point to the created CGContext. This has to be deleted again by calling endGetData
     * 
     * \sa endGetData to delegate the context again
     */
     void beginGetDataForCGImage(CGImage* image, ImageStruct* imageContent, CGContextRef* context);
    
    
    /** Frees the image context that was created with beginGetDataForCGImage
     * 
	 * \relates IUnifeyeMobileIPhone
     * \param context the context to free
     * 
     * \sa beginGetDataForCGImage to get data from a CGImage
     */
    void endGetData(CGContextRef* context);


	/**
	* \brief Create an ARMobileSystem instance
	*
	* \relates IUnifeyeMobileIPhone
	* \param signature The signature of the application identifier
	* \return a pointer to an ARMobileSystem instance
	*/
	IUnifeyeMobileIPhone* CreateUnifeyeMobileIPhone( const std::string& signature ); 




} //namespace metaio


#endif //___AS_IUNIFYEMOBILEIPHONE_H_INCLUDED___
