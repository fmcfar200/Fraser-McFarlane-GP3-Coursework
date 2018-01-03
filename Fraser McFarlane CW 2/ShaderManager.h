#pragma once

#include "Constants.h"
#include "transform.h"
#include "Camera.h"


class ShaderManager
{
private:
	static const int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,
		CAMDIR_UNIF,
		NUM_UNIFORMS
	};
	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	static string LoadShader(const string& fileName);
	static GLuint CreateShader(const string& text, GLenum shaderType);

public:
	ShaderManager();
	ShaderManager(const string& fileName);
	~ShaderManager();


	void BindShader();
	void Update(const Transform& transform, const Camera& camera);


};

