/*
==========================================================================
Font.h
==========================================================================
*/

#ifndef _Font_H
#define _Font_H

// OpenGL Headers
#include "GameConstants.h"

using namespace std;

class Font
{
private:
	FTFont* theFont;


public:
	Font();
	Font(LPCSTR fontFileName, int fontSize);
	~Font();
	FTFont* getFont();
	void printText(LPCSTR text, FTPoint textPos);
	void printText(LPCSTR text, FTPoint textPos, colour3f textColour);

};
#endif