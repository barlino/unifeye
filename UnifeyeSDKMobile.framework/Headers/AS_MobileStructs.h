#ifndef _AS_TYPEDEFS_H_
#define _AS_TYPEDEFS_H_


#include "AS_ColorFormat.h"
#include <string>

namespace metaio
{
	/** @brief Structure that defines a 2D vector */
	struct Vector2d
	{
		float x;	///< x component of the vector
		float y;	///< y component of the vector

		Vector2d() : x(0.0f), y(0.0f){};

		/**
		* \brief Structure that defines a 2D vector
		* \param _x x component of the vector
		* \param _y y component of the vector
		*/
		Vector2d( float _x, float _y ) : x(_x), y(_y) {};
		
		/**
		* \brief Determine if the vector is null
		* \return true if null vector, else false
		*/
		bool isNull() const { return (x==0.f && y==0.f); }
        
	};

	/** @brief Structure that defines an integer 2D vector */
	struct Vector2di
	{
		int x;	///< x component of the vector
		int y;	///< y component of the vector

		/**
		* \brief Structure that defines an integer 2D vector
		* \param _x x component of the vector
		* \param _y y component of the vector
		*/
		Vector2di( int _x=0, int _y=0 ) : x(_x), y(_y) {};
		
		/**
		* \brief Determine if the vector is null
		* \return true if null vector, else false
		*/
		bool isNull() const { return (x==0 && y==0); }
        
	};


	/** @brief Structure that defines a 3D vector */
	struct Vector3d
	{
		float x;	///< x component of the vector
		float y;	///< y component of the vector
		float z;	///< z component of the vector

		Vector3d() : x(0.0f), y(0.0f), z(0.0f){};
		/**
		* \brief Structure that defines a 3D vector
		* \param _x x component of the vector
		* \param _y y component of the vector
		* \param _z z component of the vector
		*/
		Vector3d( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {};
		
		/**
		* \brief Determine if the vector is null
		* \return true if null vector, else false
		*/
		bool isNull() const { return (x==0.f && y==0.f && z==0.f); }
        

	};


	/** @brief Structure that defines a 4D vector */
	struct Vector4d
	{
		float x;	///< x component of the vector
		float y;	///< y component of the vector
		float z;	///< z component of the vector
		float w;	///< w component of the vector

		Vector4d() : x(0.0f), y(0.0f), z(0.0f), w(1.0f){};
		/**
		* \brief Structure that defines a 4D vector
		* \param _x x component of the vector
		* \param _y y component of the vector
		* \param _z z component of the vector
		* \param _w w component of the vector
		*/
		Vector4d( float _x, float _y, float _z, float _w ) : 
			x(_x), y(_y), z(_z),w(_w) {};
		
		/**
		* \brief Determine if the vector is null
		* \return true if null vector, else false
		*/
		bool isNull() const { return (x==0.f && y==0.f && z==0.f && w==0.f); }
        
	};

	/** @brief Structure that defines LLA coordinates */
	struct LLACoordinate
	{
		double latitude;	///< The latitude
		double longitude;	///< The longitude
		double altitude;	///< altitude
		double accuracy;	///< the accuracy of the GPS position

		LLACoordinate() : latitude(0.0), longitude(0.0), altitude(0.0), accuracy(0.0)
		{
		};

		/**
		* \brief Structure that defines LLA coordinates
		* \note The altitude is ignored, if you want adjust the height use IUnifeyeMobileGeometry::setMoveTranslation
		* \param _lat	latitude component
		* \param _long	longitude component
		* \param _alt	altitude component
		* \param _acc	accuracy component
		*/
		LLACoordinate( double _lat, double _long, double _alt, double _acc ) :
		latitude(_lat), longitude(_long), altitude(_alt), accuracy(_acc)
		{

		};
		
		/**
		* \brief Determine if location is invalid (null)
		* \return true if invalid, else false
		*/
		bool isNull() const { return (latitude==0.0 && longitude==0.0 && altitude==0.0 && accuracy<=0.0); }

        /** \brief Determine if two LLACoordinates are equal 
		\param rhs LLACorindate to compare with
         * \return true if they are qual
         */
        bool operator==(const LLACoordinate& rhs)const
        {
            return ( ( latitude == rhs.latitude ) &&
                     ( longitude == rhs.longitude ) && 
                     ( altitude == rhs.altitude ) && 
                     ( accuracy == rhs.accuracy )
                    );
        }
	};
		
	/**
	 * @brief Structure that defines a 3D pose
	 */
	struct Pose
	{

		/// Constructor for the Pose structure.
		Pose()
		{
			//Set translation.
			translation.x = 0;
			translation.y = 0;
			translation.z = 0;
			//Set rotation.
			rotation.x = 0;
			rotation.y = 0;
			rotation.z = 0;
			rotation.w = 1;
			//Set quality value.
			quality =  0;
			//Set the coordinate system ID
			cosID = 0;
			//Set LLA coordinate
			llaCoordinate.latitude = 0;
			llaCoordinate.longitude = 0;
			llaCoordinate.altitude = 0;
			llaCoordinate.accuracy = 0;
			// init additionalValues with an empty string
			additionalValues = "empty";
		}

		/** 
		* \brief Constructor for a pose that defines translation and 
		* rotation.
		*
		* \param _tx Translation in x direction
		* \param _ty Translation in y direction
		* \param _tz Translation in z direction
		* \param _q1 First component of the rotation quaternion
		* \param _q2 Second component of the rotation quaternion
		* \param _q3 Third component of the rotation quaternion
		* \param _q4 Fourth component of the rotation quaternion
		* \param qual Value between 0 and 1 defining the tracking 
		* \param _cosID the coordinate system ID
		*	quality. (1=tracking, 0=not tracking)
		*/
		Pose(float _tx, float _ty, float _tz, float _q1, float _q2, 
			float _q3, float _q4, float qual, int _cosID)
		{
			//Set translation.
			translation.x = _tx;
			translation.y = _ty;
			translation.z = _tz;
			//Set rotation.
			rotation.x = _q1;
			rotation.y= _q2;
			rotation.z = _q3;
			rotation.w = _q4;
			//Set quality value.
			quality =  qual;
			//Set the coordinate system id
			cosID = _cosID;
			// init additionalValues with an empty string
			additionalValues = "empty";
		}

		Vector3d translation;			///< Translation component of the pose
		Vector4d rotation;				///< Rotation component of the pose
		LLACoordinate llaCoordinate;	///< if we have gloval coordinate frame;
		/** Value between 0 and 1 defining the 	tracking quality. 
			(1=tracking, 0=not tracking, 0.5 means tracking is coming from a fuser) */
		float quality;
		int cosID;						///< The ID of the coordinate system
		std::string additionalValues;	///< Room for additional values provided by a sensor that cannot be expressed with translation and rotation properly.
        
        
	};
	
	/** \brief A helper struct to represent a bounding box.
	*/
	struct BoundingBox
	{
		Vector3d min; ///< Vector containing the minimum x,y,z values
		Vector3d max; ///< Vector containing the maximum x,y,z values
	};


	/** @brief Structure that defines a image*/
	struct ImageStruct
	{
		unsigned char *buffer;				///< pointer to the pixels
		
		int width;							///< width component of the vector
		int height; 						///< height component of the vector
		metaio::common::ECOLOR_FORMAT colorFormat;	///< color format
		bool originIsUpperLeft;				///< true if the orgigin is in the upper left corner; false, if lower left

		ImageStruct() : buffer(0), width(0), height(0), 
			colorFormat(common::ECF_UNKNOWN), originIsUpperLeft(true) {};


		/**
		* \brief Constructor for image struct
		*
		* \param _buffer pointer to the image data
		* \param _width width of the image
		* \param _height height of the image
		* \param _colorFormat the color format 
		* \param _originIsUpperLeft true if the origin is upper left corner, false if lower left
		* \return 
		*/
		ImageStruct( unsigned char* _buffer, int _width, int _height, 
			metaio::common::ECOLOR_FORMAT _colorFormat, bool _originIsUpperLeft) 
				:  buffer(_buffer), width(_width), height(_height), 
				colorFormat(_colorFormat), originIsUpperLeft(_originIsUpperLeft) {};

	};

	/** Helper function to allow callbacks on android*/
	struct ByteBuffer
	{
		unsigned char *buffer;		///< pointer to a binary buffer
		int length;					///< legnth of the buffer


		/**
		* \brief Constructor for ByteBuffer struct
		*
		* \param _buffer pointer to the binary data
		* \param _length length of the buffer
		* \return 
		*/
		ByteBuffer( unsigned char* _buffer, int _length ) 
				:  buffer(_buffer), length(_length){};

	};
} // namespace metaio

#endif
