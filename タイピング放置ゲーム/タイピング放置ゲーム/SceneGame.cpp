#include "SceneGame.h"
#include "Keyboard.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneSetting.h"
#include "RomajiTable.h"
#include "DxLib.h"
#include "ManualComputer.h"
#include "AutoComputer.h"

void SceneGame::Initialize()
{
	m_sceneSetting = new SceneSetting();
	m_sceneSetting->Initialize();

	m_manualComputer = new ManualComputer("Resources\Images\charasss.png", Vector2());
	AddActor(m_manualComputer);
}

void SceneGame::Finalize()
{
	if (m_sceneSetting)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneSetting);
		m_sceneSetting->Finalize();
		delete m_sceneSetting;
		m_sceneSetting = nullptr;
	}
}

void SceneGame::Update()
{
	// SceneBase‚ÌXV
	SceneBase::Update();

	if (Keyboard::IsDown(KEY_INPUT_F1))
	{
		SceneManager::GetInstance()->PushScene(new SceneSetting());
	}
}

void SceneGame::Draw()
{
	// SceneBase‚Ì•`‰æ
	SceneBase::Draw();
}