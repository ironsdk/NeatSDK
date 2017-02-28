#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include "getvfunc.h"

namespace CSGO
{
	class BaseHudChat
	{
	public:
		typedef void(__cdecl* baseChatShit)(void*, int, int, const char*, ...);

		void ChatPrintf(int iPlayerIndex, int iFilter, const char* msg, ...)
		{
			return getvfunc<baseChatShit>(this, 26)(this, iPlayerIndex, iFilter, msg);
		}
	};
}

#endif