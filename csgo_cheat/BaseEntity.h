#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <iostream>
#include <Windows.h>
#include "Vector.h"
#include "QAngle.h"
#include "getvfunc.h"

struct model_t;

namespace CSGO
{
	class BaseEntity
	{
	public:
		typedef int(__thiscall* oGetTeam)(void*);
		typedef void(__thiscall* oRenderBounds)(void*, Vector&, Vector&);
		typedef bool(__thiscall* oAlive)(void*);

		void GetRenderBounds(Vector& min, Vector& max)
		{
			void* renderable = (PVOID)(this + 0x4);

			return getvfunc<oRenderBounds>(this, 20)(renderable, min, max);
		}

		bool IsAlive()
		{
			return getvfunc<oAlive>(this, 200)(this);
		}

		bool IsPlayer()
		{
			typedef bool(__thiscall* oPlayer)(void*);

			return getvfunc<oPlayer>(this, 202)(this);
		}

		bool IsDormant()
		{
			return *(bool*)((DWORD)this + 0xE9);
		}

		model_t* GetModel()
		{
			return *(model_t**)((DWORD)this + 0x6C);
		}

		int GetFlags()
		{
			return (int)((DWORD)this + (DWORD)0x100);
		}

		Vector& GetVecOrigin()
		{
			return *(Vector*)((DWORD)this + 0x134);
		}

		QAngle& GetAbsAngles()
		{
			return *(QAngle*)((DWORD)this + 0x4D0C);
		}

		int GetTeam()
		{
			return getvfunc<oGetTeam>(this, 124)(this);
		}
	};
}

#endif
