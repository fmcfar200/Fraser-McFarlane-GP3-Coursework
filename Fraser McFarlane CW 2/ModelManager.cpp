#include "ModelManager.h"
#include "obj_loader.h"
#include <vector>

ModelManager::ModelManager()
{

}

ModelManager::ModelManager(const std::string& fileName)
{
	//Indexed model object is defined as converted OBJ found from filename
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);	//mesh is initialised
}

ModelManager::ModelManager(VertexManager* verts, unsigned int numVerts, unsigned int* indices, unsigned int numIndices)
{
	//model is declared
	IndexedModel model;

	
	//pos, texcoord and normals are pushed onto the arrays
	for (unsigned int i = 0; i < numVerts; i++)
	{
		model.positions.push_back(*verts[i].GetPosition());
		model.texCoords.push_back(*verts[i].GetTexCoord());
		model.normals.push_back(*verts[i].GetNormal());
	}

	//indices are pushed onto array 
	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	//mesh is initialed from created model
	InitMesh(model);
}




ModelManager::~ModelManager()
{
	//Deletes the VAO 
	glDeleteVertexArrays(1, &m_VAO);
}

void ModelManager::InitMesh(const IndexedModel& model)
{
	//drawcount set to the size of the indices array =
	m_theDrawCount = model.indices.size();

	SendDataToGPU(model); // generates buffers and sends model data
	
	
}

void ModelManager::SendDataToGPU(IndexedModel model)
{
	//generates the vert array and binds to VAO object
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//creates buffers 
	glGenBuffers(N_BUFFERS, m_VAB);
	//buffer is bound for position
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[POSITION]);
	//data sent to GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	//allows opengl to access data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//data fpr texcoord are bound and sent to GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[TEX_COORD]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	//Methods are repeated for normals and indices
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(N_BUFFERS, m_VAB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VAB[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//unbinds
	glBindVertexArray(0);

}

//Takes the mesh and draws it with the GPU
void ModelManager::DrawMesh()
{
	glBindVertexArray(m_VAO);

	//Tells OpenGL how to draw the array
	glDrawElements(GL_TRIANGLES, m_theDrawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

