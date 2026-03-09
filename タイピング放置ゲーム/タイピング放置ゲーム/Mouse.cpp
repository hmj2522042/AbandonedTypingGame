#include "Mouse.h"
#include "DxLib.h"

Vector2 Mouse::m_point;
Vector2 Mouse::m_prevPoint;
int Mouse::m_wheel = 0;
int Mouse::m_button = 0;
int Mouse::m_prevButton = 0;

void Mouse::Update()
{
	// 前フレームのマウスボタン入力状態を保存
	m_prevButton = m_button;

	// 現在のマウスボタン入力状態を取得
	m_button = GetMouseInput();

	// 前フレームのマウス位置を保存
	m_prevPoint = m_point;

	// 現在のマウス位置を取得
	int x = 0;
	int y = 0;
	GetMousePoint(&x, &y);
	m_point = Vector2(x, y);

	// マウスホイールを取得
	m_wheel = GetMouseWheelRotVol();
}
