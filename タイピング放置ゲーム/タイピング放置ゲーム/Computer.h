#pragma once
#include "Actor2D.h"
#include "RomajiTable.h"
#include "Task.h"
#include <string>

class Computer : public Actor2D
{
private:
	int m_completeSE;
public:
	static constexpr int MarginWidth = 300;
protected:
	Task m_task; // 後々タスク構造体のメンバーにする
	size_t m_taskTextIndex; // 現在のタスクテキストの何バイト目を処理しているか
	size_t m_romajiTextIndex; // 現在のタスクテキストの何バイト目を処理しているか
	//size_t m_targetIndex;	// 現在ターゲットにしている文字の何文字目か tya →　tyまで打ってるなら targetIndex = 2;
	size_t m_target_byte; // i番目からchar_lenバイト数分を読んでchに代入

	std::string m_input_buffer;		// １文字区切りで見たときの、これまでの入力
	char m_preInput;	// 直近の入力キー


public:
	Computer(const char* textureName, const Vector2& position);

	virtual RomajiTable::Status RomajiChecker() = 0;
	virtual void TypingCheck() = 0;	// タイプの正誤判定

	void UpdateNewTask();

	virtual void Update() override;
	virtual void Draw() override;
};