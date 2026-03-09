#include "Actor2D.h"
#include "DxLib.h"

Actor2D::Actor2D(const char* textureName,
	const Vector2& position)
{
	m_transform.position = position;
	m_img = LoadGraph(textureName);
}

void Actor2D::Draw()
{
	DrawGraph(m_transform.position.x, m_transform.position.y, m_img, TRUE);
}

void Actor2D::Update()
{

}