#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "TetrisObject.h"
using namespace std;

//�L�[����
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

//�e�g���X�̕`��
void drawField(vector<vector<int>>& field) {
	//�`��
	system("cls");
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (field[i][j] == 0) {
				cout << "�@";
			}
			else {
				cout << "��";
			}
		}
		cout << endl;
	}
}

//�t�B�[���h�ƃ~�m�̌���
void combineField(TetrisObject& field, MinoObject mino) {
	static int sRow=0,sCol=0,sRowSize=0,sColSize=0;
	vector<vector<int>> fieldObj = field.GetObj();
	vector<vector<int>> minoObj = mino.GetObj();
	//�O��̃~�m�̈ʒu���폜
	for (int i = 0; i < sRowSize; ++i) {
		for (int j = 0; j < sColSize; ++j) {
			fieldObj[sRow + i][sCol + j] = 0;
		}
	}

	//���݂̃~�m�̈ʒu������
	for (int i = 0; i < minoObj.size(); ++i) {
		for (int j = 0; j < minoObj[0].size(); ++j) {
			fieldObj[mino.GetRow() + i][mino.GetCol() + j] = minoObj[i][j];
		}
	}
	field.SetObj(fieldObj);

	//�ʒu�o���Ă���
	sRow = mino.GetRow();
	sRowSize = minoObj.size();
	sCol = mino.GetCol();
	sColSize = minoObj.size();
}

int main() {
	//�t�B�[���h�Â���
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
	TODO:�~�m�����ۂɗ��������Ă����A�Փ˂̃`�F�b�N�A�^�C�}�[�̐ݒ�A�e��~�m�Â���A
	*/
	while (1) {
		combineField(field, Lmino);
		drawField(field.GetObj());
	}
	return 0;
}