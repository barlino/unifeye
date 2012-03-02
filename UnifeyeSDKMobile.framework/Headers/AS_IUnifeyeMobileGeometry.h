#ifndef __AS_IUNIFEYEMOBILEGEOMETRY_H_INCLUDED__
#define __AS_IUNIFEYEMOBILEGEOMETRY_H_INCLUDED__
/*
 *  metaio Mobile SDK
 *	Version 3.0
 *
 *  Copyright 2011 metaio GmbH. All rights reserved.
 *
 */
#include <vector>
#include <string>

#include "AS_MobileStructs.h"
#include "AS_ColorFormat.h"


namespace metaio
{
		/// Enumeration to encode the type of a geometry
		enum UnifeyeMobileGeometryType
		{
			GEOMETRYTYPE_GEOMETRY3D,
			GEOMETRYTYPE_BILLBOARD,
			GEOMETRYTYPE_UNKNOWN,
			GEOMETRYTYPE_GEOMETRY3D_GL20
		};

		/** 
		 * \brief General interface for a 3D geometry that can be loaded within the system
		 * 
		 */
		class IUnifeyeMobileGeometry
		{
		public:
			virtual ~IUnifeyeMobileGeometry() {};

				
			/** 
			 * \brief Set the translation of the 3D model.
			 * \param translation The 3D translation vector in millimeters.
			 * \param concat If true, the new translation is added to the existing one, otherwise it is overwritten.
			 * \sa getMoveTranslation
			 */
			virtual void setMoveTranslation( const Vector3d& translation, bool concat=false ) = 0;
		

			/**
			* \brief Get the current translation of the 3D model.
			* \return A 3D vector containing the translation in millimeters.
			* \sa setMoveTranslation
			*/
			virtual Vector3d getMoveTranslation() = 0;


			/**
			* \brief Set the translation of the 3D model to an LLA coordinate.
			*	The system will then adjust its Cartesian offset in the renderer accordingly.
			*	Note: The altitude is ignored, if you want adjust the height use setMoveTranslation
			* \param llaCoorindate The LLA (latitude, longitude, altitude) to set as translation.
			* \sa setMoveTranslation and getMoveTranslation
			* \sa getMoveTranslationLLA
			* \sa getMoveTranslationLLACartesian
			*/
			virtual void setMoveTranslationLLA( LLACoordinate llaCoorindate )  = 0;


			/**
			* \brief Get the translation of the 3D model as LLA coordinate.
			* \return The LLA (latitude, longitude, altitude) coordinate of the geometry.
			* \sa setMoveTranslation and getMoveTranslation
			* \sa setMoveTranslationLLA
			* \sa getMoveTranslationLLACartesian
			*/
			virtual LLACoordinate getMoveTranslationLLA() = 0;


			/**
			* \brief Get the Cartesian translation of the 3D model with an LLA coordinate.
			* \return A 3D vector containing the translation in millimeters corresponding to the 3D model's LLA (latitude, longitude, altitude) coordinate.
			* \sa setMoveTranslation and getMoveTranslation
			* \sa setMoveTranslationLLA and getMoveTranslationLLA
			*/
			virtual Vector3d getMoveTranslationLLACartesian() = 0;


			/** 
			 * \brief Set the scale of the 3D model.
			 * \param scale Scaling vector (x,y,z).
			 * \param concat If true, the new scale is multiplied with existing scale.
			 * \sa getMoveScale
			 */
			virtual void setMoveScale( const Vector3d& scale, bool concat=false)  = 0;
			

			/**
			* \brief Get the current scale of the 3D model.
			* \return The scaling vector (x,y,z).
			* \sa setMoveScale
			*/
			virtual Vector3d getMoveScale() = 0;


			/**
			* \brief Set the rotation of the 3D model in axis angle representation.
			*
			* \param rotation The rotation in axis angle representation (x, y, z, angle in radians).
			* \param concat If true, the new rotation is concatenated with an existing rotation.
			* \sa getMoveRotation
			*/
			virtual void setMoveRotation(const Vector4d& rotation, bool concat=false)  = 0;
			

			/**
			* \brief Get the current rotation of the 3D model in axis angle representation.
			* \return The rotation in axis angle representation (x, y, z, angle in radians).
			* \sa setMoveRotation
			*/
			virtual Vector4d getMoveRotation() = 0;


			/**
			* \brief Set the rotation of the model in Euler angles representation.
			*
			*	This rotation is applied on the lowest level and will be affected by all
			*	other rotations in the structure (like tracking). It can be used to compensate
			*	an undesired orientation of the 3D model (e.g. a model lying on the side).
			*
			* \param The rotation vector in Euler angles representation, where the Euler angles
			*	must be in the order (x, y, z) and expressed in radians.
			* \param concat If true, the new rotation is concatenated with an existing rotation.
			* \sa getMoveRotation
			*/
			virtual void setMoveRotation(const Vector3d& rotation, bool concat=false) = 0;


			/** 
			* \brief Determine if the 3D model is currently being rendered.
			* \return True if the geometry is being rendered, false otherwise.
			*/
			virtual bool getIsRendered() = 0;


			/**
			* \brief Determine the visibility of the 3D model.
			* \return True if the 3D model is set visible, false otherwise.
			* \sa setVisible
			*/			
			virtual bool getIsVisible() = 0;


			/**
			* \brief Set the visibility of the 3D model.
			* \param visible True if the 3D model should be visible, false if it should be hidden.
			* \sa getIsVisible
			* \sa setOcclusionMode
			* \sa setTransparency
			* \sa setRenderAsXray
			* \sa setPickingEnabled
			*/
			virtual void setVisible(bool visible) = 0;


			/**
			* \brief Set the rendering mode of a 3D model to "x-ray".
			*
			*	This method shall be used if a model should be drawn on top of
			*	all others and therefore ignore the z-buffer.
			*	It is only available with OpenGL ES 2.0 rendering.
			* 
			* \param xray If true, the 3D model will be rendered with the x-ray effect, otherwise it will be displayed normally.
			* \sa setVisible and getIsVisible
			* \sa setOcclusionMode
			* \sa setTransparency
			* \sa setPickingEnabled
			*/
			virtual void setRenderAsXray(bool xray) = 0;


			/**
			* \brief Set the occlusion mode of the 3D model.
			*
			* \param occlude If true, the 3D model is not displayed but only used to occlude other 3D models, otherwise it will be displayed normally.
			* \sa setVisible and getIsVisible
			* \sa setTransparency
			* \sa setRenderAsXray
			* \sa setPickingEnabled
			*/
			virtual void setOcclusionMode( bool occlude ) = 0;


			/**
			* \brief Set the transparency of the 3D model.
			*
			* \param transparency The transparency value, where 255 corresponds to an invisible model and 0 corresponds to a fully opaque model).
			* \sa setVisible and getIsVisible
			* \sa setOcclusionMode
			* \sa setRenderAsXray
			* \sa setPickingEnabled
			*/
			virtual void setTransparency( unsigned char transparency ) = 0;


			/**
			 * \brief Start a specific animation of the 3D model.
			 * \param animationName Identifier of the animation.
			 * \param loop If true, the animation is looped, otherwise it is only played once.
			 * \sa setAnimationSpeed
			 */
			virtual void startAnimation( const std::string& animationName, bool loop ) = 0;


			/**
			* \brief Set the animation speed of the model.
			* \param fps Desired animation speed in frames per second.
			*/
			virtual void setAnimationSpeed( float fps ) = 0;


			/**
			 * \brief Get the (axis-aligned) bounding box of the 3D model.
			 *
			 * \return The bounding box of the 3D model.
			 */
			virtual BoundingBox getBoundingBox() = 0;		
			

			/**
			 * \brief Bind the 3D model to a specific coordinate system (COS).
			 * \param cosID The (one based) index of the coordinate system to bind the 3D model to.
			 * \sa getCos
			 */
			virtual void setCos(int cosID) = 0;
			

			/**
			 * \brief Get the index of the coordinate system (COS) the 3D model is bound to.
			 * \return The (one based) index of the coordinate system the 3D model is bound to.
			 * \sa setCos
			 */
			virtual int getCos() = 0;
			

			/**
			 * \brief Get the type of the 3D model.
			 * \return The UnifeyeMobileGeometryType of the 3D model.
			 */
			virtual UnifeyeMobileGeometryType getType()  = 0;


			/**
			 * \brief Activate or deactivate the usage of limits for updateMoveTranslationFromLLA.
			 *
			 *	If disabled, the geometry will ignore the near and far limit
			 *	passed in updateMoveTranslationFromLLA and always render
			 *	the object the the real location. (default is true)
			 *
			 * \param enabled True to enable, false to disable.
			 * \sa updateMoveTranslationFromLLA
			 */
			virtual void setLLALimitsEnabled ( bool enabled ) = 0;
			

			/** 
			 * \brief Enable or disable picking for the 3D model.
			 *
			 *	This method will modify the renderer bit mask for the model.
			 *	All objects with bit mask 1 will be used for picking, others not.
			 * 
			 * \param enabled True to enable picking of this model, false to disable it.
			 * \sa setVisible and getIsVisible
			 * \sa setOcclusionMode
			 * \sa setTransparency
			 * \sa setPickingEnabled
			 * \sa setRenderAsXray
			 */
			virtual void setPickingEnabled( bool enabled )  = 0;

			/**
			 * \brief Set image from given file path as texture for the 3D model.
			 *
			 *	Supported formats are PNG and JPG.
			 *
			 * \param texturePath Path to the texture image file.
			 */
			virtual void setTexture( const std::string& texturePath ) = 0;

			/**
			 * \brief Set image from memory as texture for the 3D model.
			 *
			 * \param textureName A name that should be assigned to the texture (for reuse).
			 * \param image The actual image.
			 * \param updateable Flag to signal, that this image will be frequently updated.
			 */
			virtual void setTexture( const std::string& textureName, const ImageStruct& image, const bool updateable = false) = 0;

			/**
			* \brief Continuously set a h263 avi-movie's frames as texture for the 3D model.
			*
			*	The supported movie format is: left side color movie, right side transparency (red channel).
			*
			* \param filename Filename of an h263 encoded avi-movie.
			* \param loop If true, the movie gets rendered in a loop, otherwise it is played only once.
			* \param transparent If true, the movie shall get rendered as a transparent movie, otherwise not.
			* \sa removeMovieTexture
			*/
			virtual void setMovieTexture( const std::string& filename, const bool loop, 
				const bool transparent = false) = 0;

			/** 
			* \brief Remove the movie texture of the 3D model.
			* \sa setMovieTexture
			*/
			virtual void removeMovieTexture() = 0;

			/** 
			* \brief Stop the playback of a movie texture.
			* \sa playMovieTexture
			* \sa pauseMovieTexture
			*/
			virtual void stopMovieTexture() = 0;

			/** 
			* \brief Start the playback of a movie texture.
			* \sa pauseMovieTexture
			* \sa stopMovieTexture
			*/
			virtual void playMovieTexture() = 0;

			/** 
			* \brief Pause the playback of a movie texture.
			* \sa playMovieTexture
			* \sa stopMovieTexture
			*/
			virtual void pauseMovieTexture() = 0;

		};
}
#endif //__AS_IUNIFEYEMOBILEGEOMETRY_H_INCLUDED__

