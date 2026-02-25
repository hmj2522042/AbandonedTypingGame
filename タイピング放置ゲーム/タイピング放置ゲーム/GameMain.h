#pragma once
#include "Dxlib.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"

class GameMain
{
public:
	GameMain();
	//定数の定義
	static const int WIDTH = 640, HEIGHT = 480;	// ウィンドウの幅と高さのピクセル数

	void Draw();
	void Update();

	Timer GetTimer() { return m_timer; }
	void Run();
private:
	Timer m_timer;
	int m_handImage[2];
	float m_mosaicAlpha;
};