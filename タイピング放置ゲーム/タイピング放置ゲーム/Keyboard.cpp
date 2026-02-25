#include "Keyboard.h"
#include "DxLib.h"
#include <cstring>

char Keyboard::m_keyState[Keyboard::KeyStateNum] = {};
char Keyboard::m_prevKeyState[Keyboard::KeyStateNum] = {};

void Keyboard::Update()
{
	// 前フレームのキー入力状態を保存
	std::memcpy(m_prevKeyState, m_keyState, sizeof(char) * KeyStateNum);

	// 現フレームのキー入力状態を取得
	GetHitKeyStateAll(m_keyState);
}

// いずれかのキーが押されている
bool Keyboard::IsAnyPress()
{
	// 配列から1を探し出す
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}

// WASD入力を取得
Vector2 Keyboard::GetWASD()
{
	Vector2 input;
	if (IsPress(KEY_INPUT_W)) input.y = 1;
	if (IsPress(KEY_INPUT_A) || IsPress(KEY_INPUT_LEFT)) input.x = -1;
	if (IsPress(KEY_INPUT_S)) input.y = -1;
	if (IsPress(KEY_INPUT_D) || IsPress(KEY_INPUT_RIGHT)) input.x = 1;
	return input;
}
