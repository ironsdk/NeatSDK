#pragma once

#include <iostream>
#include "getvfunc.h"
#include "Surface.h"

extern CSGO::Surface* surf;

enum FontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

namespace CSGO
{
  class Render
  {
  public:
    void DrawInlineRect(int X, int Y, int W, int H, CSGO::Color rgba)
    {
      DrawRect(X, Y, W, H, rgba);
      DrawRect(X + 1, Y + 1, W - 2, H - 2, CSGO::Color(0, 0, 0, 255));
      DrawRect(X - 1, Y - 1, W + 2, H + 2, CSGO::Color(0, 0, 0, 255));
    }

    void DrawRect(int X, int Y, int W, int H, CSGO::Color rgba)
    {
      surf->DrawSetColor(rgba);
      surf->DrawOutlinedRect(X, Y, X + W, Y + H);
    }

    void InitFont(unsigned long &hFont, const char* szFontName, int size, FontFlags flags, int weight)
    {
      hFont = surf->CreateFont();
      surf->SetFontGlyphSet(hFont, szFontName, size, weight, 0, 0, flags);
    }

    void DrawString1(int x, int y, CSGO::Color rgba, int font, const char* text, ...)
    {
      if (text == NULL)
      {
        return;
      }

      va_list va_alist;
      char buffer[1024] = { '\0' };
      wchar_t string[1024] = { '\0' };

      va_start(va_alist, text);
      vsprintf_s(buffer, text, va_alist);
      va_end(va_alist);

      wsprintfW(string, L"%S", buffer);

      surf->DrawSetTextPos(x, y);
      surf->DrawSetTextFont(font);
      surf->DrawSetTextColor(rgba);
      surf->DrawPrintText(string, wcslen(string), 0);
    }
  };
}
