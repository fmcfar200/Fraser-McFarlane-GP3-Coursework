#include "ShaderManager.h"

ShaderManager::ShaderManager()
{

}

ShaderManager::ShaderManager(const std::string& fileName)
{
	//Creates the program object
	m_program = glCreateProgram();
	//Finds and creates the shaders from filename
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	//Attaches the shaders 
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	AttachAttribs();
	SetUniforms();
}

void ShaderManager::SetUniforms()
{
	//Updates the attribs
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[LPOS_U] = glGetUniformLocation(m_program, "lightPos");
	m_uniforms[SPOTDIR_U] = glGetUniformLocation(m_program, "spotDirection");

	
	//m_uniforms[CAMDIR_UNIF] = glGetUniformLocation(m_program, "cameraDirection");s
}

void ShaderManager::AttachAttribs()
{
	//binding of attribs
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	//Check for errors in the program
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader failed to link: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader unvalidated: ");

}
ShaderManager::~ShaderManager()
{
	//Detaches the shaders
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	//Deletes the shader prog
	glDeleteProgram(m_program);
}

//Binds any shaders created to the program
void ShaderManager::BindShader()
{
	glUseProgram(m_program);
}

//updates transform, light pos and spot direction
void ShaderManager::Update(const Transform& transform, const Camera& camera, const Light& light)
{
	glm::mat4 model = camera.GetViewProjectionMatrix() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniform3f(m_uniforms[LPOS_U], light.m_Position.x, light.m_Position.y, light.m_Position.z);
	glUniform3f(m_uniforms[SPOTDIR_U], light.m_SpotDirection.x, light.m_SpotDirection.y, light.m_SpotDirection.z);


	//glUniform3f(m_uniforms[CAMDIR_UNIF], camera.GetForwardV().x, camera.GetForwardV().y, camera.GetForwardV().z);
}
void ShaderManager::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjectionMatrix() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	//glUniform3f(m_uniforms[CAMDIR_UNIF], camera.GetForwardV().x, camera.GetForwardV().y, camera.GetForwardV().z);
}

 GLuint ShaderManager::CreateShader(const std::string& text, GLenum shaderType)
{
	//Creates the shader
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error:Shader creation failed" << std::endl;
	}

	//Creates an array of strings 
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	//casts to character
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	//Sends the shader code to OpenGL and compiles it
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	//Checks for any errors in the compilation of the shader
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader could not compile");

	//return the created shader
	return shader;
}

//Loads the shader from a file
std::string ShaderManager::LoadShader(const std::string& fileName)
{
	//sets file stream and opens
	std::ifstream file;
	file.open((fileName).c_str());

	//output and line strings
	std::string output;
	std::string line;

	//if the file is open
	if (file.is_open())
	{
		//while the file readable, the current line is read
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{	//error reading shader
		std::cerr << "Unable to load the shader correctly: " << fileName << std::endl;
	}
	return output;	//returns the shader
}

//Check for errors in the shader
void ShaderManager::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	//gl success
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success); //gets program info
	}
	else
	{
		glGetShaderiv(shader, flag, &success); //gets shader info
	}

	if (success == GL_FALSE) //if not successful
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error); //gets info log for program
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error); //gets info log of shader
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl; //displays error flag
	}
}
