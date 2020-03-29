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

//テトリスの描画
void drawField(std::vector<std::vector<int>> field) {
	//描画
	system("cls");
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (field[i][j] == 0) {
				std::cout << "　";
			}
			else {
				std::cout << "■";
			}
		}
		std::cout << std::endl;
	}
}

MinoObject generateMino() {
	std::random_device rnd;
	int minoType = rnd() % 7;
	std::vector<std::vector<int>> minoShape;
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
	MinoObject mino(2, 4, minoShape);
	return mino;
}


int main() {
	const int intervalTime = 1000;
	const int INITIAL_ROW = 2;
	const int INITIAL_COL = 4;
	//フィールド初期化
	std::vector<std::vector<int>> vec(22, std::vector<int>(12, 0));
		for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (i == 0 || j == 0 || i == 21 || j == 11) {
				vec[i][j] = 1;
			}
		}
	}
	TetrisObject field(0, 0, vec);

	//ミノの作成
	vec = {
		{1,0,0},
		{1,1,1},
	};
	MinoObject mino(2, 4, vec);

	//ミノを切り替える用の参照
	MinoObject& minoRef = mino;
	//プレイヤーコントローラーの作成
	PlayerControler player;
	/*
	TODO:　Iミノ、Zミノそれぞれエラーあり。消すことができない。
	*/
	std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
	while (1) {
		int interval = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time2).count();
		if (interval > intervalTime) {
			mino.FallMino();
			mino.ClearPreMino(field);
			mino.CollisionCheck(field.GetObj());
			mino.CombineMino(field);
			drawField(field.GetObj());
			if (mino.m_fixed) {
				mino = generateMino();
			}
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