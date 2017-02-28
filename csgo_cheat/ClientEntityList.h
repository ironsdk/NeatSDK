#ifndef CLIENTENTITYLIST_H
#define CLIENTENTITYLIST_H

#include "getvfunc.h"
#include "BaseEntity.h"

namespace CSGO
{
	class ClientEntityList
	{
	public:
		int GetHighestEntityIndex(void)
		{
			typedef int(__thiscall* fnGetHighestIndex)(void*);

			return getvfunc<fnGetHighestIndex>(this, 6)(this);
		}

		CSGO::BaseEntity* GetClientEntity(int index)
		{
			typedef BaseEntity*(__thiscall* fnClientEnt)(void*, int);

			return getvfunc<fnClientEnt>(this, 3)(this, index);
		}
	};
}

#endif