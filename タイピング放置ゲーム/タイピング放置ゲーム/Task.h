#pragma once
#include <string>

class Task
{
private:
	std::string m_japaneseText;
	std::string m_romajiText;

public:
	std::string GetJapaneseText() { return m_japaneseText; }
	void SetJapaneseText(std::string str) { m_japaneseText = str; }
	std::string GetRomajiText() { return m_romajiText; }
	void SetRomajiText(std::string str) { m_romajiText = str; }
};