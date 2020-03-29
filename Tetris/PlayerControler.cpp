#include "PlayerControler.h"
#include <Windows.h>

PlayerControler::PlayerControler(){
}


PlayerControler::~PlayerControler(){
}

bool PlayerControler::ControlMino(MinoObject& mino){
	if (GetAsyncKeyState(VK_DOWN)) {
		mino.SetRow(mino.GetRow() + 1);
		mino.m_action = DOWN;
	}
	else if (GetAsyncKeyState(VK_SPACE)) {
		mino.RotateMino();
		mino.m_action = ROTATE;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		mino.SetCol(mino.GetCol() - 1);
		mino.m_action = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		mino.SetCol(mino.GetCol() + 1);
		mino.m_action = RIGHT;
	}
	else {
		return false;
	}
	return true;
}


