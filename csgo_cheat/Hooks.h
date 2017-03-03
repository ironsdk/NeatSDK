#pragma once

#include "ViewSetup.h"
#include "UserCmd.h"

/*
	This namespace is ONLY for hooks that are actually major (createmove, painttraverse, etc.)
	Sorry if this is confusing
*/

namespace Hooks
{
	typedef void(__thiscall* oCreateMove)(void*, float, CSGO::UserCmd*);
	typedef void(__thiscall* oOverrideView)(void*, CSGO::ViewSetup* setup);
	typedef void(__thiscall* oPaintTraverse)(void*, unsigned int, bool, bool);
}
