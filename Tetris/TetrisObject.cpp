#include "TetrisObject.h"

TetrisObject::TetrisObject(int row, int col, vector<vector<int>> obj) {
	m_row = row;
	m_col = col;
	m_obj = obj;
}

TetrisObject::~TetrisObject() {

}

vector<vector<int>>& TetrisObject::GetObj() {
	return m_obj;
}

void TetrisObject::SetObj(vector<vector<int>> obj) {
	m_obj = obj;
}

int TetrisObject::GetRow() {
	return m_row;
}

void TetrisObject::SetRow(int row) {
	m_row = row;
}


int TetrisObject::GetCol() {
	return m_col;
}

void TetrisObject::SetCol(int col) {
	m_col = col;
}

MinoObject::MinoObject(int row, int col, vector<vector<int>> obj) :
	TetrisObject(row, col, obj) {
}
