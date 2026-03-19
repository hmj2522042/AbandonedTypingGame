#pragma once
#include "Computer.h"

class ManualComputer : public Computer
{
private:
	int m_typingSE;
public:
	ManualComputer(const char* textureName, const Vector2& position);
	void CheckInputKey();	// どのキーをタイプしたかどうか判定

	virtual RomajiTable::Status RomajiChecker() override;
	virtual void TypingCheck() override;	// タイプの正誤判定

	void UpdateNewTask();
	virtual void Draw() override;
	virtual void Update() override;
};