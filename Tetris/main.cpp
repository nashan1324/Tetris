#include <stdlib.h>
#include <random>
#include "TetrisObject.h"
#include "Timer.h"
#include "PlayerControler.h"

enum EMino {
	LMINO = 0,
	IMINO = 1,
	OMINO = 2,
	TMINO = 3,
	ZMINO = 4,
	JMINO = 5,
	SMINO = 6,
};

//�e�g���X�̕`��
void drawField(std::vector<std::vector<int>> field) {
	//�`��
	system("cls");
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (field[i][j] == 0) {
				std::cout << "�@";
			}
			else{
				std::cout << "��";
			}
		}
		std::cout << std::endl;
	}
}

MinoObject generateMino() {
	std::random_device rnd;
	int minoType = rnd() % 7;
	std::vector<std::vector<int>> minoShape;
	//minoType = TMINO;
	switch(minoType)
	{
	case LMINO:
		minoShape = {
			{1,0},
			{1,0},
			{1,1},
		};
		break;
	case IMINO:
		minoShape = {
			{1},
			{1},
			{1},
			{1},
		};
		break;
	case OMINO:
		minoShape = {
			{1,1},
			{1,1},
		};
		break;
	case TMINO:
		minoShape = {
			{1,1,1},
			{0,1,0},
		};
		break;
	case ZMINO:
		minoShape = {
			{1,1,0},
			{0,1,1},
		};
		break;
	case JMINO:
		minoShape = {
			{0,1},
			{0,1},
			{1,1},
		};
		break;
	case SMINO:
		minoShape = {
			{0,1,1},
			{1,1,0},
		};
		break;
	default:
		break;
	}
	MinoObject mino(0, 4, minoShape);
	return mino;
}


int main() {
	const int intervalTime = 1000;
	//�t�B�[���h����
	std::vector<std::vector<int>> vec(22, std::vector<int>(12, 0));
		for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (j == 0 || i == 21 || j == 11) {
				vec[i][j] = 1;
			}
		}
	}
	TetrisObject field(0, 0, vec);

	//�~�m�̐���
	auto mino = generateMino();
	//�~�m��؂�ւ���p�̎Q��
	auto& minoRef = mino;
	//�v���C���[�R���g���[���[�̍쐬
	PlayerControler player;
	/*
	TODO: �Q�[���J�n�A�I����������(����)
	*/
	auto time1 = std::chrono::high_resolution_clock::now();
	auto time2 = std::chrono::high_resolution_clock::now();
	while (1) {
		int interval = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time2).count();
		if (interval > intervalTime) {
			mino.FallMino();
			mino.ClearPreMino(field);
			mino.CollisionCheck(field.GetObj());
			mino.CombineMino(field);
			//�Œ艻����Ă�������悤�ɂ���
			if (field.HorizLine(mino.m_fixed) && mino.m_fixed) {
				field.EraseLine();
				field.ShiftLine();
			}
			if (mino.m_fixed) {
				mino.~MinoObject();
				mino = generateMino();
			}
			drawField(field.GetObj());
			time2 = std::chrono::high_resolution_clock::now();
		}
		else {
			if (player.ControlMino(mino)) {
				mino.ClearPreMino(field);
				mino.CollisionCheck(field.GetObj());
				mino.CombineMino(field);
				drawField(field.GetObj());
			}
			time1 = std::chrono::high_resolution_clock::now();
		}

	}
	return 0;
}