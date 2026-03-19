#include "ManualComputer.h"
#include "Screen.h"
#include "RomajiTable.h"
#include "Keyboard.h"
#include "Status.h"
#include <string>

ManualComputer::ManualComputer(const char* textureName, const Vector2& position) :
	Computer(textureName, position)
{
	m_task.SetMainText("はつ");
	m_task.SetYomiganaText("はつ");
	m_task.SetMainYPos(180);
	m_task.SetRomajiYPos(m_task.GetMainPosition().y + Task::MainFontSize);
	m_preInput = NULL;


	m_typingSE = LoadSoundMem("Resources/Sound/typing.mp3");
	ChangeVolumeSoundMem(120, m_typingSE);
}

void ManualComputer::TypingCheck()
{
	unsigned char c = static_cast<unsigned char>(m_task.GetYomiganaText()[m_taskTextIndex]);

	// target(例：あ、じゃ、G、!)の選定
	m_target_byte = 1;	// デフォルトでバイト数 = 1

	// SHIFT-JISの先頭バイトで2バイト文字を判定
	if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
	{
		m_target_byte = 2;

		// 後ろに二文字以上あるなら、二文字目(拗音、促音、發音)の判定
		if (m_taskTextIndex + m_target_byte + 2 <= m_task.GetYomiganaText().size())
		{
			bool secondCharSearch = false;

			// 2文字目が拗音「ゃゅょ」
			if (m_task.GetYomiganaText().substr(m_taskTextIndex + m_target_byte, 2) == "ゃ" ||
				m_task.GetYomiganaText().substr(m_taskTextIndex + m_target_byte, 2) == "ゅ" ||
				m_task.GetYomiganaText().substr(m_taskTextIndex + m_target_byte, 2) == "ぃ" ||
				m_task.GetYomiganaText().substr(m_taskTextIndex + m_target_byte, 2) == "ぇ" ||
				m_task.GetYomiganaText().substr(m_taskTextIndex + m_target_byte, 2) == "ょ")
			{
				secondCharSearch = true;
			}

			// 一文字目が促音「っ」
			if (m_task.GetYomiganaText().substr(m_taskTextIndex, 2) == "っ")
			{
				secondCharSearch = true;
			}

			// 一文字目が發音「ん」
			if (m_task.GetYomiganaText().substr(m_taskTextIndex, 2) == "ん")
			{
				secondCharSearch = true;
			}

			if (secondCharSearch)
			{
				m_target_byte += 2;
			}
		}
	}

	// タイプした後のチェック
	RomajiTable::Status checkStatus = RomajiChecker();

	// 入力したキーは正しいが、まだコンプリートじゃない
	if (checkStatus == RomajiTable::Status::CorrectKey)
	{
		m_input_buffer += m_preInput;
		m_romajiTextIndex++;
		m_preInput = NULL;

		PlaySoundMem(m_typingSE, DX_PLAYTYPE_BACK);
	}
	// 入力したキーが正しいかつtargetをコンプリートした
	else if (checkStatus == RomajiTable::Status::Complete)
	{
		m_task.AddChar(m_preInput, m_romajiTextIndex);
		m_input_buffer.clear();
		m_taskTextIndex += m_target_byte;	// 総バイト数を加算し、次のtargetを更新
		m_romajiTextIndex++;
		m_preInput = NULL;

		PlaySoundMem(m_typingSE, DX_PLAYTYPE_BACK);
		// タスクを完遂したら
		if (m_taskTextIndex == m_task.GetYomiganaText().size())
		{
			Status::GetInstance()->GetReward(static_cast<int>(m_task.GetYomiganaText().size()));
			ManualComputer::UpdateNewTask();
		}
	}
	// target一文字目が"ん"だった時に、"n"一つだけで次の文字に移行成功した
	else if (checkStatus == RomajiTable::Status::NOnly_Complete)
	{
		m_input_buffer.clear();
		m_input_buffer += m_preInput; // 今回の入力"例：j"を次の文字のinput_bufferに追加
		m_taskTextIndex += m_target_byte;
		m_romajiTextIndex++;
		m_preInput = NULL;

		PlaySoundMem(m_typingSE, DX_PLAYTYPE_BACK);
		// タスクを完遂したら
		if (m_taskTextIndex == m_task.GetYomiganaText().size())
		{
			Status::GetInstance()->GetReward(static_cast<int>(m_task.GetYomiganaText().size()));
			ManualComputer::UpdateNewTask();
		}
	}
	else if (checkStatus == RomajiTable::Status::Miss)
	{
		// ミスタイプ処理
		m_preInput = NULL;
	}

	if (m_taskTextIndex > m_task.GetYomiganaText().size())
	{
		m_taskTextIndex = m_task.GetYomiganaText().size();
	}
}

RomajiTable::Status ManualComputer::RomajiChecker()
{
	if (m_preInput == '\0') return RomajiTable::Status::Miss;	// 入力がないなら終了

	std::string target_first = "";
	std::string target_second = "";
	const auto& map = RomajiTable::GetInstance()->GetRomajiMap();
	auto it = map.find(m_task.GetYomiganaText().substr(m_taskTextIndex, m_target_byte));

	std::string input_buffer = m_input_buffer;
	input_buffer += m_preInput;	// バッファーに直近のキー入力を追加

	////////////////////////// あるふぁべっと　英語 ///////////////////////////////

	if (m_target_byte == 1)
	{
		// romajiMapに存在するパターンなら
		// target全て読み込んで（拗音ありなら4バイト分）
		it = map.find(m_task.GetYomiganaText().substr(m_taskTextIndex, m_target_byte));

		if (it != map.end())
		{
			for (std::string pattern : it->second)
			{
				// ペアが完全一致した
				if (pattern == input_buffer)
				{
					return RomajiTable::Status::Complete;
				}
				// まだペアが完成はしていないが、直近入力した一文字（キー）は正しい
				else if (pattern[input_buffer.length() - 1] == m_preInput)
				{
					return RomajiTable::Status::CorrectKey;
				}
			}
		}
	}

	if (m_target_byte >= 2)
	{
		target_first = m_task.GetYomiganaText().substr(m_taskTextIndex, 2);	// 一文字目を得る、先頭から2バイト読み込む
	}
	if (m_target_byte >= 4)
	{
		target_second = m_task.GetYomiganaText().substr(m_taskTextIndex + 2, 2);	// 二文字目を得る、3バイト目から2バイト読み込む
	}

	// 發音　促音はひらがな二文字読み込めるなら判定を行う
	if (m_target_byte >= 4)
	{
		////////////////////////// 發音 "ん" ///////////////////////////////
		if (target_first == "ん" && m_input_buffer == "n")
		{
			m_target_byte = 2; // 本来は4バイト分確保しているが、"ん"だけ入力完了なので2バイトに更新する
			bool nOnly_flag = true;	// "n"入力のみで"ん"出力判定にするかどうか

			// 二文字目がignoreに含まれていたら nOnly_flag = false
			static const std::vector<std::string> ignore_N = {
			"な", "に", "ぬ", "ね", "の",
			"ん",
			"あ", "い", "う", "え", "お"
			};

			// 二文字目がignoreに含まれるなら false つまり"nn"入力しないと"ん"にならない
			for (const std::string t : ignore_N) {
				if (target_second.find(t) != std::string::npos)
				{
					nOnly_flag = false;
					break;
				}
			}

			// "n"だけでもいい場合の処理 "n"まで入力されていたら
			if (nOnly_flag)
			{
				it = map.find(target_second);

				// romajiMapに存在するパターンなら
				if (it != map.end())
				{
					// 二文字目のローマ字の一文字目"例：j"の判定
					for (std::string pattern : it->second)
					{
						// 一致したので "ん"は'n'のみで出力完了し、次の文字たちへ移行する
						if (pattern[0] == m_preInput)
						{
							return RomajiTable::Status::NOnly_Complete;
						}
					}
				}
			}
		}

		////////////////////////// 促音 "っ"///////////////////////////////

		if (target_first == "っ")
		{
			bool sokuon_flag = true;	// "例：tte,jja"入力で"っ"出力判定にするかどうか

			it = map.find(target_second);

			// 二文字目がignoreに含まれていたら nOnly_flag = false
			static const std::vector<std::string> ignore_sokuon = {
			"あ", "い", "う", "え", "お", "ん", "っ"
			};

			// 二文字目がignoreに含まれるなら false つまり"ltsu,ltu"入力しないと"っ"にならない
			for (const std::string t : ignore_sokuon) {
				if (target_second.find(t) != std::string::npos)
				{
					sokuon_flag = false;
					break;
				}
			}

			if (sokuon_flag)
			{
				// 2文字取得可能
				it = map.find(target_second);

				// romajiMapに存在するパターンなら
				if (it != map.end())
				{
					// 二文字目のローマ字の一文字目"例：j"の判定
					for (std::string pattern : it->second)
					{
						std::string sokuon = pattern[0] + pattern;	// 例：ja → jja 

						// 一致したので "っ"は"例：jja"で出力完了し、次の文字たちへ移行する
						if (sokuon == input_buffer)
						{
							return RomajiTable::Status::Complete;
						}
						// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
						// m_input_bufferと一致しているか
						else if (sokuon[input_buffer.length() - 1] == m_preInput &&
							sokuon.rfind(input_buffer, 0) == 0)
						{
							return RomajiTable::Status::CorrectKey;
						}
					}
				}

				// 3文字取得可能なら 拗音("ゃ,ゅ,ょ") までしらべる
				if (m_task.GetYomiganaText().size() >= m_taskTextIndex + m_target_byte + 2)
				{
					std::string target_third = m_task.GetYomiganaText().substr(m_taskTextIndex + 4, 2);	// 二文字目を得る、3バイト目から2バイト読み込む

					// 3文字目が拗音「ゃゅょ」
					if (target_third == "ゃ" || target_third == "ゅ" || target_third == "ょ" || target_third == "ぃ" || target_third == "ぇ")
					{
						m_target_byte += 2;
						it = map.find(target_second + target_third);

						// romajiMapに存在するパターンなら
						if (it != map.end())
						{
							// 二文字目のローマ字の一文字目"例：j"の判定
							for (std::string pattern : it->second)
							{
								std::string sokuon = pattern[0] + pattern;	// 例：ja → jja 

								// 一致したので "っ"は"例：jja"で出力完了し、次の文字たちへ移行する
								if (sokuon == input_buffer)
								{
									return RomajiTable::Status::Complete;
								}
								// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
								// m_input_bufferと一致しているか
								else if (sokuon[input_buffer.length() - 1] == m_preInput &&
									sokuon.rfind(input_buffer, 0) == 0)
								{
									return RomajiTable::Status::CorrectKey;
								}
							}
						}
					}
				}
			}
		}
	}

	////////////////////////// 拗音 ("ゃ,ゅ,ょ") ///////////////////////////////

	// target全て読み込んで（拗音ありなら4バイト分）
	it = map.find(target_first + target_second);

	// romajiMapに存在するパターンなら
	if (it != map.end())
	{
		for (std::string pattern : it->second)
		{
			// ペアが完全一致した
			if (pattern == input_buffer)
			{
				return RomajiTable::Status::Complete;
			}
			// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
			// m_input_bufferと一致しているか
			else if (pattern[input_buffer.length() - 1] == m_preInput &&
				pattern.rfind(input_buffer, 0) == 0)
			{
				return RomajiTable::Status::CorrectKey;
			}
		}
	}

	/////////////////////////// 一文字ずつ通常入力 例：じょ→　”じ”と”ょ”に分けて入力とか ///////////////////////////////

	// 一文字ずつ通常入力 "じゃ"→"じ"だけ入力
	if (m_target_byte >= 2)
	{
		m_target_byte = 2;
		it = map.find(target_first);

		// romajiMapに存在するパターンなら
		if (it != map.end())
		{
			for (std::string pattern : it->second)
			{
				// ペアが完全一致した
				if (pattern == input_buffer)
				{
					return RomajiTable::Status::Complete;
				}
				// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
				// m_input_bufferと一致しているか
				else if (pattern[input_buffer.length() - 1] == m_preInput &&
					pattern.rfind(input_buffer, 0) == 0)
				{
					return RomajiTable::Status::CorrectKey;
				}
			}
		}
	}
	// ミスタイプ
	return RomajiTable::Status::Miss;
}

void ManualComputer::Draw()
{
	Computer::Draw();
	DrawBox(20, 100, 500, 300, GetColor(255, 100, 100), FALSE);

	DrawFormatString(30, 110, GetColor(0, 0, 0), "推定報酬: %d", 
		static_cast<int>(m_task.GetYomiganaText().size()) + static_cast<int>(Status::GetInstance()->GetLv(Status::EnhanceType::RewardRatioLv) * Status::GetInstance()->RewardRatio * static_cast<int>(m_task.GetYomiganaText().size()))); // 引数の色で文字列を表示

	SetFontSize(24);
	DrawFormatString(430, 110, GetColor(0, 0, 0), "手動"); // 引数の色で文字列を表示
	SetFontSize(16);
}

void ManualComputer::Update()
{
	CheckInputKey();	// キー入力
	Computer::Update();	// 正誤判定
	TypingCheck();	// 入力キーの正誤判定
	m_task.UpdateText(m_input_buffer, m_taskTextIndex, m_romajiTextIndex);
}

void ManualComputer::UpdateNewTask()
{
	m_task.SetNewText(Status::GetInstance()->GetLv(Status::EnhanceType::ManualTaskLv));
	Computer::UpdateNewTask();
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
		if (Keyboard::IsDown(KEY_INPUT_Y)) { 
			m_preInput = 'y'; return; 
		}
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