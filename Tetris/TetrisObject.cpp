#include "TetrisObject.h"

TetrisObject::TetrisObject(int row, int col, std::vector<std::vector<int>> obj) {
	m_row = row;
	m_col = col;
	m_obj = obj;
}

TetrisObject::~TetrisObject() {

}

std::vector<std::vector<int>>& TetrisObject::GetObj() {
	return m_obj;
}

void TetrisObject::SetObj(std::vector<std::vector<int>> obj) {
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

MinoObject::MinoObject(int row, int col, std::vector<std::vector<int>> obj) :
	TetrisObject(row, col, obj) {
	m_fixed = false;
}

void MinoObject::FallMino(){
	++m_row;
	m_action = FALL;
}

void MinoObject::CombineMino(TetrisObject & field){
	ClearPreMino(field);
	//操作用と落下用で2回衝突チェックしておく
	//CollisionCheck(fieldObj);
	//FallMino();
	//CollisionCheck(fieldObj);

	auto fieldObj = field.GetObj();
	//現在のミノの位置をフィールドに結合(足し合わせる)
	for (int i = 0; i < m_obj.size(); ++i) {
		for (int j = 0; j < m_obj[0].size(); ++j) {
			fieldObj[m_row + i][m_col + j] += m_obj[i][j];
		}
	}
	field.SetObj(fieldObj);

	//位置覚えておく
	m_prerow = m_row;
	m_precol = m_col;
	m_prerowsize = m_obj.size();
	m_precolsize = m_obj[0].size();
}

//前回のミノの位置を消去する
void MinoObject::ClearPreMino(TetrisObject & field)
{
	auto fieldObj = field.GetObj();
	//前回のミノの位置を削除
	for (int i = 0; i < m_prerowsize; ++i) {
		for (int j = 0; j < m_precolsize; ++j) {
			fieldObj[m_prerow + i][m_precol + j] = 0;
		}
	}
	field.SetObj(fieldObj);
}

//ミノを90度時計回りに回転
void MinoObject::RotateMino(){
	//行と列が逆のvectorを用意
	std::vector<std::vector<int>> vec(m_obj[0].size(), std::vector<int>(m_obj.size(), 0));

	for (int i = 0; i < m_obj[0].size(); ++i) {
		for (int j = 0; j < m_obj.size(); ++j) {
			vec[i][j] = m_obj[m_obj.size() - 1 - j][i];
		}
	}

	//回転させたものと入れ替え
	m_obj = vec;
}

//衝突したかのチェック、使う前にClerPreObjを呼ぶこと
void MinoObject::CollisionCheck(std::vector<std::vector<int>> fieldObj) {
	//minoと結合した後のフィールドに2が存在していたら、巻き戻す
	//右
	if (m_action == RIGHT) {
		for (int i = 0; i < m_obj.size(); ++i) {
			for (int j = 0; j < m_obj[0].size(); ++j) {
				fieldObj[m_row + i][m_col + j] += m_obj[i][j];
				if (fieldObj[m_row + i][m_col + j] > 1) {
					--m_col;
					return;
				}
			}
		}
	}
	//左
	else if (m_action == LEFT) {
		for (int i = 0; i < m_obj.size(); ++i) {
			for (int j = 0; j < m_obj[0].size(); ++j) {
				fieldObj[m_row + i][m_col + j] += m_obj[i][j];
				if (fieldObj[m_row + i][m_col + j] > 1) {
					++m_col;
					return;
				}
			}
		}
	}
	//下
	else if(m_action == DOWN){
		for (int i = 0; i < m_obj.size(); ++i) {
			for (int j = 0; j < m_obj[0].size(); ++j) {
				fieldObj[m_row + i][m_col + j] += m_obj[i][j];
				if (fieldObj[m_row + i][m_col + j] > 1) {
					--m_row;
					m_fixed = true;
					return;
				}
			}
		}
	}
	//落下
	else if (m_action == FALL) {
		for (int i = 0; i < m_obj.size(); ++i) {
			for (int j = 0; j < m_obj[0].size(); ++j) {
				fieldObj[m_row + i][m_col + j] += m_obj[i][j];
				if (fieldObj[m_row + i][m_col + j] > 1) {
					--m_row;
					m_fixed = true;
					return;
				}
			}
		}
	}
	else if (m_action == ROTATE) {
		for (int i = 0; i < m_obj.size(); ++i) {
			for (int j = 0; j < m_obj[0].size(); ++j) {
				fieldObj[m_row + i][m_col + j] += m_obj[i][j];
				if (fieldObj[m_row + i][m_col + j] > 1) {
					--m_row;
					return;
				}
			}
		}
	}

	//int underRow = m_row + m_obj.size() - 1;
	//if (underRow >= 20) {
	//	m_row = 21 - m_obj.size();
	//	m_fixed = true;
	//}
}

int MinoObject::GetPrerow()
{
	return m_prerow;
}
