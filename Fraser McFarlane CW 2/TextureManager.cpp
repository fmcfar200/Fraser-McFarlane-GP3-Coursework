#include "TextureManager.h"
#include "stb_image.h"
#include "Constants.h"

TextureManager::TextureManager() //default 
{

}

TextureManager::TextureManager(const std::string& fileName)
{
	
	LoadTextureData(fileName);
	GenerateTexture();
	//Deletes image data
	stbi_image_free(imageData);
}

void TextureManager::LoadTextureData(const string& fileName)
{
	
	//Loads texture data
	imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed: " << fileName << std::endl;
	}
}

void TextureManager::GenerateTexture()
{
	//generates textures and bind it to the buffer object
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glGenerateMipmap(GL_TEXTURE_2D);

	//sets wrapping parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Sends texture to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &m_texture); //detructor deletes texture
}

void TextureManager::BindTexture(unsigned int unit)
{
	//checks if the unit is within range
	assert(unit >= 0 && unit <= 31);

	//Sets texture unit and binds the texture
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
