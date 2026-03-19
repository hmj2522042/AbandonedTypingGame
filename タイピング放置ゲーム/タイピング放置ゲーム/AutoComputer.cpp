#include "AutoComputer.h"
#include "Screen.h"
#include "RomajiTable.h"
#include "Keyboard.h"
#include <string>

AutoComputer::AutoComputer(const char* textureName, const Vector2& position) :
	Computer(textureName, position),
	m_timer(),
	m_answerKey(NULL)
{
	m_task.SetMainText("けっきょく");
	m_task.SetYomiganaText("けっきょく");
	m_task.SetMainYPos(430);
	m_task.SetRomajiYPos(m_task.GetMainPosition().y + Task::MainFontSize);
	m_preInput = NULL;
}

void AutoComputer::TypingCheck()
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
	}
	// 入力したキーが正しいかつtargetをコンプリートした
	else if (checkStatus == RomajiTable::Status::Complete)
	{
		m_task.AddChar(m_preInput, m_romajiTextIndex);
		m_input_buffer.clear();
		m_taskTextIndex += m_target_byte;	// 総バイト数を加算し、次のtargetを更新
		m_romajiTextIndex++;
		m_preInput = NULL;

		// タスクを完遂したら
		if (m_taskTextIndex == m_task.GetYomiganaText().size())
		{
			Status::GetInstance()->GetReward(static_cast<int>(m_task.GetYomiganaText().size()));
			AutoComputer::UpdateNewTask();
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

		// タスクを完遂したら
		if (m_taskTextIndex == m_task.GetYomiganaText().size())
		{
			Status::GetInstance()->GetReward(static_cast<int>(m_task.GetYomiganaText().size()));
			AutoComputer::UpdateNewTask();
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

RomajiTable::Status AutoComputer::RomajiChecker()
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
		if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 2)
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
		}

		////////////////////////// 促音 "っ"///////////////////////////////

		if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 4)
		{
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
	}

	////////////////////////// 拗音 ("ゃ,ゅ,ょ") ///////////////////////////////

	if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 3)
	{
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

void AutoComputer::SearchAnswerKey()
{
	std::string target_first = "";
	std::string target_second = "";
	const auto& map = RomajiTable::GetInstance()->GetRomajiMap();
	auto it = map.find(m_task.GetYomiganaText().substr(m_taskTextIndex, m_target_byte));

	std::string input_buffer = m_input_buffer;

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
				m_answerKey = pattern[input_buffer.size()];
				return;
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
		if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 2)
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
							m_answerKey = pattern[0];
							return;
						}
					}
				}
			}
		}

		////////////////////////// 促音 "っ"///////////////////////////////

		if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 4)
		{
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

							// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
							// m_input_bufferと一致しているか
							if (input_buffer[0] == NULL)
							{
								m_answerKey = sokuon[input_buffer.size()];
								return;
							}
							if (sokuon.rfind(input_buffer, 0) == 0)
							{
								m_answerKey = sokuon[input_buffer.size()];
								return;
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

									// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
									// m_input_bufferと一致しているか
									if (input_buffer[0] == NULL)
									{
										m_answerKey = sokuon[input_buffer.size()];
										return;
									}
									if (sokuon.rfind(input_buffer, 0) == 0)
									{
										m_answerKey = sokuon[input_buffer.size()];
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	////////////////////////// 拗音 ("ゃ,ゅ,ょ") ///////////////////////////////

	if (Status::GetInstance()->GetLv(Status::EnhanceType::EfficientLv) >= 3)
	{
		// target全て読み込んで（拗音ありなら4バイト分）
		it = map.find(target_first + target_second);

		// romajiMapに存在するパターンなら
		if (it != map.end())
		{
			for (std::string pattern : it->second)
			{
				// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
				// m_input_bufferと一致しているか
				if (input_buffer[0] == NULL)
				{
					m_answerKey = pattern[input_buffer.size()];
					return;
				}
				if (pattern.rfind(input_buffer, 0) == 0)
				{
					m_answerKey = pattern[input_buffer.size()];
					return;
				}
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
				// まだペアが完成はしていないが、直近タイプした一文字（キー）は正しい かつ
				// m_input_bufferと一致しているか
				if (input_buffer[0] == NULL)
				{
					m_answerKey = pattern[input_buffer.size()];
					return;
				}
				if (pattern.rfind(input_buffer, 0) == 0)
				{
					m_answerKey = pattern[input_buffer.size()];
					return;
				}
			}
		}
	}
}

void AutoComputer::Draw()
{
	Computer::Draw();

	DrawBox(20, 350, 500, 550, GetColor(255, 100, 100), FALSE);

	DrawFormatString(0, 0, GetColor(0, 0, 0), "%f", m_timer.GetTime()); // 引数の色で文字列を表示
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "%c", m_answerKey); // 引数の色で文字列を表示

	DrawFormatString(30, 360, GetColor(0, 0, 0), "推定報酬: %d", 
		static_cast<int>(m_task.GetYomiganaText().size()) + static_cast<int>(Status::GetInstance()->GetLv(Status::EnhanceType::RewardRatioLv) * Status::GetInstance()->RewardRatio * static_cast<int>(m_task.GetYomiganaText().size()))); // 引数の色で文字列を表示

	SetFontSize(24);
	DrawFormatString(445, 360, GetColor(0, 0, 0), "AI"); // 引数の色で文字列を表示
	SetFontSize(16);
}

void AutoComputer::Update()
{
	Computer::Update();

	if (m_timer.GetTime() >= Status::GetInstance()->WaitingTimeForTyping - Status::GetInstance()->GetLv(Status::EnhanceType::SpeedLv) * Status::Speed)
	{
		AutoTyping();
		m_timer.Clear();
	}

	TypingCheck();	// 入力キーの正誤判定
	m_task.UpdateText(m_input_buffer, m_taskTextIndex, m_romajiTextIndex);
	
	// タイマーの更新
	m_timer.Update();
}

void AutoComputer::UpdateNewTask()
{
	m_task.SetNewText(Status::GetInstance()->GetLv(Status::EnhanceType::AutoTaskLv));
	Computer::UpdateNewTask();
}


void AutoComputer::AutoTyping()
{
	int num = GetRand(Status::GetInstance()->Accurate - Status::GetInstance()->GetLv(Status::EnhanceType::AccurateLv));

	// タイプ成功
	if (num == 0)
	{
		SearchAnswerKey();	// 正解のキーを探す
		m_preInput = m_answerKey;
	}
}