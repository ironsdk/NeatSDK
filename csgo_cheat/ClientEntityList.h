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
			typedef int(__thiscall* oGetHighestIndex)(void*);

			return getvfunc<oGetHighestIndex>(this, 6)(this);
		}

		CSGO::BaseEntity* GetClientEntity(int index)
		{
			typedef BaseEntity*(__thiscall* oClientEnt)(void*, int);

			return getvfunc<oClientEnt>(this, 3)(this, index);
		}
	};
}

#endif
