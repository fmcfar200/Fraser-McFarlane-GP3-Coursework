
#ifndef _Font_H
#define _Font_H

#include "Constants.h"

// OpenGL Headers
#include <FTGL\ftgl.h>

class Font
{
private:
	FTFont* theFont;	//font object


public:
	Font();	//constrcutor - default
	Font(LPCSTR fontFileName, int fontSize); // constructor 
	~Font(); //destructor
	FTFont* getFont();//getter for font obj
	//printing text
	void printText(LPCSTR text, FTPoint textPos);
	void printText(LPCSTR text, FTPoint textPos, colour3f textColour);

};
#endif