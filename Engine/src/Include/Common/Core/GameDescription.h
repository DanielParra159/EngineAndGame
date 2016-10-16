#ifndef _CORE_GAMESDESCRIPTION_H_
#define _CORE_GAMESDESCRIPTION_H_

#include "Types.h"
#include "Support\Color.h"
#include "Support\Vector2D.h"

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
		Color											mRenderDrawColor;
		BOOL											mFullScreen;
		float32											mPhysicsGravity;
		std::string										mRootDir;
	public:
		GameDescription() : mScreenSize(500,500), mScreenPosition(50,50), mRenderDrawColor(), mFullScreen(FALSE), mPhysicsGravity(-9.81f) {}
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
		void											SetRenderDrawColor(const Color &aColor);
		/** Assigns draw color
		@param aR Red component to assign
		@param aG Green component to assign
		@param aB Blue component to assign
		@param aA Alpha component to assign
		*/
		void											SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA);
		/** Start windows in full screen
		@param aFullScreen
		*/
		void											SetFullScreen(BOOL aFullScreen);
		void											SetRootDir(const std::string& aDirectory);
		void											SetPhysicsGravity(float32 aPhysicsGravity);
			
	}; // GameDescription
} // namespace core
#endif // _CORE_GAMESDESCRIPTION_H_
