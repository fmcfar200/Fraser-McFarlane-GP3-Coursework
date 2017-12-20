#include <string>
#include "GL\glew.h"
#include "GameConstants.h"
#include "Camera.h"
using namespace std;

class Shader
{

private:

	static const unsigned int NUM_OF_SHADERS = 2;

	enum
	{
		TRANSFORM_UNI,
		DIRECTION_UNI,
		NUM_OF_UNI
	};

	GLuint shaderProgram;
	GLuint shaders[NUM_OF_SHADERS];
	GLuint uniforms[NUM_OF_UNI];

public:
	Shader(const string& filename);
	~Shader();

	void AttachShader();

	string LoadShader(const string& filename);
	void CheckErrors(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	GLuint CreateShader(const string& text, unsigned int type);
	void update(const Transform& trans, const Camera& camera);


};
