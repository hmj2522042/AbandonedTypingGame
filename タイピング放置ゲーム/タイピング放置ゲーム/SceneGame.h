#pragma once
#include "SceneBase.h"
#include "RomajiTable.h"
#include "EnhanceButton.h"

class ManualComputer;
class AutoComputer;
class SceneSetting;

class SceneGame : public SceneBase
{
private:
	SceneSetting* m_sceneSetting;
	ManualComputer* m_manualComputer;
	AutoComputer* m_autoComputer;
	EnhanceButton* m_enhanceButton[static_cast<int>(Status::EnhanceType::Length)];

	RomajiTable m_romajiTable;

	int m_bgm;
	int m_piconSE;

public:
	SceneGame();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};
