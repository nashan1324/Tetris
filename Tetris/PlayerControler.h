#pragma once
#include "TetrisObject.h"

class PlayerControler
{
public:
	PlayerControler();
	~PlayerControler();
	bool ControlMino(MinoObject& mino);
};

