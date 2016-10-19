#ifndef _CORE_GAMESDESCRIPTION_H_
#define _CORE_GAMESDESCRIPTION_H_

#include "Types.h"
#include "Support\Color.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"

#include <string>

namespace core
{
	/**
	GameDescription is used to describe the Game, this indicates the screen size, screen position, if is fullscreen...
	*/
	class GameDescription {
	friend class Game;
	protected:
		Vector2D<uint32>								mScreenSize;
		Vector2D<uint32>								mScreenPosition;
		Color											mClearColor;
		BOOL											mFullScreen;
		Vector3D<float32>								mPhysicsGravity;
		std::string										mRootDir;
		float32											mPhysicUpdatedFrequency;
	public:
		GameDescription() : mScreenSize(500,500), mScreenPosition(50,50), mClearColor(), 
			mFullScreen(FALSE), mPhysicsGravity(0.0f, -9.81f, 0.0f), mPhysicUpdatedFrequency(0.02f){}
		~GameDescription() {}
		/** Assigns screen size
		@param aX width
		@param aY height
		*/
		void											SetScreenSize(uint32 aX, uint32 aY);
		/** Assigns screen position
		@param aX X pos
		@param aY Y pos
		*/
		void											SetScreenPosition(uint32 aX, uint32 aY);
		/** Assigns draw color
		@param aColor Color to assign
		*/
		void											SetClearColor(const Color &aColor);
		/** Assigns draw color
		@param aR Red component to assign
		@param aG Green component to assign
		@param aB Blue component to assign
		@param aA Alpha component to assign
		*/
		void											SetClearColor(float32 aR, float32 aG, float32 aB, float32 aA);
		/** Assigns draw color
		@param aR Red component to assign
		@param aG Green component to assign
		@param aB Blue component to assign
		@param aA Alpha component to assign
		*/
		void											SetClearColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA);
		/** Start windows in full screen
		@param aFullScreen
		*/
		void											SetFullScreen(BOOL aFullScreen);
		void											SetRootDir(const std::string& aDirectory);
		void											SetPhysicsGravity(const Vector3D<float32>& aPhysicsGravity);
		void											SetPhysicUpdatedFrequency(float32 aPhysicUpdatedFrequency);
			
	}; // GameDescription
} // namespace core
#endif // _CORE_GAMESDESCRIPTION_H_
