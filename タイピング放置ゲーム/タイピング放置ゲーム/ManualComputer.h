#pragma once
#include "Computer.h"

class ManualComputer : public Computer
{
public:
	ManualComputer(const char* textureName, const Vector2& position);
	void CheckInputKey();	// どのキーをタイプしたかどうか判定

	virtual void Draw() override;
	virtual void Update() override;
};