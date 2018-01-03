#pragma once

#include "Constants.h"

class TextureManager
{
public:
	TextureManager();
	TextureManager(const std::string& fileName);
	
	void BindTexture(unsigned int unit);

	~TextureManager();

private:
	GLuint m_texture;
};

