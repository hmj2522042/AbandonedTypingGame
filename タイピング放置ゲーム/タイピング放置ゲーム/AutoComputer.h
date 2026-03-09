#pragma once
#include "Computer.h"

class AutoComputer : public Computer
{
public:
	virtual void Draw() override;
	virtual void Update() override;
};