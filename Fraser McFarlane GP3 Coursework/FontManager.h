/*
== == == == == == == == =
FontManager.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/
#ifndef _FontManager_H
#define _FontManager_H
#include "GameConstants.h"
#include "Font.h"

class FontManager
{
private:

	static FontManager* pInstance;
	map<LPCSTR, Font*> gameFonts;

public:
	static FontManager* getInstance();

	FontManager();								// Constructor
	~FontManager();							// Destructor.
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);  // add font to the Font collection
	Font* getFont(LPCSTR fontName);				// return the font for use
	void deleteFont();								// delete font.

};

#endif