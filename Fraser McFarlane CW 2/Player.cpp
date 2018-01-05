#include "Player.h"


Player::Player()
{
}

Player::Player(const vec3& pos, const string& textureFilename, const string& modelFilename)
{
	m_transform.SetScale(vec3(1, 1, 1));
	m_model = new ModelManager(modelFilename);
	m_texture = new TextureManager(textureFilename);
}


Player::~Player()
{
}

void Player::Update()
{

}

void Player::Render()
{
	m_texture->BindTexture(0);
	m_model->DrawMesh();
}

vec3 Player::GetPos()
{
	return m_transform.GetPos();
}

