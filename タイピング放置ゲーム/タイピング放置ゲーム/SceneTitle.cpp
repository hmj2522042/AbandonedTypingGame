#include "SceneTitle.h"
#include "Keyboard.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneSetting.h"
#include "DxLib.h"

void SceneTitle::Initialize()
{
	m_sceneSetting = new SceneSetting();
	m_sceneSetting->Initialize();
}

void SceneTitle::Finalize()
{
	if (m_sceneSetting)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneSetting);
		m_sceneSetting->Finalize();
		delete m_sceneSetting;
		m_sceneSetting = nullptr;
	}
}

void SceneTitle::Update()
{
	// SceneBaseの更新
	SceneBase::Update();

	if (Keyboard::IsDown(KEY_INPUT_G))
	{
		SceneManager::GetInstance()->LoadScene(new SceneGame());
	}

	if (Keyboard::IsDown(KEY_INPUT_S))
	{
		SceneManager::GetInstance()->PushScene(new SceneSetting());
	}
}

void SceneTitle::Draw()
{
	// SceneBaseの描画
	SceneBase::Draw();

	DrawFormatString(0, 0, 0xffffff, "SceneTitle"); // 引数の色で文字列を表示
}
