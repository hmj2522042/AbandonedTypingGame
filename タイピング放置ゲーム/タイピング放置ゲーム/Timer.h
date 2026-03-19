#pragma once
#include <iostream>
#include <string>
#include "Time.hpp"

class Timer {
private:
	float m_time;
	bool m_isEnable; // 有効か
	std::string m_timeText;

public:
	Timer();

	void Update();
	void Stop();	// タイマーを止める
	void Clear() { m_time = 0.0f; }

	bool GetIsEnable() { return m_isEnable; }
	float GetTime() { return m_time; }
};