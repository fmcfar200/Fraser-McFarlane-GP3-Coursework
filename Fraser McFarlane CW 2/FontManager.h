
#ifndef _FontManager_H
#define _FontManager_H
#include <FTGL\ftgl.h>
#include "Font.h"

class FontManager
{
private:

	static FontManager* pInstance;	//instance priv
	map<LPCSTR, Font*> gameFonts;	//font map

public:
	static FontManager* getInstance(); //getter for instance

	FontManager();								// Constructor
	~FontManager();							// Destructor.
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);  // add font to the Font 
	Font* getFont(LPCSTR fontName);				// return the font for use
	void deleteFont();								// delete font.

};

#endif