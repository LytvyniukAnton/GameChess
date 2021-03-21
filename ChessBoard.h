#pragma once
#include "Figure.h"
#include <iostream>

using namespace std;

struct Position {
	int x;
	int y;
};

class ChessBoard{
	Figure* figures[8][8];
	int x1_, y1_, x2_, y2_;
	Figure* figure_;
  
public:
	ChessBoard();
	virtual ~ChessBoard();
	void Init();
	void Paint() const;
	void Clean();
	void Move(int x1, int y1, int x2, int y2);
	void MoveBack();
	void setFigure(int x, int y, Figure* figure);
	bool isFreeSpaceBetween(int x1, int y1, int x2, int y2) const;
	Position getWhiteKingPosition() const;
	Position getBlackKingPosition() const;
	Figure* getFigure(int x, int y) const;
};
