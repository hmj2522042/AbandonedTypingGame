#pragma once

#include <string>
#include <map>
#include <vector>

class RomajiTable
{
private:
	std::map<std::string, std::vector<std::string>> m_romajiMap;
public:
	RomajiTable()
	{
		m_romajiMap["あ"] = { "a" };
		m_romajiMap["い"] = { "i" };
		m_romajiMap["う"] = { "u" };
		m_romajiMap["え"] = { "e" };
		m_romajiMap["お"] = { "o" };
		m_romajiMap["ゐ"] = { "i" };
		m_romajiMap["ゑ"] = { "e" };

		m_romajiMap["ぁ"] = { "la" ,"xa"};
		m_romajiMap["ぃ"] = { "li" ,"xi"};
		m_romajiMap["ぅ"] = { "lu" ,"xu"};
		m_romajiMap["ぇ"] = { "le" ,"xe"};
		m_romajiMap["ぉ"] = { "lo" ,"xo"};

		// か行・濁音・拗音
		m_romajiMap["か"] = { "ka" };
		m_romajiMap["き"] = { "ki" };
		m_romajiMap["く"] = { "ku" };
		m_romajiMap["け"] = { "ke" };
		m_romajiMap["こ"] = { "ko" };
		m_romajiMap["が"] = { "ga" };
		m_romajiMap["ぎ"] = { "gi" };
		m_romajiMap["ぐ"] = { "gu" };
		m_romajiMap["げ"] = { "ge" };
		m_romajiMap["ご"] = { "go" };
		m_romajiMap["きゃ"] = { "kya" };
		m_romajiMap["きゅ"] = { "kyu" };
		m_romajiMap["きょ"] = { "kyo" };

		// ぎ行
		m_romajiMap["が"] = { "ga" };
		m_romajiMap["ぎ"] = { "gi" };
		m_romajiMap["ぐ"] = { "gu" };
		m_romajiMap["げ"] = { "ge" };
		m_romajiMap["ご"] = { "go" };
		m_romajiMap["ぎゃ"] = { "gya" };
		m_romajiMap["ぎゅ"] = { "gyu" };
		m_romajiMap["ぎょ"] = { "gyo" };

		// さ行・拗音
		m_romajiMap["さ"] = { "sa" };        m_romajiMap["サ"] = { "sa" };
		m_romajiMap["し"] = { "si" ,"shi" };       m_romajiMap["シ"] = { "si", "shi" };
		m_romajiMap["す"] = { "su" };        m_romajiMap["ス"] = { "su" };
		m_romajiMap["せ"] = { "se" };        m_romajiMap["セ"] = { "se" };
		m_romajiMap["そ"] = { "so" };        m_romajiMap["ソ"] = { "so" };
		m_romajiMap["しゃ"] = { "sha", "sya" };
		m_romajiMap["しゅ"] = { "shu", "syu" };
		m_romajiMap["しょ"] = { "sho", "syo" };

		// ざ行（濁音）
		m_romajiMap["ざ"] = { "za" }; m_romajiMap["ザ"] = { "za" };
		m_romajiMap["じ"] = { "ji","zi" }; m_romajiMap["ジ"] = { "ji","zi" };
		m_romajiMap["ず"] = { "zu" }; m_romajiMap["ズ"] = { "zu" };
		m_romajiMap["ぜ"] = { "ze" }; m_romajiMap["ゼ"] = { "ze" };
		m_romajiMap["ぞ"] = { "zo" }; m_romajiMap["ゾ"] = { "zo" };
		m_romajiMap["じゃ"] = { "ja","jya","zya" };
		m_romajiMap["じゅ"] = { "ju","jyu","zyu" };
		m_romajiMap["じょ"] = { "jo","jyo","zyo" };

		// た行・拗音
		m_romajiMap["た"] = { "ta" };
		m_romajiMap["ち"] = {"ti", "chi" };
		m_romajiMap["つ"] = {"tu", "tsu" };
		m_romajiMap["っ"] = { "ltu" ,"xtu","xtsu" ,"ltsu" };
		m_romajiMap["て"] = { "te" };
		m_romajiMap["と"] = { "to" };
		m_romajiMap["ちゃ"] = { "cha", "tya" };
		m_romajiMap["ちゅ"] = { "chu", "tyu" };
		m_romajiMap["ちょ"] = { "cho", "tyo" };

		m_romajiMap["つぁ"] = { "tsa" };
		m_romajiMap["つぃ"] = { "tsi" };
		m_romajiMap["つぇ"] = { "tse" };
		m_romajiMap["つぉ"] = { "tso" };

		// だ行（濁音・ぢ行）
		m_romajiMap["だ"] = { "da" };
		m_romajiMap["ぢ"] = { "ji","di" }; 
		m_romajiMap["づ"] = { "zu","du" }; 
		m_romajiMap["で"] = { "de" }; 
		m_romajiMap["ど"] = { "do" }; 
		m_romajiMap["ぢゃ"] = { "dya" };
		m_romajiMap["ぢゅ"] = { "dyu" };
		m_romajiMap["ぢょ"] = { "dyo" };

		m_romajiMap["てゃ"] = { "tha" };
		m_romajiMap["てぃ"] = { "thi" };
		m_romajiMap["てゅ"] = { "thu" };
		m_romajiMap["てぇ"] = { "the" };
		m_romajiMap["てょ"] = { "tho" };

		m_romajiMap["でゃ"] = { "dha" };
		m_romajiMap["でぃ"] = { "dhi" };
		m_romajiMap["でゅ"] = { "dhu" };
		m_romajiMap["でぇ"] = { "dhe" };
		m_romajiMap["でょ"] = { "dho" };

		// な行
		m_romajiMap["な"] = { "na" };
		m_romajiMap["に"] = { "ni" };
		m_romajiMap["ぬ"] = { "nu" };
		m_romajiMap["ね"] = { "ne" };
		m_romajiMap["の"] = { "no" };
		m_romajiMap["にゃ"] = { "nya" };
		m_romajiMap["にゅ"] = { "nyu" };
		m_romajiMap["にょ"] = { "nyo" };

		// は行・濁音・半濁音・拗音
		m_romajiMap["は"] = { "ha" };
		m_romajiMap["ひ"] = { "hi" };
		m_romajiMap["ふ"] = { "fu" };
		m_romajiMap["へ"] = { "he" };
		m_romajiMap["ほ"] = { "ho" };
		m_romajiMap["ば"] = { "ba" };
		m_romajiMap["び"] = { "bi" };
		m_romajiMap["ぶ"] = { "bu" };
		m_romajiMap["べ"] = { "be" };
		m_romajiMap["ぼ"] = { "bo" };
		m_romajiMap["ぱ"] = { "pa" };
		m_romajiMap["ぴ"] = { "pi" };
		m_romajiMap["ぷ"] = { "pu" };
		m_romajiMap["ぺ"] = { "pe" };
		m_romajiMap["ぽ"] = { "po" };
		m_romajiMap["ひゃ"] = { "hya" };
		m_romajiMap["ひゅ"] = { "hyu" };
		m_romajiMap["ひょ"] = { "hyo" };
		m_romajiMap["ふぁ"] = { "fa" };
		m_romajiMap["ふぃ"] = { "fi" };
		m_romajiMap["ふぇ"] = { "fe" };
		m_romajiMap["ふぉ"] = { "fo" };

		// びゃ行（濁音）
		m_romajiMap["びゃ"] = { "bya" };
		m_romajiMap["びゅ"] = { "byu" };
		m_romajiMap["びょ"] = { "byo" };

		// ぴゃ行（半濁音）
		m_romajiMap["ぴゃ"] = { "pya" };
		m_romajiMap["ぴゅ"] = { "pyu" };
		m_romajiMap["ぴょ"] = { "pyo" };

		// ま行
		m_romajiMap["ま"] = { "ma" };
		m_romajiMap["み"] = { "mi" };
		m_romajiMap["む"] = { "mu" };
		m_romajiMap["め"] = { "me" };
		m_romajiMap["も"] = { "mo" };
		// みゃ行
		m_romajiMap["みゃ"] = { "mya" };
		m_romajiMap["みゅ"] = { "myu" };
		m_romajiMap["みょ"] = { "myo" };

		// や行
		m_romajiMap["や"] = { "ya" };
		m_romajiMap["ゆ"] = { "yu" };
		m_romajiMap["よ"] = { "yo" };
		m_romajiMap["ゃ"] = { "lya","xya"  };
		m_romajiMap["ゅ"] = { "lyu","xyu"  };
		m_romajiMap["ょ"] = { "lyo","xyo" };

		// ら行
		m_romajiMap["ら"] = { "ra" };
		m_romajiMap["り"] = { "ri" };
		m_romajiMap["る"] = { "ru" };
		m_romajiMap["れ"] = { "re" };
		m_romajiMap["ろ"] = { "ro" };

		// りゃ行
		m_romajiMap["りゃ"] = { "rya" };
		m_romajiMap["りゅ"] = { "ryu" };
		m_romajiMap["りょ"] = { "ryo" };

		// わ・ん
		m_romajiMap["わ"] = { "wa" };
		m_romajiMap["を"] = { "wo" };
		m_romajiMap["ん"] = { "nn" };

		m_romajiMap["うぃ"] = { "whi" };
		m_romajiMap["うぇ"] = { "whe" };
		m_romajiMap["うぉ"] = { "who" };

		m_romajiMap["ヴ"] =	{ "vu" };  
		m_romajiMap["ヴぁ"] = { "va" };
		m_romajiMap["ヴぃ"] = { "vi" };
		m_romajiMap["ヴぇ"] = { "ve" };
		m_romajiMap["ヴぉ"] = { "vo" };
		m_romajiMap["ー"] = { "-" };

		m_romajiMap["a"] = { "a" };
		m_romajiMap["A"] = { "a" };
		m_romajiMap["b"] = { "b" };
		m_romajiMap["B"] = { "b" };
		m_romajiMap["c"] = { "c" };
		m_romajiMap["C"] = { "c" };
		m_romajiMap["d"] = { "d" };
		m_romajiMap["D"] = { "d" };
		m_romajiMap["e"] = { "e" };
		m_romajiMap["E"] = { "e" };
		m_romajiMap["f"] = { "f" };
		m_romajiMap["F"] = { "f" };
		m_romajiMap["g"] = { "g" };
		m_romajiMap["G"] = { "g" };
		m_romajiMap["h"] = { "h" };
		m_romajiMap["H"] = { "h" };
		m_romajiMap["i"] = { "i" };
		m_romajiMap["I"] = { "i" };
		m_romajiMap["j"] = { "j" };
		m_romajiMap["J"] = { "j" };
		m_romajiMap["k"] = { "k" };
		m_romajiMap["K"] = { "k" };
		m_romajiMap["l"] = { "l" };
		m_romajiMap["L"] = { "l" };
		m_romajiMap["m"] = { "m" };
		m_romajiMap["M"] = { "m" };
		m_romajiMap["n"] = { "n" };
		m_romajiMap["N"] = { "n" };
		m_romajiMap["o"] = { "o" };
		m_romajiMap["O"] = { "o" };
		m_romajiMap["p"] = { "p" };
		m_romajiMap["P"] = { "p" };
		m_romajiMap["q"] = { "q" };
		m_romajiMap["Q"] = { "q" };
		m_romajiMap["r"] = { "r" };
		m_romajiMap["R"] = { "r" };
		m_romajiMap["s"] = { "s" };
		m_romajiMap["S"] = { "s" };
		m_romajiMap["t"] = { "t" };
		m_romajiMap["T"] = { "t" };
		m_romajiMap["u"] = { "u" };
		m_romajiMap["U"] = { "u" };
		m_romajiMap["v"] = { "v" };
		m_romajiMap["V"] = { "v" };
		m_romajiMap["w"] = { "w" };
		m_romajiMap["W"] = { "w" };
		m_romajiMap["x"] = { "x" };
		m_romajiMap["X"] = { "x" };
		m_romajiMap["y"] = { "y" };
		m_romajiMap["Y"] = { "y" };
		m_romajiMap["z"] = { "z" };
		m_romajiMap["Z"] = { "z" };

		// Shift + 数字/記号
		m_romajiMap["!"] = { "!" };
		m_romajiMap["\""] = { "\"" };
		m_romajiMap["#"] = { "#" };
		m_romajiMap["$"] = { "$" };
		m_romajiMap["%"] = { "%" };
		m_romajiMap["&"] = { "&" };
		m_romajiMap["'"] = { "'" };
		m_romajiMap["("] = { "(" };
		m_romajiMap[")"] = { ")" };
		m_romajiMap["="] = { "=" };
		m_romajiMap["~"] = { "~" };
		m_romajiMap["|"] = { "|" };
		m_romajiMap["?"] = { "?" };
		m_romajiMap[","] = { "," };
		m_romajiMap["."] = { "." };

		// 数字キーと記号
		m_romajiMap["1"] = { "1" };
		m_romajiMap["2"] = { "2" };
		m_romajiMap["3"] = { "3" };
		m_romajiMap["4"] = { "4" };
		m_romajiMap["5"] = { "5" };
		m_romajiMap["6"] = { "6" };
		m_romajiMap["7"] = { "7" };
		m_romajiMap["8"] = { "8" };
		m_romajiMap["9"] = { "9" };
		m_romajiMap["0"] = { "0" };
		m_romajiMap["-"] = { "-" };
		m_romajiMap["\\"] = { "\\" };
		m_romajiMap["@"] = { "@" };
		m_romajiMap["/"] = { "/" };

		// 全角数字
		m_romajiMap["１"] = { "1" };
		m_romajiMap["２"] = { "2" };
		m_romajiMap["３"] = { "3" };
		m_romajiMap["４"] = { "4" };
		m_romajiMap["５"] = { "5" };
		m_romajiMap["６"] = { "6" };
		m_romajiMap["７"] = { "7" };
		m_romajiMap["８"] = { "8" };
		m_romajiMap["９"] = { "9" };
		m_romajiMap["０"] = { "0" };

		// 全角記号（Shift + 数字・その他） 
		m_romajiMap["！"] = { "!" };
		m_romajiMap["”"] = { "\"" };
		m_romajiMap["＃"] = { "#" };
		m_romajiMap["＄"] = { "$" };
		m_romajiMap["％"] = { "%" };
		m_romajiMap["＆"] = { "&" };
		m_romajiMap["’"] = { "'" };
		m_romajiMap["（"] = { "(" };
		m_romajiMap["）"] = { ")" };
		m_romajiMap["＝"] = { "=" };
		m_romajiMap["～"] = { "~" };
		m_romajiMap["｜"] = { "|" };
		m_romajiMap["？"] = { "?" }; 
		m_romajiMap["＠"] = { "@" };
		m_romajiMap["／"] = { "/" };
		m_romajiMap["＼"] = { "\\" };
		m_romajiMap["－"] = { "-" };
		m_romajiMap["、"] = { "," };
		m_romajiMap["。"] = { "." };
	}

	enum class Status
	{
		Miss,
		CorrectKey,
		NOnly_Complete,
		Complete,
	};

	// シングルトン
	static RomajiTable* GetInstance()
	{
		static RomajiTable instance;
		return &instance;
	}

	const std::map<std::string, std::vector<std::string>>& GetRomajiMap() { return m_romajiMap; }
};