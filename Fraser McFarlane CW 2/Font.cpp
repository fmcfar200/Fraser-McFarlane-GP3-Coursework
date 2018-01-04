#pragma warning ( disable : 4996 )
#include "Font.h"


Font::Font() //defualt construct
{
	theFont = NULL;
}


Font::Font(LPCSTR fontFileName, int fontSize)	//contructor override
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}


Font::~Font()	//destructor
{
	delete theFont;
}


FTFont* Font::getFont() //get font
{
	return theFont;
}

//render text using font
void Font::printText(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glTranslatef(textPos.X(), textPos.Y(), 0 );
	// glRotatef(180,1, 0, 0); // Will work too
	glScalef(1, -1, 1);
	glColor3f(0.0f, 255.0f, 0.0f);
	theFont->Render(text);

	glPopMatrix();
}

void Font::printText(LPCSTR text, FTPoint textPos, colour3f textColour)
{
	glPushMatrix();

	glTranslatef(textPos.X(), textPos.Y(), 0);
	glScalef(1, -1, 1);
	glColor3f(textColour.r, textColour.g, textColour.b);
	theFont->Render(text);

	glPopMatrix();
}
