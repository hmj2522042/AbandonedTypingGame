#pragma once
#include "SceneBase.h"

class SceneSetting : public SceneBase
{
public:
	SceneSetting() {}

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};