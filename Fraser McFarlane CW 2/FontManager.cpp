
#include "FontManager.h"

FontManager* FontManager::pInstance = NULL;


FontManager* FontManager::getInstance() //gets font intsnce 
{
	if (pInstance == NULL)
	{
		pInstance = new FontManager();
	}
	return FontManager::pInstance;
}


FontManager::FontManager() //default contructor
{

}

FontManager::~FontManager()	//destruct						
{
	deleteFont();
}
void FontManager::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font map
{
	if (!getFont(fontName))
	{
		Font * newFont = new Font(fileName, fontSize);
		gameFonts.insert(make_pair(fontName, newFont));
	}
}

Font* FontManager::getFont(LPCSTR fontName)	// return the font 
{
	map<LPCSTR, Font*>::iterator theFont = gameFonts.find(fontName);
	if (theFont != gameFonts.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}

void FontManager::deleteFont()		// deletes the font.
{
	for (map<LPCSTR, Font*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++)
	{
		delete theFont->second;
	}
}
