#pragma once
class Status
{
private:

	int m_manualTask_lv;
	int m_autoTask_lv;
	int m_efficient_lv;	// 打ち方の効率(じゃ　を　jya ではなく ja　で打つとか)
	int m_speed_lv;		// 速さ
	int m_accurate_lv;	// 正確性

	int m_rewardRatio_lv;	// 報酬割合

	int m_token;	// 所持金

	int m_enhanceSE;
	int m_cantSE;

public:
	static constexpr int MaxTaskLevel = 4;	// タスクレベル
	static constexpr int MaxEfficientLevel = 4;	// 効率レベル
	static constexpr int MaxSpeedLevel = 20;	// タスクレベル
	static constexpr int MaxAccurateLevel = 10;	// タスクレベル
	static constexpr int MaxRewardRatioLevel = 100;	// タスクレベル

	static constexpr float Speed = 0.1f;	// レベルに乗算する
	static constexpr int Accurate = 10;		// タイプ成功確率 1 / Accurate 
	static constexpr float WaitingTimeForTyping = 2.0f; // 自動タイピングまでのベースの時間
	static constexpr float RewardRatio = 0.2f; // 報酬レベルに乗算する重み

	// 強化要素
	enum class EnhanceType
	{
		ManualTaskLv,		// 業務レベル
		AutoTaskLv,		// 業務レベル
		EfficientLv,	// 打ち方の効率(じゃ　を　jya ではなく ja　で打つとか)
		SpeedLv,			// 速さ
		AccurateLv,		// 正確性
		RewardRatioLv,		// 報酬割合

		Length,
	};

	// 強化コスト
	static constexpr int ManualTaskLvEnhanceCost[MaxTaskLevel - 1] =
	{
		50,
		150,
		400,
	};
	

	// 強化コスト
	static constexpr int AutoTaskLvEnhanceCost[MaxTaskLevel - 1] =
	{
		100,
		300,
		1000,
	};

	static constexpr int EfficientLvEnhanceCost[MaxEfficientLevel - 1] =
	{
		100,
		300,
		1000,
	};

	static constexpr int SpeedLvEnhanceCost[MaxSpeedLevel - 1] =
	{
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80,
		80
	};

	static constexpr int AccurateLvEnhanceCost[MaxAccurateLevel - 1] =
	{
		20,
		50,
		100,
		200,
		350,
		550,
		800,
		1100,
		1500
	};

	static constexpr int RewardRatioLvEnhanceCost[MaxRewardRatioLevel - 1] =
	{
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50
	};

	static constexpr const char* EnhanceText[static_cast<int>(EnhanceType::Length)] =
	{
		"手動業務内容",
		"AI業務内容",
		"タイプ効率",
		"速さ      ",
		"正確度	   ",
		"報酬量	   "
	};

public:
	Status() :
		m_manualTask_lv(1),
		m_autoTask_lv(1),
		m_efficient_lv(1),
		m_speed_lv(1),
		m_accurate_lv(1),
		m_rewardRatio_lv(1),
		m_token(0)
	{
		m_enhanceSE = LoadSoundMem("Resources/Sound/enhance.mp3");
		ChangeVolumeSoundMem(90, m_enhanceSE);
		m_cantSE = LoadSoundMem("Resources/Sound/cant.mp3");
		ChangeVolumeSoundMem(90, m_cantSE);
	}

public:
	// シングルトン
	static Status* GetInstance()
	{
		static Status instance;
		return &instance;
	}
	int GetToken() { return m_token; }

	void GetReward(int num) 
	{
		int reward = num + num * RewardRatio * m_rewardRatio_lv;
		m_token += reward + GetRand(reward);
	}

	int GetLv(EnhanceType type)
	{
		switch (type)
		{
		case EnhanceType::ManualTaskLv:
			return m_manualTask_lv;
			break;
		case EnhanceType::AutoTaskLv:
			return m_autoTask_lv;
			break;
		case EnhanceType::EfficientLv:
			return m_efficient_lv;
			break;
		case EnhanceType::SpeedLv:
			return m_speed_lv;
			break;
		case EnhanceType::AccurateLv:
			return m_accurate_lv;
			break;
		case EnhanceType::RewardRatioLv:
			return m_rewardRatio_lv;
			break;
		}
	}

	int GetMaxLv(EnhanceType type)
	{
		switch (type)
		{
		case EnhanceType::ManualTaskLv:
			return MaxTaskLevel;
			break;
		case EnhanceType::AutoTaskLv:
			return MaxTaskLevel;
			break;
		case EnhanceType::EfficientLv:
			return MaxEfficientLevel;
			break;
		case EnhanceType::SpeedLv:
			return MaxSpeedLevel;
			break;
		case EnhanceType::AccurateLv:
			return MaxAccurateLevel;
			break;
		case EnhanceType::RewardRatioLv:
			return MaxRewardRatioLevel;
			break;
		}
	}

	void LvUp(EnhanceType type)
	{
		switch (type)
		{
		case EnhanceType::ManualTaskLv:
			if (m_token >= ManualTaskLvEnhanceCost[m_manualTask_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= ManualTaskLvEnhanceCost[m_manualTask_lv - 1];
				m_manualTask_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		case EnhanceType::AutoTaskLv:
			if (m_token >= AutoTaskLvEnhanceCost[m_autoTask_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= AutoTaskLvEnhanceCost[m_autoTask_lv - 1];
				m_autoTask_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		case EnhanceType::EfficientLv:
			if (m_token >= EfficientLvEnhanceCost[m_efficient_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= EfficientLvEnhanceCost[m_efficient_lv - 1];
				m_efficient_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		case EnhanceType::SpeedLv:
			if (m_token >= SpeedLvEnhanceCost[m_speed_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= SpeedLvEnhanceCost[m_speed_lv - 1];
				m_speed_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		case EnhanceType::AccurateLv:
			if (m_token >= AccurateLvEnhanceCost[m_accurate_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= AccurateLvEnhanceCost[m_accurate_lv - 1];
				m_accurate_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		case EnhanceType::RewardRatioLv:
			if (m_token >= RewardRatioLvEnhanceCost[m_rewardRatio_lv - 1] && Status::GetInstance()->GetLv(type) < Status::GetInstance()->GetMaxLv(type))
			{
				m_token -= RewardRatioLvEnhanceCost[m_rewardRatio_lv - 1];
				m_rewardRatio_lv++;
				PlaySoundMem(m_enhanceSE, DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(m_cantSE, DX_PLAYTYPE_BACK);
			}
			break;
		}
	}

	int GetEnhanceCost(EnhanceType type)
	{
		switch (type)
		{
		case EnhanceType::ManualTaskLv:
			return ManualTaskLvEnhanceCost[m_manualTask_lv - 1];
			break;
		case EnhanceType::AutoTaskLv:
			return AutoTaskLvEnhanceCost[m_autoTask_lv - 1];
			break;
		case EnhanceType::EfficientLv:
			return EfficientLvEnhanceCost[m_efficient_lv - 1];
			break;
		case EnhanceType::SpeedLv:
			return SpeedLvEnhanceCost[m_speed_lv - 1];
			break;
		case EnhanceType::AccurateLv:
			return AccurateLvEnhanceCost[m_accurate_lv - 1];
			break;
		case EnhanceType::RewardRatioLv:
			return RewardRatioLvEnhanceCost[m_rewardRatio_lv - 1];
			break;
		}
	}
};