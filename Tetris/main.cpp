#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "TetrisObject.h"
using namespace std;

//キー入力
void getKey() {
	if (GetAsyncKeyState(VK_DOWN)) {
		cout << "DOWN" << endl;
	}
	else if (GetAsyncKeyState(VK_UP)) {
		cout << "UP" << endl;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		cout << "LEGT" << endl;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		cout << "RIGHT" << endl;
	}
	else {
	}
}

//テトリスの描画
void drawField(vector<vector<int>>& field) {
	//描画
	system("cls");
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (field[i][j] == 0) {
				cout << "　";
			}
			else {
				cout << "■";
			}
		}
		cout << endl;
	}
}

//フィールドとミノの結合
void combineField(TetrisObject& field, MinoObject mino) {
	static int sRow=0,sCol=0,sRowSize=0,sColSize=0;
	vector<vector<int>> fieldObj = field.GetObj();
	vector<vector<int>> minoObj = mino.GetObj();
	//前回のミノの位置を削除
	for (int i = 0; i < sRowSize; ++i) {
		for (int j = 0; j < sColSize; ++j) {
			fieldObj[sRow + i][sCol + j] = 0;
		}
	}

	//現在のミノの位置を結合
	for (int i = 0; i < minoObj.size(); ++i) {
		for (int j = 0; j < minoObj[0].size(); ++j) {
			fieldObj[mino.GetRow() + i][mino.GetCol() + j] = minoObj[i][j];
		}
	}
	field.SetObj(fieldObj);

	//位置覚えておく
	sRow = mino.GetRow();
	sRowSize = minoObj.size();
	sCol = mino.GetCol();
	sColSize = minoObj.size();
}

int main() {
	//フィールドづくり
	vector<vector<int>> vec(22, vector<int>(12, 0));
		for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (i == 0 || j == 0 || i == 21 || j == 11) {
				vec[i][j] = 1;
			}
		}
	}

	TetrisObject field(0, 0, vec);
	vec = {
		{1,0,0},
		{1,1,1},
	};
	cout << vec[0].size() << endl;
	MinoObject Lmino(3, 3, vec);
	
	/*
	TODO:ミノを実際に落下させていく、衝突のチェック、タイマーの設定、各種ミノづくり、
	*/
	while (1) {
		combineField(field, Lmino);
		drawField(field.GetObj());
	}
	return 0;
}