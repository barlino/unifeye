#ifndef __AS_UNIFEYE_CALLBACK__
#define __AS_UNIFEYE_CALLBACK__

#include <string>


namespace metaio
{
	// forward declarations
	class IUnifeyeMobileGeometry;

	/**
	* The Unifeye SDK Mobile Callback interface. 
	* 
	* These functions should be implemented for handling events triggered by the mobile SDK. 
	*/
	class IUnifeyeMobileCallback 
	{
    public:

        /** Virtual destructor */
        virtual ~IUnifeyeMobileCallback() {};
    
        
        /**
         * \brief This function will be triggered, when an animation has ended
         * \param geometry the geometry which has finished animating
         * \param animationName the name of the just finished animation
         * \return void
         */
        virtual void onAnimationEnd( metaio::IUnifeyeMobileGeometry* geometry, std::string animationName) = 0;
        
        /**
		* \brief Callback that delivers the next camera image.
		*
		* The image will have the dimensions of the current capture resolution.
        * To request this callback, call requestCameraFrame()
		*
        * \param cameraFrame the latest camera image
        * 
		* \note you must copy the ImageStuct::buffer, if you need it for later. 
        */
        virtual void onNewCameraFrame( metaio::ImageStruct*  cameraFrame) = 0;
	};


}


#endif