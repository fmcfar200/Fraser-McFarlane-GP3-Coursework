#pragma once

#include <glm\glm.hpp>
#include "Constants.h"
#include "obj_loader.h"

class VertexManager
{
private:
	//vertex pos , texture coord and normals
	vec3 position;
	vec2 texCoord;
	vec3 normal;

public:
	//constructor for vertex object
	VertexManager(const vec3& position, const vec2& texCoord, const  vec3& normal = vec3(0,0,0))
	{
		//Setters
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	//getters for position tex coordinates and normals
	inline vec3* GetPosition() 
	{ 
		return &position; 
	}
	inline vec2* GetTexCoord() 
	{ 
		return &texCoord; 
	}
	inline vec3* GetNormal() 
	{ 
		return &normal;
	}

};

class ModelManager
{
private:
	void InitMesh(const IndexedModel& model);

	enum //enum flags
	{
		POSITION,
		TEX_COORD,
		INDEX,
		NORMAL,
		N_BUFFERS
	};

	GLuint m_VAO;
	GLuint m_VAB[N_BUFFERS];
	unsigned int m_theDrawCount;

	void SendDataToGPU(IndexedModel model);

public:
	ModelManager(); //model default
	ModelManager(VertexManager* verts, unsigned int numVerts, unsigned int* indices, unsigned int numIndices); //contructor 
	ModelManager(const string& fileName);	//contructor w/filename
	~ModelManager(); //detructor


	void DrawMesh();	//draw



};

