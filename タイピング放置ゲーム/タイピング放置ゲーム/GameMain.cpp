#include "DxLib.h"
#include "GameMain.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "SceneManager.h"
#include "Screen.h"
#include "SceneTitle.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("タイピング放置ゲーム");	// ウィンドウのタイトル
	SetGraphMode(Screen::Width, Screen::Height, 32);	// ウィンドウの大きさとカラービット数の指定
	ChangeWindowMode(TRUE);	//ウィンドウモードで起動
	if (DxLib_Init() == -1)	return -1;// ＤＸライブラリ初期化処理
	SetBackgroundColor(150, 150, 150);	// 背景色の指定
	SetDrawScreen(DX_SCREEN_BACK);	// 描画面を裏画面にする

	SceneManager::GetInstance()->LoadScene(new SceneTitle());

	GameMain game;
	game.Run();

	DxLib_End();
	return 0;
}

// 影を付けた文字列と値を表示する関数
void drawText(int x, int y, const char* txt, int val, int col, int siz)
{
	SetFontSize(siz); // フォントの大きさを指定
	DrawFormatString(x + 1, y + 1, 0x000000, txt, val); // 黒で文字列を表示
	DrawFormatString(x, y, col, txt, val); // 引数の色で文字列を表示
}

void GameMain::Run()
{
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		// ESCキーで終了
		if (Keyboard::IsDown(KEY_INPUT_ESCAPE)) break;

		// 入力デバイスの更新
		Keyboard::Update();
		Mouse::Update();

		// 時間の更新
		Time::GetInstance()->Update();

		// シーンの更新
		SceneManager::GetInstance()->Update();
		// シーンの描画
		SceneManager::GetInstance()->Draw();

		ScreenFlip();	// 裏画面の内容を表画面に反映させる
	}
}

//void GameMain::Draw()
//{
//	drawText(0, 60, "クリア条件：新年 & 32ミリ秒以内にストップ", 0, 0xffffff, 20);
//
//	//if (!m_timer.GetIsEnable())
//	//{
//	//	drawText(0, 0, "時間差：%d ミリ秒 (Rでリトライ)", m_timer.GetGapTime(), 0xffffff, 30);
//	//	if (m_timer.GetIsClear())
//	//	{
//	//		drawText(300, 280, "無事年越し", m_timer.GetGapTime(), 0xff0000, 40);
//	//	}
//	//	else if (!m_timer.GetIsClear())
//	//	{
//	//		drawText(110, 280, "年越し失敗", m_timer.GetGapTime(), 0xff0000, 40);
//	//	}
//	//	if (Keyboard::IsDown(KEY_INPUT_R)) m_timer.Retry();
//
//	//	DrawRotaGraph(300, 400, 2.0, 0, m_handImage[1], TRUE);
//	//	m_mosaicAlpha = 0.0f;
//	//}
//	//else
//	//{
//	//	if (m_timer.GetElapsedTime() > 4000)
//	//	{
//	//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_mosaicAlpha); // 半透明
//	//		DrawBox(120, 180, 520, 260, GetColor(0, 0, 0), TRUE);
//	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 戻す
//	//		if (m_mosaicAlpha < 255) m_mosaicAlpha += 2.3f;
//	//	}
//	//	DrawRotaGraph(300, 400, 2.0, 0, m_handImage[0], TRUE);
//	//}
//}