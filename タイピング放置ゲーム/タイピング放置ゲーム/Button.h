#pragma once
#include "Actor2D.h"
#include "Mouse.h"

class Button : public Actor2D
{
private:
	
protected:
	bool m_isClickable;
	bool m_isPushing;

public:
	static constexpr int MarginX = 50;
	static constexpr int MarginY = 50;
	static constexpr int PositionMarginY = 80;
	static constexpr int BasePositionX = 740;
	static constexpr int BasePositionY = 100;


public:
	Button();

	virtual void Update() override;
	virtual void Draw() override;
};