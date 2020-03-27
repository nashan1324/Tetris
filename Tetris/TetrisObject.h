#pragma once
#include <vector>
using namespace std;

//ミノとフィールドで使うクラス
class TetrisObject {
public:
	TetrisObject(int row, int col, vector<vector<int>> obj);
	virtual ~TetrisObject();
	vector<vector<int>>& GetObj();
	void SetObj(vector<vector<int>> obj);
	int GetRow();
	void SetRow(int row);
	int GetCol();
	void SetCol(int col);

protected:
	int m_row;
	int m_col;
	vector<vector<int>> m_obj;

};

class MinoObject : public TetrisObject {
public:
	MinoObject(int row, int col, vector<vector<int>> obj);
	//void Rotate();
	//void CollisionCheck();
};

