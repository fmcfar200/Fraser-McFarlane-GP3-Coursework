#ifndef _ModelLoader_H
#define _ModelLoader_H

#include "GameConstants.h"

class ModelLoader
{
public:
	ModelLoader();

	void loadModel(const char* mdlFilename);
	void loadModel(const char* mdlFilename, GLuint textureID);
	void loadModel(const char* mdlFilename, Texture mdlTexture);
	void renderMdl(glm::vec3 mdlPosition, float mdlRotationAngle, glm::vec3 mdlScale);
	mdlDimensions getModelDimensions();

	~ModelLoader();
private:
	// Set the position of the model in world space, and set the rotation.
	GLMmodel* m_model;
	GLuint m_TextureID;
	float m_TextWidth;
	float m_TextHeight;

	//GLuint initTexture(char* txtFilename);

};
#endif