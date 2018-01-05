#pragma once

#include "Constants.h"
#include "transform.h"
#include "Camera.h"


class ShaderManager
{
private:
	static const int NUM_SHADER = 2;	//number of shaders that will be used in a program

	// enum flags for setting uniform values within the shader
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	//program, shader array and uniform array
	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];

	//checking loading and creating the program
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	static string LoadShader(const string& fileName);
	static GLuint CreateShader(const string& text, GLenum shaderType);
	 //methods for setting uniforms and binding attributes to the array
	void SetUniforms();
	void AttachAttribs();

public:
	ShaderManager();	//defualt contructor
	ShaderManager(const string& fileName); //constructor that takes in the filename
	~ShaderManager(); //destructor


	void BindShader();	//binds the shader
	void Update(const Transform& transform, const Camera& camera); //update using teh transform and camera
	void Update(const Transform *transform, const Camera& camera);


};

