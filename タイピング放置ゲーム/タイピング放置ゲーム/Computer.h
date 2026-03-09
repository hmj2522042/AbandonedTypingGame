#pragma once
#include "Actor2D.h"
#include "RomajiTable.h"
#include "Task.h"
#include <string>

class Computer : public Actor2D
{
protected:
	Task m_task; // 後々タスク構造体のメンバーにする
	size_t m_taskTextIndex; // 現在のタスクテキストの何バイト目を処理しているか
	size_t m_target_byte; // i番目からchar_lenバイト数分を読んでchに代入

	std::string m_input_buffer;		// １文字区切りで見たときの、これまでの入力
	char m_preInput;	// 直近の入力キー

public:
	Computer(const char* textureName, const Vector2& position);

	RomajiTable::Status RomajiChecker();
	void TypingCheck();	// タイプの正誤判定

	virtual void Update() override;
	virtual void Draw() override;
};