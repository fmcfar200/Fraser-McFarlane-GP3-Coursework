#pragma once
#include "Constants.h"
#include "Transform.h"
#include "ModelManager.h"
#include "TextureManager.h"

class Player
{
private:
	ModelManager* m_model;
	TextureManager* m_texture;
	Transform m_transform = vec3(-50,0,-350);

	
public:
	Player();
	Player(const vec3& pos, const string& textureFilename, const string& modelFilename);
	~Player();

	void Update();
	void Render();

	inline vec3 GetPos();

	Transform getTrans()
	{
		return m_transform;
	}

	
	
};

