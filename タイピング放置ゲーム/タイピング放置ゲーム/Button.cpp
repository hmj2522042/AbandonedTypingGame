#include "Button.h"

Button::Button():
	Actor2D("",Vector2()),
	m_isClickable(0)
{
}

void Button::Update()
{
	// マウスポインたーがボタン上にあれば
	if (Mouse::GetPoint().x >= m_transform.position.x && Mouse::GetPoint().x < m_transform.position.x + MarginX &&
		Mouse::GetPoint().y >= m_transform.position.y && Mouse::GetPoint().y < m_transform.position.y + MarginY)
	{
		m_isClickable = true;
	}
	else
	{
		m_isClickable = false;
	}

	// isPushing処理
	if (Mouse::IsPress(MOUSE_INPUT_LEFT))
	{
		m_isPushing = true;
	}
	else
	{
		m_isPushing = false;
	}
}

void Button::Draw()
{
	if (m_isClickable)
	{
		if (m_isPushing)
		{
			DrawBox(m_transform.position.x, m_transform.position.y, m_transform.position.x + MarginX, m_transform.position.y + MarginY, GetColor(255, 100, 100), TRUE);
		}
		else
		{
			DrawBox(m_transform.position.x, m_transform.position.y, m_transform.position.x + MarginX, m_transform.position.y + MarginY, GetColor(100, 100, 100), TRUE);
		}
	}
	else
	{
		DrawBox(m_transform.position.x, m_transform.position.y, m_transform.position.x + MarginX, m_transform.position.y + MarginY, GetColor(220, 220, 220), TRUE);
	}

	SetFontSize(35);
	DrawFormatString(m_transform.position.x+ 6, m_transform.position.y+6, GetColor(0, 0, 0), "UP"); // 引数の色で文字列を表示
	SetFontSize(16);
}