#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

enum EAction {
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	FALL = 3,
	ROTATE = 4,
};

//テトリス内のオブジェクト用クラス
class TetrisObject {
public:
	TetrisObject(int row, int col, std::vector<std::vector<int>> obj);
	virtual ~TetrisObject();
	std::vector<std::vector<int>>& GetObj();
	void SetObj(std::vector<std::vector<int>> obj);
	int GetRow();
	void SetRow(int row);
	int GetCol();
	void SetCol(int col);
	bool HorizLine(bool fixedMino);
	void EraseLine();
	void ShiftLine();

protected:
	int m_row;
	int m_col;
	std::vector<std::vector<int>> m_obj;

private:
	std::vector<int> m_horizlines;

};

//ミノ用のクラス
class MinoObject : public TetrisObject {
public:
	MinoObject(int row, int col, std::vector<std::vector<int>> obj);
	~MinoObject();
	void FallMino();
	void CombineMino(TetrisObject& field);
	void ClearPreMino(TetrisObject& field);
	void RotateMino();
	void CollisionCheck(std::vector<std::vector<int>> obj);
	int GetPrerow();

public:
	int m_action;
	bool m_fixed;

private:
	int m_prerow;
	int m_precol;
	int m_prerowsize;
	int m_precolsize;
	std::vector<std::vector<int>> m_preobj;
};
