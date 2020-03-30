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

//ラインが揃っていたらm_horizlineにプッシュバックする
bool TetrisObject::HorizLine(bool fixedMino)
{
	if (fixedMino) {
		for (int i = 1; i < 21; ++i) {
			for (int j = 1; j < 11; ++j) {
				if (m_obj[i][j] == 0) {
					break;
				}
				else {
					if (j == 10) {
						m_horizlines.push_back(i);
					}
				}
			}
		}
	}
	//入っていればtrueを返す
	if (!m_horizlines.empty()) {
		return true;
	}
	else {
		return false;
	}
}

void TetrisObject::EraseLine(){
	for (auto& elem : m_horizlines) {
		for (int i = 1; i < 11; ++i) {
			m_obj[elem][i] = 0;
		}
	}
}

void TetrisObject::ShiftLine(){
	std::vector<int> vec1 = { 1,0,0,0,0,0,0,0,0,0,0,1 };
	std::vector<int> vec2 = { 1,1,1,1,1,1,1,1,1,1,1,1 };
	//降順で並び替える
	std::sort(m_horizlines.begin(), m_horizlines.end(),std::greater<int>());
	m_obj.erase(m_obj.begin());
	for (auto& elem : m_horizlines) {
		m_obj.erase(m_obj.begin() + elem);
		m_obj.insert(m_obj.begin(), vec1);
	}
	m_obj.pop_back();
	m_obj.push_back(vec2);
	m_obj.insert(m_obj.begin(), vec1);
	m_horizlines.clear();
}

MinoObject::MinoObject(int row, int col, std::vector<std::vector<int>> obj) :
	TetrisObject(row, col, obj) {
	m_fixed = false;
}

MinoObject::~MinoObject(){
}

void MinoObject::FallMino(){
	++m_row;
	m_action = FALL;
}

void MinoObject::CombineMino(TetrisObject & field){
	//ClearPreMino(field);
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
	m_preobj = m_obj;
}

//前回のミノの位置を消去する
void MinoObject::ClearPreMino(TetrisObject & field)
{
	auto fieldObj = field.GetObj();
	//前回のミノの位置を削除
	for (int i = 0; i < m_prerowsize; ++i) {
		for (int j = 0; j < m_precolsize; ++j) {
			fieldObj[m_prerow + i][m_precol + j] += m_preobj[i][j];
			if (fieldObj[m_prerow + i][m_precol + j] > 1) {
				fieldObj[m_prerow + i][m_precol + j] = 0;
			}
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
		//Iミノなど右側がはみ出た場合、棒の長さがフィールドに収まるまでマイナスしていく
		while(m_col + m_obj[0].size() > 11){
			--m_col;
		}
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
