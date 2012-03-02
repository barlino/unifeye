/*
 *  metaio Mobile SDK
 *	Version 3.0
 *
 *  Copyright 2011 metaio GmbH. All rights reserved.
 *
 */
#ifndef __AS_IUNIFEYEMOBILE_H_INCLUDED__
#define __AS_IUNIFEYEMOBILE_H_INCLUDED__


#include <string>
#include <vector>
#include <limits>

#include "AS_MobileStructs.h"
#include "AS_IUnifeyeMobileGeometry.h"
#include "AS_IUnifeyeBillboardGroup.h"
#include "AS_IUnifeyeMobileCallback.h"



namespace metaio
{


	/** 
		Enumerations for different rendering implementations
	*/
	enum ERENDER_SYSTEM
	{
		/// NullRender implementation, if you want to use your own renderer
		ERENDER_SYSTEM_NULL,
		/// OpenGL based rendering (PC only)
		ERENDER_SYSTEM_OPENGL,
		/// OpenGL ES 1.1 based rendering - not supported in SDK release 3.0
		ERENDER_SYSTEM_OPENGL_ES,
		/// OpenGL ES 2.0 based rendering
		ERENDER_SYSTEM_OPENGL_ES_2_0 
	};


	/** \brief The common interface for all platforms.
	*
	* \date 08-12-2011
	*
	* \par License
	* This code is the property of the metaio GmbH (www.metaio.com). 
	* It is absolutely not free to be used, copied or
	* be modified without prior written permission from metaio GmbH.
	* The code is provided "as is" with no expressed or implied warranty. 
	* The author accepts no liability if it causes
	* any damage to your computer, or any harm at all.
	*/

	class IUnifeyeMobile 
	{
	public:
		

		/**
		* \brief Destructor of the mobile SDK
		* \return 
		*/
		virtual ~IUnifeyeMobile(){};


		/**
		* \brief Load a tracking configuration from an XML file.
		*
		*	This function configures the tracking system and the coordinate systems based on an XML file.
		*
		* \param trackingDataFile Fully qualified path of the XML file that should be loaded.
		* \return True if successful, false otherwise.
		*/
		virtual bool setTrackingData( const std::string& trackingDataFile) = 0;
        
		/**
		* \brief Load a camera calibration (intrinsic parameters) from an XML file.
		*
		*	The provided XML file should be structured as follows:
		*
		*	&lt;?xml version="1.0"?&gt;<br/>
		*	&lt;Camera&gt;&lt;Name&gt;iPhoneCamera&lt;/Name&gt;<br/>
		*		&lt;CalibrationResolution&gt;&lt;X&gt;480&lt;/X&gt;&lt;Y&gt;360&lt;/Y&gt;&lt;/CalibrationResolution&gt;<br/>
		*		&lt;FocalLength&gt;&lt;X&gt;500&lt;/X&gt;&lt;Y&gt;500&lt;/Y&gt;&lt;/FocalLength&gt;<br/>
		*		&lt;PrincipalPoint&gt;&lt;X&gt;240&lt;/X&gt;&lt;Y&gt;180&lt;/Y&gt;&lt;/PrincipalPoint&gt;<br/>
		*	&lt;/Camera&gt;
		*
		*	You can also provide a device identifier. Currently iOS is supported with
		*		"iPhone2" for iPhone 3GS,
		*		"iPhone3" for iPhone 4,
		*		"iPad" for iPad2 and
        *		"iPod" for 4th generation iPod.
        *
        *	If you provide an empty parameter, the system will detect your device automatically (only works for iOS).
		*
		* \param calibrationFile Fully qualified path to the calibration file.
		* \return True if successful, false otherwise.
		*/
		virtual bool loadStandardCameraCalibration(	const std::string& calibrationFile ) = 0;

		/**
		* \brief The main function performing capturing, tracking and rendering.
		*
		*	This method is usually called from the application loop. It takes care of capturing, tracking and rendering.
		*
		* \sa activateCamera
		* \sa stopCamera
		* \sa setImageSource
		* \sa getTrackingValues
		* \sa getValidTrackingValues
		*/
		virtual	void render() = 0;

		/**
		* \brief Set an image file as image source.
		*
		*	This method is used to set the image source for display and (optical) tracking. The image source can be any 
		*	string representing a fully qualified path to an image file e.g. "c:/image/1.jpg". Setting a new image will 
		*	include the tracking step. You do not need to call render() afterwards to perform the tracking.
		*	
		*	Supported image formats are JPG and PNG.
		*
		* \param source A fully qualified path to an image file.
		* \return Resolution of the image if loaded successfully, else a null vector.
		*/
		virtual Vector2di setImageSource( const std::string& source ) = 0;


		/**
		* \brief Activate capturing on a camera.
		*
		*  Activate the given camera and start capturing frames.
		*
		* \param index The index of the camera to activate (zero-based). Pass -1 to deactivate the camera.
		* \param width The desired width of the camera frame.
		* \param height The desired height of the camera frame.
		* \return Actual camera frame resolution (x = width, y = height) on success, else a null vector.
		* \sa stopCamera
		*/
		virtual Vector2di activateCamera( int index, unsigned int width=320, unsigned int height=240 ) = 0;

		/**
		* \brief Deactivate capturing on a camera.
		*
		*	Use this to stop capturing on the current camera.
		*
		* \sa activateCamera
		*/
		virtual void stopCamera() = 0;

		/**
		* \brief Rotates the camera image.
		*
		*	This function is needed for some devices, which have the camera built in rotated.
		* 
		*	The parameter can be
		*		0: no rotation,
		*		1: rotate by 90 degrees,
		*		2: rotate by 180 degrees or
		*		3: rotate by 270 degrees.
		*
		* \param rotation Index of the desired rotation.
		*/
		virtual void setCameraRotation( int rotation ) = 0;

		/**
		* \brief Request a callback that delivers the next camera image.
		*
		*	The image will have the dimensions of the current capture resolution.
        *	It will be delivered through the IUnifeyeMobileCallback.
		*
		*	Note: you need to copy the ImageStuct::buffer, if you need it for later.
		* 
        * \sa registerCallback to register a callback.
		*/
		virtual void requestCameraImage() = 0;

		/**
		* \brief Saves the last captured image to a file.
		*
		*	This function saves the last capture image to a file at a given path.
		*	The image will have the dimensions of the current capture resolution.
		*
		* \note At the moment only ppm files are supported.
		* \param absFilename Fully qualified file path and name, where the image will be stored. The correct extension (ppm) 
		*	needs to be put as well.
		* \return True if successful, false otherwise.
		*/
		virtual bool saveLastCapturedImage( const std::string& absFilename ) = 0;

		/**
		* \brief Get the current rendering frame rate.
		*
		*	The methods returns the rendering performance as number of frames per second.
		*
		* \return The mean rendering performance in frames per second over the last 25 frames.
		*/
		virtual float getRendererFrameRate() = 0;

		/**
		* \brief Get the current tracking frame rate.
		*
		*	The methods returns the image processing performance as number of frames per second.
		*
		* \return The mean image processing performance in frames per second over the last 25 frames.
		*/
		virtual float getTrackingFrameRate() = 0;

		/**
		* \brief Allows to get the state of the tracking system for a given coordinate system.
		*
		*	Depending on the configuration of the tracking system, the provided values may include
		*		a 6DoF camera pose with 3D translation and 3D rotation,
		*		an LLA coordinate (latitude, longitude, altitude) and
		*		a value indicating the quality/certainty of the above.
		*
		* \param cosID The (one-based) index of the coordinate system, the values should be retrieved for.
		* \return A Pose structure containing the tracking values for the desired coordinate system.
		*/
		virtual metaio::Pose getTrackingValues( int cosID) = 0;

		/**
		* \brief Allows to get the state of the tracking system for a given coordinate system.
		*
		*	The provided matrix is compatible with the OpenGL ModelView matrix such that rendered geometry will
		*	e.g. be placed on a marker or markerless tracking target.
		*	If setCameraRotation() was used, this method will return an accordingly rotated matrix.
		*
		* \param cosID The (one-based) index of the coordinate system, the values should be retrieved for.
		* \param matrix An array that will carry 16 float values forming a (4x4) ModelView matrix after execution.
		* \param preMultiplyWithStandardViewMatrix A boolean parameter specifying if the matrix should be
		*	pre-multiplied with metaio's standard ViewMatrix to finally form a ModelView matrix for OpenGL.
		*/
		virtual void getTrackingValues( int cosID, float* matrix, bool preMultiplyWithStandardViewMatrix = true ) = 0;

		/**
		* \brief Get the poses of all tracked coordinate systems.
		* 
		* \return A vector containing the valid poses.
		*/
		virtual std::vector< metaio::Pose > getValidTrackingValues() = 0;

		/** 
		*\brief Computes the spatial relationship, which is a rigid model transformation, between two coordinate systems.
		*
		*	This function computes the spatial relationship between the two given coordinate systems.
		*
		* \param baseCos The (one-based) index of the coordinate system to measure from.
		* \param relativeCos The (one-based) index of the coordinate system to measure to.
		* \param[out] relation Relation (i.e. transformation) between the given baseCOS and the relativeCOS
		* \return True if the relation could be computed, false otherwise (e.g. if one coordinate system has no pose).
		*/
		virtual bool getCosRelation( int baseCos, int relativeCos, metaio::Pose& relation ) = 0;

		/**
		* \brief Set an offset for a particular coordinate system.
		*
		* \param cosID The (one-based) index of the desired coordinate system.
		* \param pose A pose consisting of a 3D translation and a 3D rotation which should act as offset.
		*/
		virtual void setCosOffset( int cosID, const Pose& pose ) = 0;

		/**
		* \brief Inverts the metaio::Pose. This can be interpreted as swapping the roles of the coordinate systems of the camera and the tracking target.
		*
		* \param inPose The pose to invert.
		* \return The inverted pose as metaio::Pose.
		*/
		virtual metaio::Pose invertPose( const metaio::Pose& inPose ) = 0;

		/**
		* \brief Allows to get the OpenGL projection matrix retrieved from camera calibration
		*
		*	The values can be used to set the OpenGL projection matrix according to the camera parameters of the current camera.
		*
		* \sa setStandardCameraCalibration
		* \param matrix An array that will carry 16 float values forming a (4x4) projection matrix after execution.
		*/
		virtual void getProjectionMatrix(float* matrix) = 0;

		/**
		* \brief Get the number of currently tracked coordinate systems.
		*
		*	This function returns the number of coordinate systems that are currently tracked, i.e. have a valid pose.
		*
		* \return The number of tracked coordinate systems.
		*/
		virtual int getNumberOfValidCoordinateSystems() = 0;

		/**
		* \brief Get the number of currently defined coordinate systems.
		*
		*	This function returns the number of coordinate systems that are currently defined.
		*
		* \return The number of defined coordinate systems.
		*/
		virtual int getNumberOfDefinedCoordinateSystems() = 0;


		/**
		* \brief Toggle see-through state of the camera image.
		*
		*	This function can be used to turn off the rendering of the camera image.
		*	It is useful e.g. when overlaying the mobile SDK view on top of another view that renders the camera image.
		*
		* \param seeThrough If true, the camera image is not displayed, otherwise it is drawn as by default.
		*/
		virtual void setSeeThrough( bool seeThrough ) = 0;

		/** \brief Freeze tracking.
		*
		*	Freezes or un-freezes the current tracking. While frozen, the CPU load is reduced.
		*	The tracking values of the last frame before freezing will be returned by the mobile SDK.
		*
		* \param freeze True to freeze the tracking, false to un-freeze it.
		*/
		virtual void setFreezeTracking( bool freeze ) = 0;

		/**
		* \brief Take a screenshot and put it into an ImageStruct.
		* 
		*	Note, you need to free the memory assigned to ImageStruct.
		* 	On Android you don't have access to the buffer of the ImageStruct, so use saveScreenshot instead.
		*
		* \return Returns an ImageStruct containing the screenshot.
		*/
		virtual ImageStruct getScreenshot() = 0;

		/**
		* \brief Take a screenshot and save it to a file.
		*
		*	Currently only the BMP file type is supported. 
		*
		* \param filename The filename where to save the screenshot.
		* \return Returns 0 if saving was successful.
		*/
		virtual int saveScreenshot( const std::string& filename ) = 0;

		/**
		* \brief Returns if the current tracking system (sensor source) uses optical tracking.
		*
		* \return True if the current tracking system (sensor source) uses optical tracking, false otherwise (e.g. GPS and compass).
		*/
		virtual bool isOpticalTracking() = 0;

		/**
		* \brief Retrieve the sensor type that has been loaded using setTrackingData.
		*
		* \return The type of the currently loaded sensor as a string.
		*/
		virtual std::string getSensorType() = 0;

		/**
        * \brief Provide the mobile SDK with the current GPS position.
        *
        *	In order to use GPS based sensor sources the mobile SDK needs to know the current position.
		*	This method has to be used to set and update the current GPS position.
        *
        * \param currentPosition The current LLA position of the device.
        */
        virtual void setSensorLLA( const LLACoordinate& currentPosition ) = 0;

		/**
        * \brief Provide the mobile SDK with the current accelerometer values.
        *
        *	The accelerometer values need to be set if the tracking system uses them.
		*	This is the case when using one of the following sensor sources:
		*		- GPSCompassSensorSource
		*		- FeatureBasedSensorSource using Gravity-Aligned Feature Descriptors
        *
        * \param values A 3D vector containing the current accelerometer values.
        */
        virtual void setSensorAccelerometer( const Vector3d& values) = 0;

        /**
        * \brief Provide the mobile SDK with the current compass heading.
        *
        *	In order to use GPS based sensor sources the mobile SDK needs to know the current compass heading.
        *	This method has to be used to set and update the current compass heading. 
        *
        * \param angle The current compass heading in degrees. The value 0 means the device is pointed toward
		*	true north, 90 means it is pointed due east, 180 means it is pointed due south, and so on.
		*	A negative value indicates that the heading could not be determined.
        *
        */
		virtual void setSensorCompassAngle( float angle ) = 0;

		/**
		* \brief Sets the near and far clipping planes of the renderer.
		*
		* \param nearCP The distance of the near clipping plane in millimeters.
		* \param farCP The distance of the far clipping plane in millimeters.
		*/
		virtual void setRendererClippingPlaneLimits( float nearCP, float farCP) = 0;

		/**
		* \brief Load a 3D model from a given file.
		*
		*	This function loads a 3D geometry from the given file. You can unload the geometry again with unloadGeometry().
		*	Supported 3D formats are OBJ and MD2. 
		*
		* \sa unloadGeometry to unload a geometry.
		*
		* \param geometryFile Path to the geometry file to load.
		* \return Pointer to the geometry. Null pointer if not successful.
		*/
		virtual metaio::IUnifeyeMobileGeometry* loadGeometry( const std::string& geometryFile ) = 0;

		/**
		* \brief Unload a given geometry.
		*
		*	This function unloads a geometry. If you do not want to unload the geometry but hide it, 
		*	use setVisible() instead.
		*
		* \param geometry Pointer to the geometry to be unloaded.
		* \sa loadGeometry to load geometries.
		* \sa setVisible in case you want to hide a geometry instead of unloading it.
		*/
		virtual void unloadGeometry( metaio::IUnifeyeMobileGeometry* geometry) = 0;

		/** 
		* \brief Get a vector containing all loaded geometries.
		*
		*	This function returns a vector containing pointers to all loaded 3D geometries.
		* 
		* \sa loadGeometry to load geometries.
		*
		* \return A vector containing pointers to all geometries.
		*/
		virtual std::vector<metaio::IUnifeyeMobileGeometry*> getLoadedGeometries() = 0;

		/** 
		* \brief Determines the frontmost 3D geometry that is located at a given screen coordinate.
		*
		* \param x The x-component of the screen coordinate.
		* \param y The y-component of the screen coordinate.
		* \param useTriangleTest If true, all triangles are tested which is more accurate but slower. If set to false, bounding boxes are used instead.
		* \return A pointer to the geometry. If no 3D model is located at the given coordinate, it's a null pointer.
		*/
		virtual metaio::IUnifeyeMobileGeometry* getGeometryFromScreenCoordinates( int x, int y, 
			bool useTriangleTest = false ) = 0;

        /** 
        * \brief Converts a given 3D point to screen coordinates.
        *
        * \param cosID The (one-based) index of the coordinate system in which the 3D point is defined.
        * \param point The 3D point to convert.
        * \return A 2D vector containing the screen coordinates.
        */
		virtual Vector2d getScreenCoordinatesFrom3DPosition( int cosID, const Vector3d& point ) = 0;
        
		/**
        * \brief Converts screen coordinates to the corresponding 3D point on the plane of the tracked target.
        *
        * \param cosID The (one-based) index of the coordinate system in which the 3D point is defined.
        * \param point The 2D screen coordinate to use.
        * \return A 3D vector containing the coordinates of the resulting 3D point.
        */
		virtual Vector3d get3DPositionFromScreenCoordinates( int cosID, const Vector2d& point) = 0;

		/** 
		* \brief Set the rendering limits for geometries with LLA coordinates
		*
		*	The near limit will ensure that all geometries closer than this limit are pushed back to the near limit. 
		*	The far limit will ensure that all geometries farther away than this limit are pulled forward to the far limit.
		* 
		*	This is especially helpful for billboards.
		* 
		* \param nearLimit The near limit or 0 to disable.
		* \param farLimit The far limit or 0 disable.
		* \sa setLLALimitsEnabled
		*/
		virtual void setLLAObjectRenderingLimits( int nearLimit, int farLimit ) = 0;

		/**
		* \brief Creates or gets the billboard group object. 
		*
		*	Calling this function the first time will create a billboard group. Calling it again, will return the 
		*	previously created object. 
		* 
		*	A billboard group takes a set of billboards and reorders them in space. All billboards within the set are 
		*	placed in space relative to each other. First the billboard distance to the global origin (3d camera position) 
		*	is adjusted (in the range [nearValue, farValue] see parameters) and then the billboards are arranged in 
		*	clip space that they don't overlap anymore.
		*
		* \param nearValue The minimum billboard-to-camera distance a billboard can have.
		* \param farValue The maximum billboard-to-camera distance a billboard can have
		* \return Pointer to the billboard group.
		*/
		virtual metaio::IUnifeyeBillboardGroup* createBillboardGroup( float nearValue, float farValue ) = 0;
		
		/**
		* \brief Create a new image billboard object from an image file.
		*
		* \param texturePath The path to the image file to create a billboard from.
		* \return A pointer to the created billboard geometry.
		*/
		virtual metaio::IUnifeyeMobileGeometry* loadImageBillboard( const std::string& texturePath ) = 0;

        /**
         * \brief Create an image billboard from an image which is already in memory.
         *
         * \param textureName Assign a unique identifier to the texture.
         * \param image The new image in memory.
         * \return A pointer to the created billboard geometry.
         */
        virtual metaio::IUnifeyeMobileGeometry* loadImageBillboard( const std::string& textureName,
                                                           const ImageStruct& image  ) = 0;
        
		/**
		* \brief Register a callback interface to the Mobile SDK.
		*
		* \param callback A pointer to the class that should receive callbacks.
		*/
		virtual void registerCallback( metaio::IUnifeyeMobileCallback* callback ) = 0;

		/**
		* \brief Creates an environment map, which can be seen as a reflection on 3D geometries.
		*
		*	This feature can be used to attach a reflection map to an object.
		*	
		*	The six image files contained in the provided folder need to have the following names:
		*	"positive_x.png", "positive_y.png", "positive_z.png",
		*	"negative_x.png", "negative_y.png",	"negative_z.png".
		*	
		* \param folder The path of a folder that should contain six PNG image files containing
		*	the textures for the six faces of the cube.
		* \return Returns true, if the environment map was successfully loaded.
		*/
		virtual bool loadEnvironmentMap( const std::string& folder ) = 0;

		/**
		* \brief This function will pause all currently running movie textures. 
		*/
		virtual void pauseAllMovieTextures() = 0;


};


} // namespace metaio

#endif //___AS_ARMOBILESYSTEM_H_INCLUDED___
