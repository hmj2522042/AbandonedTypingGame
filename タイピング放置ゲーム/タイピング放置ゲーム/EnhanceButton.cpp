#include "EnhanceButton.h"
#include "Mouse.h"

EnhanceButton::EnhanceButton(const Vector2& position, Status::EnhanceType type, const char* text):
	m_enhanceType(type),
	m_text(text)
{
	m_transform.position.x = position.x;
	m_transform.position.y = position.y;
}

void EnhanceButton::Click(Status::EnhanceType type)
{
	Status::GetInstance()->LvUp(type);
}

void EnhanceButton::Update()
{
	Button::Update();
	if (Mouse::IsDown(MOUSE_INPUT_LEFT) && m_isClickable)
	{ 
		Click(m_enhanceType); 
	}
}

void EnhanceButton::Draw()
{
	Button::Draw();
	SetFontSize(16);
	if (Status::GetInstance()->GetLv(m_enhanceType) < Status::GetInstance()->GetMaxLv(m_enhanceType))
	{
		DrawFormatString(m_transform.position.x - 220, m_transform.position.y + 10, GetColor(0, 0, 0), "%s(%dトークン)",m_text, Status::GetInstance()->GetEnhanceCost(m_enhanceType)); // 引数の色で文字列を表示
	}
	else
	{
		DrawFormatString(m_transform.position.x - 220, m_transform.position.y + 10, GetColor(0, 0, 0), "%s(レベルMax)",m_text); // 引数の色で文字列を表示
	}
	DrawFormatString(m_transform.position.x - 220, m_transform.position.y + 30, GetColor(0, 0, 0), "レベル%d / %d", Status::GetInstance()->GetLv(m_enhanceType), Status::GetInstance()->GetMaxLv(m_enhanceType)); // 引数の色で文字列を表示
	SetFontSize(16);
	//if (Mouse::IsDown(MOUSE_INPUT_LEFT)) { Click(m_enhanceType); }
}
