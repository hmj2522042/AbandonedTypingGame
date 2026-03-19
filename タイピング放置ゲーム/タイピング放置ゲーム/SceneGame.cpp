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

SceneGame::SceneGame():
	m_sceneSetting(nullptr),
	m_autoComputer(nullptr),
	m_manualComputer(nullptr)
{
}

void SceneGame::Initialize()
{
	m_sceneSetting = new SceneSetting();
	m_sceneSetting->Initialize();

	// コンピューター
	m_manualComputer = new ManualComputer("", Vector2());
	AddActor(m_manualComputer);	
	m_autoComputer = new AutoComputer("", Vector2());
	AddActor(m_autoComputer);

	for (int i = 0; i < static_cast<int>(Status::EnhanceType::Length); i++)
	{
		// 強化ボタン
		m_enhanceButton[i] = new EnhanceButton(Vector2(Button::BasePositionX, Button::BasePositionY + Button::PositionMarginY * i), static_cast<Status::EnhanceType>(i),Status::EnhanceText[i]);
		AddActor(m_enhanceButton[i]);
	}

	m_bgm = LoadSoundMem("Resources/Sound/bgm.mp3");
	m_piconSE = LoadSoundMem("Resources/Sound/picon.mp3");

	ChangeVolumeSoundMem(90, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
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
	// SceneBaseの更新
	SceneBase::Update();

	if (Keyboard::IsDown(KEY_INPUT_F1))
	{
		SceneManager::GetInstance()->PushScene(new SceneSetting());
	}
}

void SceneGame::Draw()
{
	// SceneBaseの描画
	SceneBase::Draw();

	DrawFormatString(0, 30, GetColor(0, 0, 0), "トークン: %d", Status::GetInstance()->GetToken()); // 引数の色で文字列を表示
}