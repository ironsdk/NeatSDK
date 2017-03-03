#pragma once

#include "Vector.h"

/*
bhop stuff
*/
#define IN_JUMP (1 << 1)
#define	FL_ONGROUND (1 << 0)

namespace CSGO
{
	class UserCmd
	{
	public:
		int	commandNumber;
		int	tickCount;
		Vector viewAngles;
		Vector aimDirection;
		Vector move;
		int	buttons;
		char impulse;
		int weaponSelect;
		int	weaponSubtype;
		int	randomSeed;
		short mousedx;
		short mousedy;
		bool hasBeenPredicted;
	};
}
