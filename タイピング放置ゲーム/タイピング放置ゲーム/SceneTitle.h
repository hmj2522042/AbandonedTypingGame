#pragma once
#include "SceneBase.h"
class SceneSetting;

class SceneTitle : public SceneBase
{
private:
	SceneSetting* m_sceneSetting;

public:
	SceneTitle() {}

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};
