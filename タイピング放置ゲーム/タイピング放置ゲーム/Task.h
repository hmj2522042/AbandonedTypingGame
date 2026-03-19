#pragma once
#include <string>
#include "Screen.h"
#include "Vector2.h"
#include "TaskTable.h"

class Task
{
private:
	const TaskTable m_taskTable;
	std::string m_mainText;	// 漢字こみ
	std::string m_romajiText;	// ローマ字
	std::string m_yomiganaText;	// ひらがなのみ(内部処理に使うだけ)
	Vector2 m_mainPos;
	Vector2 m_romajiPos;

	int m_mainWidth;	// 文字列全体の長さを取得
	int m_romajiWidth;	// 文字列全体の長さを取得

public:
	static constexpr int MainFontSize = 30;
	static constexpr int YomiganaFontSize = 21;
	static constexpr int SubFontSize = 16;
	static constexpr Vector2 Margin = Vector2(0, MainFontSize);

	Task() :
		m_romajiText(""),
		m_mainWidth(0),
		m_romajiWidth(0),
		m_mainPos(Vector2(0, Screen::Height / 2 - GetFontSize() / 2)),
		m_romajiPos(Vector2(0, Screen::Height / 2 - GetFontSize() / 2) + Margin)
	{
	}
	
	void SetNewText(int textLevel)
	{
		int rand = GetRand(TaskTable::MaxTaskPair - 1);

		switch (textLevel)
		{
		case 1:
			SetMainText(m_taskTable.taskPair2to3[rand].m_main);
			SetYomiganaText(m_taskTable.taskPair2to3[rand].m_yomigana);
			break;
		case 2:
			SetMainText(m_taskTable.taskPair4to7[rand].m_main);
			SetYomiganaText(m_taskTable.taskPair4to7[rand].m_yomigana);
			break;
		case 3:
			SetMainText(m_taskTable.taskPair8to13[rand].m_main);
			SetYomiganaText(m_taskTable.taskPair8to13[rand].m_yomigana);
			break;
		case 4:
			SetMainText(m_taskTable.taskPair14to20[rand].m_main);
			SetYomiganaText(m_taskTable.taskPair14to20[rand].m_yomigana);
			break;
		}

		// 文字列の長さ
		SetFontSize(Task::MainFontSize);	// フォントサイズ変更
		m_mainWidth = GetDrawStringWidth(m_mainText.c_str(), -1);	// 文字列全体の長さを取得
		SetFontSize(Task::SubFontSize);	// フォントサイズ変更
		m_romajiWidth = GetDrawStringWidth(m_romajiText.c_str(), -1);	// 文字列全体の長さを取得
		SetFontSize(16);	// フォントサイズ変更
	}

	void UpdateText(std::string input_buffer, int taskTextIndex, size_t& romajiTextIndex)
	{
		m_romajiText.erase(romajiTextIndex - input_buffer.size()); // 未入力の部分を削除

		size_t index = 0;

		for (size_t i = taskTextIndex; i < m_yomiganaText.size();)
		{
			unsigned char c = static_cast<unsigned char>(m_yomiganaText[i]);

			// target(例：あ、じゃ、G、!)の選定
			int target_byte = 1;	// デフォルトでバイト数 = 1

			// SHIFT-JISの先頭バイトで2バイト文字を判定
			if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
			{
				target_byte = 2;

				// 後ろに二文字以上あるなら、二文字目(拗音、促音、發音)の判定
				if (i + target_byte + 2 <= m_yomiganaText.size())
				{
					bool secondCharSearch = false;

					// 2文字目が拗音「ゃゅょ」
					if (m_yomiganaText.substr(i + target_byte, 2) == "ゃ" ||
						m_yomiganaText.substr(i + target_byte, 2) == "ゅ" ||
						m_yomiganaText.substr(i + target_byte, 2) == "ぃ" ||
						m_yomiganaText.substr(i + target_byte, 2) == "ぇ" ||
						m_yomiganaText.substr(i + target_byte, 2) == "ょ")
					{
						secondCharSearch = true;
					}

					// 一文字目が促音「っ」
					if (m_yomiganaText.substr(i, 2) == "っ")
					{
						secondCharSearch = true;
					}

					// 一文字目が發音「ん」
					if (m_yomiganaText.substr(i, 2) == "ん")
					{
						secondCharSearch = true;
					}

					if (secondCharSearch)
					{
						target_byte += 2;
					}
				}
			}

			// 読み仮名からローマ字に変換処理
			std::string text = ConvertToRomaji(i, target_byte, input_buffer, taskTextIndex);
			if (text != "miss")
			{
				m_romajiText += text;
			}
			i += target_byte;
			//romajiTextIndex += text.size();
		}
	}

	// indexはローマ字表示中に使うよみがな何文字目かの番号
	std::string ConvertToRomaji(int index, int& target_byte, std::string input_buffer, int taskTextIndex)
	{
		std::string target_first = "";
		std::string target_second = "";
		const auto& map = RomajiTable::GetInstance()->GetRomajiMap();
		auto it = map.find(m_yomiganaText.substr(index, target_byte));

		////////////////////////// あるふぁべっと　英語 ///////////////////////////////

		if (target_byte == 1)
		{
			// romajiMapに存在するパターンなら
			// target全て読み込んで（拗音ありなら4バイト分）
			it = map.find(m_yomiganaText.substr(index, target_byte));

			if (it != map.end())
			{
				for (std::string pattern : it->second)
				{
					// もしタイプ中の文字なら
					if (index == taskTextIndex && pattern.rfind(input_buffer, 0) == 0)
					{
						std::string str = pattern;
						return str;
					}
					// タイプ中の文字じゃないならマップで最初にとれたValueを出力
					if (index != taskTextIndex)
					{
						return pattern;
					}
				}
			}
		}

		if (target_byte >= 2)
		{
			target_first = m_yomiganaText.substr(index, 2);	// 一文字目を得る、先頭から2バイト読み込む
		}
		if (target_byte >= 4)
		{
			target_second = m_yomiganaText.substr(index + 2, 2);	// 二文字目を得る、3バイト目から2バイト読み込む
		}

		// 發音　促音はひらがな二文字読み込めるなら判定を行う
		if (target_byte >= 4)
		{
			////////////////////////// 發音 "ん" ///////////////////////////////
			if (target_first == "ん" && input_buffer == "n")
			{
				target_byte = 2; // 本来は4バイト分確保しているが、"ん"だけ入力完了なので2バイトに更新する
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
							// もしタイプ中の文字なら
							// 例：じゃ → jy なら jyaのみ抽出
							if (index == taskTextIndex && pattern.rfind(input_buffer, 0) == 0)
							{
								return std::string(1, pattern[0]);
							}
							// タイプ中の文字じゃなくても'n'だけ出力
							if (index != taskTextIndex)
							{
								return std::string(1, pattern[0]);
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
				"あ", "い", "う", "え", "お", "ん"
				};

				// 二文字目がignoreに含まれるなら false つまり"ltsu,ltu"入力しないと"っ"にならない
				for (const std::string t : ignore_sokuon) {
					if (target_second.find(t) != std::string::npos)
					{
						sokuon_flag = false;
						break;
					}
				}

				// "tt"まで入力されていたら
				if (sokuon_flag)
				{
					// 3文字取得可能なら 拗音("ゃ,ゅ,ょ") までしらべる
					if (m_yomiganaText.size() >= taskTextIndex + target_byte + 2)
					{
						std::string target_third = m_yomiganaText.substr(index + 4, 2);	// 二文字目を得る、3バイト目から2バイト読み込む

						// 3文字目が拗音「ゃゅょ」
						if (target_third == "ゃ" || target_third == "ゅ" || target_third == "ょ" || target_third == "ぃ" || target_third == "ぇ")
						{
							target_byte += 2;
							it = map.find(target_second + target_third);

							// romajiMapに存在するパターンなら
							if (it != map.end())
							{
								// 二文字目のローマ字の一文字目"例：j"の判定
								for (std::string pattern : it->second)
								{
									std::string sokuon = pattern[0] + pattern;	// 例：ja → jja 

									// もしタイプ中の文字なら
									// 一致したので "っじゃ"は"例：jja"で出力
									if (index == taskTextIndex && sokuon.rfind(input_buffer, 0) == 0)
									{
										return sokuon;
									}
									// タイプ中の文字じゃないならマップで最初にとれたValueを出力
									if (index != taskTextIndex)
									{
										return sokuon;
									}
								}
							}
						}
					}

					// 拗音なしで二文字までの促音"っ"なら
					it = map.find(target_second);

					// romajiMapに存在するパターンなら
					if (it != map.end())
					{
						// 二文字目のローマ字の一文字目"例：j"の判定
						for (std::string pattern : it->second)
						{
							std::string sokuon = pattern[0] + pattern;	// 例：ji → jji 

							// もしタイプ中の文字なら
							// 一致したので "っじゃ"は"例：jja"で出力
							if (index == taskTextIndex && sokuon.rfind(input_buffer, 0) == 0)
							{
								return sokuon;
							}
							// タイプ中の文字じゃないならマップで最初にとれたValueを出力
							if (index != taskTextIndex)
							{
								return sokuon;
							}
						}
					}
				}
			}
		}

		////////////////////////// 拗音あり ("じゃ,じゅ,じょ") ///////////////////////////////

		// target全て読み込んで（拗音ありなら4バイト分）
		it = map.find(target_first + target_second);

		// romajiMapに存在するパターンなら
		if (it != map.end())
		{
			for (std::string pattern : it->second)
			{
				// 完全一致
				if (index == taskTextIndex && pattern == input_buffer)
				{
					return input_buffer;
				}
				// 一致したので出力
				if (index == taskTextIndex && pattern.rfind(input_buffer, 0) == 0)
				{
					return pattern;
				}
				// タイプ中の文字じゃないならマップで最初にとれたValueを出力
				if (index != taskTextIndex)
				{
					return pattern;
				}
			}
		}

		/////////////////////////// 一文字ずつ通常入力 例：じょ→　”じ”と”ょ”に分けて入力とか ///////////////////////////////

		// 一文字ずつ通常入力 "じゃ"→"じ"だけ入力
		if (target_byte >= 2)
		{
			target_byte = 2;
			it = map.find(target_first);

			// romajiMapに存在するパターンなら
			if (it != map.end())
			{
				for (std::string pattern : it->second)
				{
					// 完全一致
					if (index == taskTextIndex && pattern == input_buffer)
					{
						return input_buffer;
					}
					// タイプ中の文字が部分一致したので出力
					if (index == taskTextIndex && pattern.rfind(input_buffer, 0) == 0)
					{
						return pattern;
					}
					// タイプ中の文字じゃないならマップで最初にとれたValueを出力
					if (index != taskTextIndex)
					{
						return pattern;
					}
				}
			}
		}
		return "miss";
	}

	std::string GetMainText() { return m_mainText; }
	std::string GetYomiganaText() { return m_yomiganaText; }
	std::string GetRomajiText() { return m_romajiText; }
	Vector2 GetMainPosition() { return m_mainPos; }
	Vector2 GetRomajiPosition() { return m_romajiPos; }
	int GetMainTextWidth() { return m_mainWidth; }
	int GetRomajiTextWidth() { return m_romajiWidth; }

	void AddChar(char c, size_t insertIndex) { m_romajiText.insert(insertIndex, 1, c); }

	void SetMainText(std::string str) { m_mainText = str; }
	void SetYomiganaText(std::string str) { m_yomiganaText = str; }
	void SetRomajiText(std::string str) { m_romajiText = str; }

	void SetMainXPos(float pos) { m_mainPos.x = pos; }
	void SetRomajiXPos(float pos) { m_romajiPos.x = pos; }
	void SetMainYPos(float pos) { m_mainPos.y = pos; }
	void SetRomajiYPos(float pos) { m_romajiPos.y = pos; }
};