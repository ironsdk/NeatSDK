#pragma once

#include "ConVar.h"
#include "getvfunc.h"

namespace CSGO
{
	class CVar
	{
	public:
		typedef CSGO::ConVar*(__thiscall* oFindVar)(void*, const char*);

		CSGO::ConVar* FindVar(const char* name)
		{
			return getvfunc<oFindVar>(this, 14)(this, name);
		}
	};
}
