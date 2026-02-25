#include "Timer.h"
#include "DxLib.h"
Timer::Timer() :
	m_time(0.0f),
	m_isEnable(true)
{
}

void Timer::Update()
{
	// タイマーが有効でないなら
	if (!m_isEnable) return;

	m_time += Time::GetInstance()->GetDeltaTime();
}

void Timer::Stop()
{
	m_isEnable = false;
}