#pragma once
#include "Vector2.h"

// マウス
class Mouse
{
private:
	static Vector2 m_point;		// 現フレームの位置
	static Vector2 m_prevPoint;	// 前フレームの位置
	static int m_wheel;			// ホイール
	static int m_button;		// 現フレームのボタン入力状態
	static int m_prevButton;	// 前フレームのボタン入力状態

	Mouse() {}

public:
	static void Update();

	// 位置を取得
	static Vector2 GetPoint() { return m_point; }

	// 移動量を取得
	static Vector2 GetPointDelta() { return m_point - m_prevPoint; }

	// ホイールを取得
	static int GetWheel() { return m_wheel; }

	// マウスボタンが押された瞬間
	static bool IsDown(int button) { return (m_button & button) && !(m_prevButton & button); }

	// マウスボタンが押されている
	static bool IsPress(int button) { return (m_button & button); }

	// マウスボタンが離された瞬間
	static bool IsUp(int button) { return !(m_button & button) && (m_prevButton & button); }

	// いずれかのボタンが押されている
	static bool IsAnyPress() { return m_button; }
};
