///TODO shu syu jyo zyo などの、三文字入力で拗音を表すときに、str out of rangeえらー
///TODO ”っ”促音も上手く行かない


#include "ManualComputer.h"
#include "Screen.h"
#include "RomajiTable.h"
#include "Keyboard.h"
#include <string>

ManualComputer::ManualComputer(const char* textureName, const Vector2& position) :
	Computer(textureName, position)
{
	m_task.SetJapaneseText("”＃＄％＆’（）けっきょく?,んんHんきello！おんなの、ひと?");
	m_preInput = NULL;
}

void ManualComputer::Draw()
{
	Computer::Draw();

	SetFontSize(40);	// フォントサイズ変更

	int drawWidth = GetDrawStringWidth(m_task.GetJapaneseText().c_str(), -1);	// 文字列全体の長さを取得
	int x = (Screen::Width - drawWidth) / 2;			// 中央寄せ基準の文字列の1文字目のx座標（今回はScreen::WIdthなので画面の中心）

	// 一文字ずつ表示
	for (size_t i = 0; i < m_task.GetJapaneseText().size(); )
	{
		unsigned char c = static_cast<unsigned char>(m_task.GetJapaneseText()[i]);

		// target(例：あ、じゃ、G、!)の選定
		size_t target_byte = 1;	// デフォルトでバイト数 = 1

		// SHIFT-JISの先頭バイトで2バイト文字を判定
		if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		{
			target_byte = 2;
		}

		std::string target = m_task.GetJapaneseText().substr(i, target_byte);	// i番目からchar_lenバイト数分を読んでchに代入

		if (i < m_taskTextIndex)
		{
			DrawFormatString(x, Screen::Height / 2 - GetFontSize() / 2, GetColor(0, 0, 0), target.c_str()); // 引数の色で文字列を表示
		}
		else
		{
			DrawFormatString(x, Screen::Height / 2 - GetFontSize() / 2, GetColor(255, 255, 255), target.c_str()); // 引数の色で文字列を表示
		}

		i += target_byte;
		x += GetDrawStringWidth(target.c_str(), -1);	// 今回入力した1文字の長さ分、次のX座標をずらす
	}
	SetFontSize(16);	// フォントサイズを戻す
}

void ManualComputer::Update()
{
	CheckInputKey();	// キー入力
	Computer::Update();	// 正誤判定
}

void ManualComputer::CheckInputKey()
{
	if (Keyboard::IsPress(KEY_INPUT_LSHIFT))
	{
		// Shift + 数字/記号
		if (Keyboard::IsDown(KEY_INPUT_1)) { m_preInput = '!';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_SLASH)) { m_preInput = '?';	 return; }
		if (Keyboard::IsDown(KEY_INPUT_2)) { m_preInput = '"';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_3)) { m_preInput = '#';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_4)) { m_preInput = '$';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_5)) { m_preInput = '%';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_6)) { m_preInput = '&';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_7)) { m_preInput = '\'';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_8)) { m_preInput = '(';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_9)) { m_preInput = ')';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_0)) { m_preInput = '=';		 return; }
		if (Keyboard::IsDown(KEY_INPUT_MINUS)) { m_preInput = '~';	 return; }
		if (Keyboard::IsDown(KEY_INPUT_YEN)) { m_preInput = '|';	 return; }
		if (Keyboard::IsDown(KEY_INPUT_COMMA)) { m_preInput = '<'; return; }
		if (Keyboard::IsDown(KEY_INPUT_PERIOD)) { m_preInput = '>'; return; }
	}
	else
	{
		// アルファベット
		if (Keyboard::IsDown(KEY_INPUT_A)) { m_preInput = 'a'; return; }
		if (Keyboard::IsDown(KEY_INPUT_B)) { m_preInput = 'b'; return; }
		if (Keyboard::IsDown(KEY_INPUT_C)) { m_preInput = 'c'; return; }
		if (Keyboard::IsDown(KEY_INPUT_D)) { m_preInput = 'd'; return; }
		if (Keyboard::IsDown(KEY_INPUT_E)) { m_preInput = 'e'; return; }
		if (Keyboard::IsDown(KEY_INPUT_F)) { m_preInput = 'f'; return; }
		if (Keyboard::IsDown(KEY_INPUT_G)) { m_preInput = 'g'; return; }
		if (Keyboard::IsDown(KEY_INPUT_H)) { m_preInput = 'h'; return; }
		if (Keyboard::IsDown(KEY_INPUT_I)) { m_preInput = 'i'; return; }
		if (Keyboard::IsDown(KEY_INPUT_J)) { m_preInput = 'j'; return; }
		if (Keyboard::IsDown(KEY_INPUT_K)) { m_preInput = 'k'; return; }
		if (Keyboard::IsDown(KEY_INPUT_L)) { m_preInput = 'l'; return; }
		if (Keyboard::IsDown(KEY_INPUT_M)) { m_preInput = 'm'; return; }
		if (Keyboard::IsDown(KEY_INPUT_N)) { m_preInput = 'n'; return; }
		if (Keyboard::IsDown(KEY_INPUT_O)) { m_preInput = 'o'; return; }
		if (Keyboard::IsDown(KEY_INPUT_P)) { m_preInput = 'p'; return; }
		if (Keyboard::IsDown(KEY_INPUT_Q)) { m_preInput = 'q'; return; }
		if (Keyboard::IsDown(KEY_INPUT_R)) { m_preInput = 'r'; return; }
		if (Keyboard::IsDown(KEY_INPUT_S)) { m_preInput = 's'; return; }
		if (Keyboard::IsDown(KEY_INPUT_T)) { m_preInput = 't'; return; }
		if (Keyboard::IsDown(KEY_INPUT_U)) { m_preInput = 'u'; return; }
		if (Keyboard::IsDown(KEY_INPUT_V)) { m_preInput = 'v'; return; }
		if (Keyboard::IsDown(KEY_INPUT_W)) { m_preInput = 'w'; return; }
		if (Keyboard::IsDown(KEY_INPUT_X)) { m_preInput = 'x'; return; }
		if (Keyboard::IsDown(KEY_INPUT_Y)) { m_preInput = 'y'; return; }
		if (Keyboard::IsDown(KEY_INPUT_Z)) { m_preInput = 'z'; return; }

		// 記号・数字キー
		if (Keyboard::IsDown(KEY_INPUT_1)) { m_preInput = '1';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_2)) { m_preInput = '2';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_3)) { m_preInput = '3';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_4)) { m_preInput = '4';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_5)) { m_preInput = '5';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_6)) { m_preInput = '6';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_7)) { m_preInput = '7';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_8)) { m_preInput = '8';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_9)) { m_preInput = '9';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_0)) { m_preInput = '0';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_MINUS)) { m_preInput = '-';   return; }
		if (Keyboard::IsDown(KEY_INPUT_YEN)) { m_preInput = '\\';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_AT)) { m_preInput = '@';	   return; }
		if (Keyboard::IsDown(KEY_INPUT_SLASH)) { m_preInput = '/';   return; }
		if (Keyboard::IsDown(KEY_INPUT_COMMA)) { m_preInput = ','; return; }
		if (Keyboard::IsDown(KEY_INPUT_PERIOD)) { m_preInput = '.'; return; }
	}
}