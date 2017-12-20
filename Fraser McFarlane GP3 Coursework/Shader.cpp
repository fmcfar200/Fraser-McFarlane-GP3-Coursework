#include "Shader.h"


Shader::Shader(const string& filename)
{
	//creates shader program and creates shaders
	shaderProgram = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

	//attaches shaders to the shader program
	for (int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glAttachShader(shaderProgram, shaders[i]);
	}

	//binds attributes to shader
	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "textureCoord");
	glBindAttribLocation(shaderProgram, 2, "normal");

	glLinkProgram(shaderProgram); //creates executables that will run on the gpu shader
	CheckErrors(shaderProgram, GL_LINK_STATUS, true, "Error: Shader shaderProg linking failed"); //checks for errors

	glValidateProgram(shaderProgram); //checks entire program is valid
	CheckErrors(shaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program is not valid"); //check for erros

	//uniform locations are set
	uniforms[TRANSFORM_UNI] = glGetUniformLocation(shaderProgram, "trans");
	uniforms[DIRECTION_UNI] = glGetUniformLocation(shaderProgram, "camDirection");
}


Shader::~Shader()
{
	//detaches and deletes shaders
	for (int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glDetachShader(shaderProgram, shaders[i]); //detache shader from prog
		glDeleteShader(shaders[i]);


	}
	//deletes program
	glDeleteProgram(shaderProgram);
}

void Shader::AttachShader()
{
	glUseProgram(shaderProgram);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	//file is declared and opened
	std::ifstream file;
	file.open((fileName).c_str());

	//strings for output and lines
	std::string output;
	std::string line;

	if (file.is_open()) //if file is open
	{
		while (file.good()) //while file is able to be parsed
		{
			getline(file, line); //gets the line data
			output.append(line + "\n"); //appends on output value
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl; //prompt
	}

	return output; //returns line output 
}

void Shader::CheckErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0; // success int
	GLchar error[1024] = { 0 }; //error array

	if (isProgram) //if it is a program
		glGetProgramiv(shader, flag, &success); //returns program parameter flag
	else
		glGetShaderiv(shader, flag, &success); //return shader parameter flag

	if (success == GL_FALSE) //if not success
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error); //gets program logs
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error); //gets shader logs

		std::cerr << errorMessage << ": '" << error << "'" << std::endl; //promps message
	}
}

GLuint Shader::CreateShader(const std::string & text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckErrors(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

void Shader::update(const Transform & trans, const Camera & camera)
{
	glm::mat4 modelMat = camera.GetViewProjectionMatrix() * trans.GetModel(); //model vew projection matrix is calculated
	glUniformMatrix4fv(uniforms[TRANSFORM_UNI], 1, GLU_FALSE, &modelMat[0][0]);		//model mat uniform is linked
	glUniform3f(uniforms[DIRECTION_UNI], camera.forwardV.x, camera.forwardV.y, camera.forwardV.z); //camera direction uniform is linked
}