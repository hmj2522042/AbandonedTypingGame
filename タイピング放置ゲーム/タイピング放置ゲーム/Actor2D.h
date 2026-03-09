#pragma once
#include "Transform2D.h"

class Actor2D
{
protected:
	Transform2D m_transform;	// p¨î•ñ
	int m_img;			// 2D‰æ‘œ

public:
	Actor2D(const char* textureName,
		const Vector2& position);

	virtual void Draw();
	virtual void Update();
};