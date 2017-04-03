#ifndef _GAME_PLATFORMMERBACKGROUND_H_
#define _GAME_PLATFORMMERBACKGROUND_H_

#include "Types.h"
#include "Logic/IGameObject.h"


namespace game
{

	class PlatformerBackground : public logic::IGameObject
	{

	public:
		PlatformerBackground() : IGameObject(){}
		virtual ~PlatformerBackground() {}

		virtual void									Init(BOOL aActive);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();
	
	}; // PlatformerBackground
} // namespace game
#endif // _GAME_PLATFORMMERBACKGROUND_H_
