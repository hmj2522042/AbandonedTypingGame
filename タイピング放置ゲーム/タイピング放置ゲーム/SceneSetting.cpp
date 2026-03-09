#include "SceneGame.h"
#include "Keyboard.h"
#include "SceneManager.h"
#include "SceneSetting.h"
#include "SceneTitle.h"
#include "DxLib.h"

void SceneSetting::Initialize()
{

}

void SceneSetting::Finalize()
{

}

void SceneSetting::Update()
{
	// SceneBaseの更新
	SceneBase::Update();

	if (Keyboard::IsDown(KEY_INPUT_S))
	{
		// 設定シーンを削除
		SceneManager::GetInstance()->PopScene();
	}

	if (Keyboard::IsDown(KEY_INPUT_T))
	{
		SceneManager::GetInstance()->LoadScene(new SceneTitle());
	}
}

void SceneSetting::Draw()
{
	// SceneBaseの描画
	SceneBase::Draw();

	DrawFormatString(200, 0, 0xffffff, "SceneSetting"); // 引数の色で文字列を表示
}
