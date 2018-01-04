#pragma once

#include "Constants.h"

class TextureManager
{
private:
	GLuint m_texture;	//texture object
	//data for image genration
	int width, height, numComponents;
	unsigned char* imageData;

public:
	//default constructor, constructor w/filename and destructor
	TextureManager();
	TextureManager(const std::string& fileName);
	~TextureManager();

	//binding, loading and generating texture data
	void BindTexture(unsigned int unit);
	void LoadTextureData(const string& fileName);
	void GenerateTexture();

};

