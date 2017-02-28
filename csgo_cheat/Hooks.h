#ifndef HOOKS_H
#define HOOKS_H

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
}

#endif