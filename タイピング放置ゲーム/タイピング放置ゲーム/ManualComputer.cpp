#include "ManualComputer.h"
#include "Screen.h"
#include "RomajiTable.h"
#include "Keyboard.h"
#include <string>

ManualComputer::ManualComputer(const char* textureName, const Vector2& position) :
	Computer(textureName, position)
{
	m_task.SetMainText("けっきよくたのし");
	m_task.SetYomiganaText("けっきよくたのし");
	m_preInput = NULL;
}

void ManualComputer::Draw()
{
	Computer::Draw();
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
		if (Keyboard::IsDown(KEY_INPUT_I)) { 
			m_preInput = 'i'; return; 
		}
		if (Keyboard::IsDown(KEY_INPUT_J)) { m_preInput = 'j'; return; }
		if (Keyboard::IsDown(KEY_INPUT_K)) { m_preInput = 'k'; return; }
		if (Keyboard::IsDown(KEY_INPUT_L)) { m_preInput = 'l'; return; }
		if (Keyboard::IsDown(KEY_INPUT_M)) { m_preInput = 'm'; return; }
		if (Keyboard::IsDown(KEY_INPUT_N)) { m_preInput = 'n'; return; }
		if (Keyboard::IsDown(KEY_INPUT_O)) { m_preInput = 'o'; return; }
		if (Keyboard::IsDown(KEY_INPUT_P)) { m_preInput = 'p'; return; }
		if (Keyboard::IsDown(KEY_INPUT_Q)) { m_preInput = 'q'; return; }
		if (Keyboard::IsDown(KEY_INPUT_R)) {
			
			m_preInput = 'r'; return; 
		
		}
		if (Keyboard::IsDown(KEY_INPUT_S)) { 
			m_preInput = 's'; return;
		}
		if (Keyboard::IsDown(KEY_INPUT_T)) { m_preInput = 't'; return; }
		if (Keyboard::IsDown(KEY_INPUT_U)) { 
			m_preInput = 'u'; return; 
		}
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