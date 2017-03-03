#pragma once

#include "getvfunc.h"
#include "Color.h"

namespace CSGO
{
	class Surface
	{
	public:
		// Create a font
		long CreateFont()
		{
			typedef	int(__thiscall* oCreateFont)(void*);

			return getvfunc<oCreateFont>(this, 71)(this);
		}

		// Set font glyph set
		void SetFontGlyphSet(unsigned long& font, const char* fontName, int h, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
		{
			typedef void(__thiscall* oSFGS)(void*, unsigned long, const char*, int, int, int, int, int, int, int);

			return getvfunc<oSFGS>(this, 72)(this, font, fontName, h, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
		}

		// Draw color
		void DrawSetColor(Color col)
		{
			typedef void(__thiscall* oDrawSetColor)(void*, Color);

			return getvfunc<oDrawSetColor>(this, 14)(this, col);
		}

		void DrawOutlinedRect(int x, int y, int w, int h)
		{
			typedef void(__thiscall* oOutlinedRect)(void*, int, int, int, int);

			return getvfunc<oOutlinedRect>(this, 18)(this, x, y, w, h);
		}

		// Text to draw, length, length of text, and type, type of text. Nor
		void DrawPrintText(wchar_t* text, int length, int type)
		{

			typedef void(__thiscall* oTTP) (void*, wchar_t*, int, int);

			return getvfunc<oTTP>(this, 28) (this, text, length, type);
		}

		void DrawSetTextPos(int x, int y)
		{
			typedef void(__thiscall* oSetTextPos)(void*, int, int);

			return getvfunc<oSetTextPos>(this, 26)(this, x, y);
		}

		void DrawSetTextFont(int font)
		{
			typedef void(__thiscall* oFont)(void*, int);

			return getvfunc<oFont>(this, 23)(this, font);
		}

		void DrawSetTextColor(Color col)
		{
			typedef void(__thiscall* oCol) (void*, Color);

			return getvfunc<oCol>(this, 24)(this, col);
		}
	};
}
