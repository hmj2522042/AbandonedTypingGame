#pragma once
#include "Computer.h"
#include "Status.h"
#include "Keyboard.h"
#include "Timer.h"

class AutoComputer : public Computer
{
private:
	Timer m_timer;
	char m_answerKey;	// 正解のキー

public:
	AutoComputer(const char* textureName, const Vector2& position);

	void AutoTyping();	// 自動タイピング

	virtual RomajiTable::Status RomajiChecker() override;
	virtual void TypingCheck() override;	// タイプの正誤判定
	void SearchAnswerKey();			// 正解のキーを探す

	void UpdateNewTask();
	virtual void Draw() override;
	virtual void Update() override;
};