#pragma once
#include "ChessBoard.h"

class Game{
	ChessBoard board;
	int cnt;
  
public:
	Game();
	void OneMove();
	void Reset();
	void Show() const;
	void Save() const;
	void Load();
	void Help() const;
	bool isСheckForWhite() const;
	bool isСheckForBlack() const;
	bool isMateForWhite();
	bool isMateForBlack();
	void CancelLastMove();
	string getLastColor() const;
	bool getPermishen(int x1, int y1, int x2, int y2) const;
};
