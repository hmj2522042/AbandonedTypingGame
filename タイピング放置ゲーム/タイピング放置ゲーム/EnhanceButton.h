#pragma once
#include "Button.h"
#include "Status.h"
#include <string>

class EnhanceButton : public Button
{
private:
	Status::EnhanceType m_enhanceType;
	const char* m_text;

public: 
	EnhanceButton(const Vector2& position, Status::EnhanceType type,const char* text);

	void Click(Status::EnhanceType type);
	//Status::EnhanceType GetEnhanceType() { return m_enhanceType; }

	virtual void Update() override;
	virtual void Draw() override;
};