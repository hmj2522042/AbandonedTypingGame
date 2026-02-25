#pragma once
#include "Vector2.h"

// キーボード
class Keyboard
{
private:
	static constexpr int KeyStateNum = 256;	// キー入力状態の要素数

	static char m_keyState[KeyStateNum];		// 現フレームのキー入力状態
	static char m_prevKeyState[KeyStateNum];	// 前フレームのキー入力状態

	Keyboard() {}

public:
	static void Update();

	// キーが押された瞬間
	static bool IsDown(int key) { return !m_prevKeyState[key] && m_keyState[key]; }

	// キーが押されている
	static bool IsPress(int key) { return m_keyState[key]; }

	// キーが離された瞬間
	static bool IsUp(int key) { return m_prevKeyState[key] && !m_keyState[key]; }

	// いずれかのキーが押されている
	static bool IsAnyPress();

	// WASD入力を取得
	static Vector2 GetWASD();
};
