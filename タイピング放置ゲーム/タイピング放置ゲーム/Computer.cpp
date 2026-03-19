#include "Computer.h"
#include "RomajiTable.h"

Computer::Computer(const char* textureName, const Vector2& position) :
	Actor2D(textureName, position),
	m_input_buffer(""),
	m_preInput(0),
	m_target_byte(0),
	m_task(),
	m_taskTextIndex(0),
	m_romajiTextIndex(0)
{
	m_completeSE = LoadSoundMem("Resources/Sound/complete.mp3");
	ChangeVolumeSoundMem(100, m_completeSE);
}

void Computer::Draw()
{
	Actor2D::Draw();

	SetFontSize(Task::MainFontSize);	// フォントサイズ変更
	int mainWidth = GetDrawStringWidth(m_task.GetMainText().c_str(), -1);	// 文字列全体の長さを取得
	SetFontSize(Task::SubFontSize);	// フォントサイズを戻す
	int subWidth = GetDrawStringWidth(m_task.GetRomajiText().c_str(), -1);	// 文字列全体の長さを取得
	SetFontSize(16);	// フォントサイズを戻す

	m_task.SetMainXPos((Screen::Width - MarginWidth - mainWidth) / 2);			// 中央寄せ基準の文字列の1文字目のx座標（今回はScreen::WIdthなので画面の中心）
	m_task.SetRomajiXPos((Screen::Width - MarginWidth - subWidth) / 2);			// 中央寄せ基準の文字列の1文字目のx座標（今回はScreen::WIdthなので画面の中心）

	//int firstX = m_task.GetMainPosition().x;

	// メインテキスト一文字ずつ表示
	for (size_t i = 0; i < m_task.GetMainText().size(); )
	{
		unsigned char c = static_cast<unsigned char>(m_task.GetMainText()[i]);

		// target(例：あ、じゃ、G、!)の選定
		size_t target_byte = 1;	// デフォルトでバイト数 = 1

		// SHIFT-JISの先頭バイトで2バイト文字を判定
		if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		{
			target_byte = 2;
		}

		std::string target = m_task.GetMainText().substr(i, target_byte);	// i番目からchar_lenバイト数分を読んでchに代入

		SetFontSize(Task::MainFontSize);	// フォントサイズ変更
		DrawFormatString(m_task.GetMainPosition().x, m_task.GetMainPosition().y, GetColor(255, 255, 255), target.c_str()); // 引数の色で文字列を表示

		m_task.SetMainXPos(m_task.GetMainPosition().x + GetDrawStringWidth(target.c_str(), -1));	// 今回入力した1文字の長さ分、次のX座標をずらす
		i += target_byte;
		SetFontSize(16);	// フォントサイズを戻す
	}


	//m_task.SetMainXPos(firstX);

	//// よみがな一文字ずつ表示
	//for (size_t i = 0; i < m_task.GetYomiganaText().size(); )
	//{
	//	unsigned char c = static_cast<unsigned char>(m_task.GetYomiganaText()[i]);


	//	// target(例：あ、じゃ、G、!)の選定
	//	size_t target_byte = 1;	// デフォルトでバイト数 = 1

	//	// SHIFT-JISの先頭バイトで2バイト文字を判定
	//	if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
	//	{
	//		target_byte = 2;
	//	}

	//	std::string target = m_task.GetYomiganaText().substr(i, target_byte);	// i番目からchar_lenバイト数分を読んでchに代入

	//	SetFontSize(Task::YomiganaFontSize);	// フォントサイズ変更
	//	if (i < m_taskTextIndex)
	//	{
	//		DrawFormatString(m_task.GetMainPosition().x, m_task.GetMainPosition().y - Task::MainFontSize / 2, GetColor(0, 0, 0), target.c_str()); // 引数の色で文字列を表示
	//	}
	//	else
	//	{
	//		DrawFormatString(m_task.GetMainPosition().x, m_task.GetMainPosition().y - Task::MainFontSize / 2, GetColor(255, 255, 255), target.c_str()); // 引数の色で文字列を表示
	//	}

	//	m_task.SetMainXPos(m_task.GetMainPosition().x + GetDrawStringWidth(target.c_str(), -1));	// 今回入力した1文字の長さ分、次のX座標をずらす
	//	i += target_byte;
	//	SetFontSize(16);	// フォントサイズを戻す
	//}

	// ローマ字表示
	for (size_t i = 0; i < m_task.GetRomajiText().size(); i++)
	{
		std::string target = m_task.GetRomajiText().substr(i, 1);	// i番目からchar_lenバイト数分を読んでchに代入

		SetFontSize(Task::SubFontSize);	// フォントサイズ変更
		if (i < m_romajiTextIndex)
		{
			DrawFormatString(m_task.GetRomajiPosition().x, m_task.GetRomajiPosition().y, GetColor(0, 0, 0), target.c_str()); // 引数の色で文字列を表示
		}
		else
		{
			DrawFormatString(m_task.GetRomajiPosition().x, m_task.GetRomajiPosition().y, GetColor(255, 255, 255), target.c_str()); // 引数の色で文字列を表示
		}
		m_task.SetRomajiXPos(m_task.GetRomajiPosition().x + GetDrawStringWidth(target.c_str(), -1));	// 今回入力した1文字の長さ分、次のX座標をずらす
		SetFontSize(16);
	}
}

void Computer::UpdateNewTask()
{
	m_input_buffer = "";
	m_preInput = NULL;
	m_target_byte = 0;
	m_taskTextIndex = 0;
	m_romajiTextIndex = 0;
	PlaySoundMem(m_completeSE, DX_PLAYTYPE_BACK);
}

void Computer::Update()
{
	Actor2D::Update();
}