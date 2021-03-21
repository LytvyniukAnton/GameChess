#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	Init();
}

ChessBoard::~ChessBoard()
{
	Clean();
}

void ChessBoard::Init()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			figures[i][j]=nullptr;
		}
	}

	for (int j = 0; j < 8; j++) {
		Figure* pawn = new Figure(Figure::pawn, Figure::eBlack);
		figures[6][j] = pawn;
	}
	
	for (int j = 0; j < 8; j++) {
		Figure* pawn = new Figure(Figure::pawn, Figure::eWhite);
		figures[1][j] = pawn;
	}

	Figure* kNightBL = new Figure(Figure::kNight, Figure::eBlack);
	Figure* kNightBR = new Figure(Figure::kNight, Figure::eBlack);
	Figure* kNightWL = new Figure(Figure::kNight, Figure::eWhite);
	Figure* kNightWR = new Figure(Figure::kNight, Figure::eWhite);
	figures[7][1] = kNightBL;
	figures[7][6] = kNightBR;
	figures[0][1] = kNightWL;
	figures[0][6] = kNightWR;

	Figure* bishopBL = new Figure(Figure::bishop, Figure::eBlack);
	Figure* bishopBR = new Figure(Figure::bishop, Figure::eBlack);
	Figure* bishopWL = new Figure(Figure::bishop, Figure::eWhite);
	Figure* bishopWR = new Figure(Figure::bishop, Figure::eWhite);
	figures[7][2] = bishopBL;
	figures[7][5] = bishopBR;
	figures[0][2] = bishopWL;
	figures[0][5] = bishopWR;

	Figure* rookBL = new Figure(Figure::rook, Figure::eBlack);
	Figure* rookBR = new Figure(Figure::rook, Figure::eBlack);
	Figure* rookWL = new Figure(Figure::rook, Figure::eWhite);
	Figure* rookWR = new Figure(Figure::rook, Figure::eWhite);
	figures[7][0] = rookBL;
	figures[7][7] = rookBR;
	figures[0][0] = rookWL;
	figures[0][7] = rookWR;

	Figure* kingB = new Figure(Figure::king, Figure::eBlack);
	Figure* kingW = new Figure(Figure::king, Figure::eWhite);
	figures[7][4] = kingB;
	figures[0][4] = kingW;

	Figure* queenB = new Figure(Figure::queen, Figure::eBlack);
	Figure* queenW = new Figure(Figure::queen, Figure::eWhite);
	figures[7][3] = queenB;
	figures[0][3] = queenW;
}

void ChessBoard::Paint() const
{
	cout << "            White" << endl;
	cout << "   a  b  c  d  e  f  g  h  " << endl;
	//-----
	cout << " " << (char)0xC9;
	for (int i = 0; i < 7; i++) {
		cout << (char)0xCD << (char)0xCD << (char)0xD1;
	}
	cout << (char)0xCD << (char)0xCD << (char)0xBB << endl;
	//-----
	int cnt = 1;
	for (int i = 0; i < 8; i++) {
		cout << cnt << (char)0xBA;
		for (int j = 0; j < 8; j++) {
			char color = ' ';
			char name = ' ';
			if (figures[i][j]) {
				if (figures[i][j]->getColor() == Figure::eBlack) color = 'B';
				if (figures[i][j]->getColor() == Figure::eWhite) color = 'W';
				if (figures[i][j]->getName() == Figure::rook) name = 'R';
				if (figures[i][j]->getName() == Figure::kNight) name = 'N';
				if (figures[i][j]->getName() == Figure::bishop) name = 'B';
				if (figures[i][j]->getName() == Figure::queen) name = 'Q';
				if (figures[i][j]->getName() == Figure::king) name = 'K';
				if (figures[i][j]->getName() == Figure::pawn) name = 'P';
			}
			cout << color << name;
			if (j < 7) cout << (char)0xB3;
		}
		cout << (char)0xBA << cnt++ << endl;
		if (i < 7) {
			cout << " " << (char)0xC7;
			for (int j = 0; j < 8; j++) {
				cout << (char)0xC4 << (char)0xC4;
				if (j < 7) cout << (char)0xC5;
			}
			cout << (char)0xB6;
			cout << endl;
		}
	}
	//-----
	cout << " " << (char)0xC8;
	for (int i = 0; i < 7; i++) {
		cout << (char)0xCD << (char)0xCD << (char)0xCF;
	}
	cout << (char)0xCD << (char)0xCD << (char)0xBC << endl;
	//-----
	cout << "   a  b  c  d  e  f  g  h  " << endl;
	cout << "            Black" << endl;
}

void ChessBoard::Clean()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (figures[i][j] != nullptr) {
				delete figures[i][j];
				figures[i][j] = nullptr;
			}
		}
	}
}

void ChessBoard::Move(int x1, int y1, int x2, int y2)
{
	x1_ = x1;
	y1_ = y1;
	x2_ = x2;
	y2_ = y2;
	figure_ = figures[y2][x2];
	figures[y2][x2] = figures[y1][x1];
	figures[y1][x1] = nullptr;
}

void ChessBoard::MoveBack()
{
	//Move(x2_, y2_, x1_, y1_);
	figures[y1_][x1_] = figures[y2_][x2_];
	figures[y2_][x2_] = figure_;
}

bool ChessBoard::isFreeSpaceBetween(int x1, int y1, int x2, int y2) const
{
	if (x1 == x2) {
		int a = y1 < y2 ? y1 : y2;
		int b = y1 > y2 ? y1 : y2;
		for (int i = a+1; i < b; i++) {
			if (getFigure(x1, i)) return false;
		}
		return true;
	}
	if (y1 == y2) {
		int a = x1 < x2 ? x1 : x2;
		int b = x1 > x2 ? x1 : x2;
		for (int j = a + 1; j < b; j++) {
			if (getFigure(j, y1)) return false;
		}
		return true;
	}

	if (abs(x1 - x2) == abs(y1 - y2)) {
		int dx = (x2 - x1) > 0 ? 1 : -1;
		int dy = (y2 - y1) > 0 ? 1 : -1;
		int i = y1+dy;
		int j = x1+dx;
		while (i != y2) {
			if (getFigure(j, i)) return false;
			i += dy;
			j += dx;
		}
		return true;
	}
	return false;
}

Position ChessBoard::getWhiteKingPosition() const
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = getFigure(j, i);
			if (figure != nullptr) {
				if (figure->getName() == Figure::king && figure->getColor() == Figure::eWhite) {
					return { j,i };
				}
			}
		}
	}
	return {-1,-1};
}

Position ChessBoard::getBlackKingPosition() const
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = getFigure(j, i);
			if (figure != nullptr) {
				if (figure->getName() == Figure::king && figure->getColor() == Figure::eBlack) {
					return { j,i };
				}
			}
		}
	}
	return { -1,-1 };
}

Figure* ChessBoard::getFigure(int x, int y) const
{
	return figures[y][x];
}

void ChessBoard::setFigure(int x, int y, Figure* figure)
{
	figures[y][x] = figure;
}
