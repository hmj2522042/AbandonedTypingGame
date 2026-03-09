#pragma once
#include "SceneBase.h"
#include "RomajiTable.h"

class ManualComputer;
class AutoComputer;
class SceneSetting;

class SceneGame : public SceneBase
{
private:
	SceneSetting* m_sceneSetting;
	ManualComputer* m_manualComputer;
	AutoComputer* m_autoComputer;

	RomajiTable m_romajiTable;
public:
	SceneGame() {}

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};
