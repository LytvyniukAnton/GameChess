#include "Game.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Game::Game()
{
	Reset();
}

//e2-e4
void Game::OneMove()
{
	cout << "Write \"Help\" if you need." << endl;
	cout << "What is your move?" << endl;
	string color = cnt % 2 == 0 ? " White" : " Black";
	cout << cnt << color <<" ==> ";
	char s[10] = {0};
	cin >> s; 
	if (strcmp(s, "Start") == 0 || strcmp(s, "Restart") == 0) {
		Reset();
		Show();
	}
	else if (strcmp(s, "Help") == 0) {
		Help();
	}
	else if (strcmp(s, "Save") == 0) {
		Save();
	}
	else if (strcmp(s, "Load") == 0) {
		Load();
	}
	else {
		int x1 = s[0] - 'a';
		int y1 = s[1] - '1';
		int x2 = s[3] - 'a';
		int y2 = s[4] - '1';

		//Cheking if this move is permitted.
		Figure* figure = board.getFigure(x1, y1);
		if ((figure->getColor() == Figure::eWhite && cnt % 2 == 0) || (figure->getColor() == Figure::eBlack && cnt % 2 != 0)) {
			bool isPermitted = getPermishen(x1, y1, x2, y2);
			if (isPermitted) {
				board.Move(x1, y1, x2, y2);
				cnt++;
			}
		}
	}
}

void Game::Reset()
{
	cnt = 0;
	board.Init();
}

void Game::Show() const
{
	board.Paint();
}

void Game::Save() const
{
	char fileName[200];
	cout << "Enter file name: ";
	cin >> fileName;
	FILE* f; 
	fopen_s(&f, fileName, "wt");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = board.getFigure(j, i);
			if (figure == 0) {
				fputs("*\n", f);
			}
			else {
				Figure::Color color = figure->getColor();
				Figure::Name name = figure->getName();
				if (color == Figure::eWhite) {
					fprintf(f, "White ");
				}
				else {
					fprintf(f, "Black ");
				}
				switch (name)
				{
				case Figure::pawn:
					fprintf(f, "pawn ");
					break;
				case Figure::bishop:
					fprintf(f, "bishop ");
					break;
				case Figure::kNight:
					fprintf(f, "kNight ");
					break;
				case Figure::rook:
					fprintf(f, "rook ");
					break;
				case Figure::queen:
					fprintf(f, "queen ");
					break;
				case Figure::king:
					fprintf(f, "king ");
					break;
				default:
					break;
				}
				fputs("\n", f);
			}
		}
	}
	fprintf(f, "%d", cnt);
	fputs("\n", f);
	fclose(f);
}

void Game::Load()
{
	char fileName[200];
	cout << "Enter file name: ";
	cin >> fileName;
	FILE* f;
	fopen_s(&f, fileName, "rt");
	board.Clean();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			char s[100];
			fgets(s, 100, f);
			if (s[0] != '*') {
				char* context = NULL;
				char* color = strtok_s(s, " ", &context);
				char* name = strtok_s(NULL, " ", &context);
				Figure::Color color_ = Figure::eBlack;
				if (strcmp(color, "White") == 0) {
					color_ = Figure::eWhite;
				}
				Figure::Name name_ = Figure::pawn;
				if (strcmp(name, "rook") == 0) {
					name_ = Figure::rook;
				}
				if (strcmp(name, "bishop") == 0) {
					name_ = Figure::bishop;
				}
				if (strcmp(name, "kNight") == 0) {
					name_ = Figure::kNight;
				}
				if (strcmp(name, "king") == 0) {
					name_ = Figure::king;
				}
				if (strcmp(name, "queen") == 0) {
					name_ = Figure::queen;
				}
				board.setFigure(j, i, new Figure(name_, color_));
			}
		}
	}
	char s[100];
	fgets(s, 100, f);
	cnt = atoi(s);
	fclose(f);
}

void Game::Help() const
{
	cout << endl;
	cout << "You have commands: Save, Load." << endl;
	cout << "Example for \"Save\" -->  " << endl;
	cout << "After your move write --> " << endl; 
	cout <<	"\"Save\" and you will see-->" << endl;
	cout << "Enter your file name:" << endl;
	cout <<	"Write for example \"Chess.txt\"" << endl;
}

bool Game::isСheckForWhite() const
{
	Position p = board.getWhiteKingPosition();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = board.getFigure(j, i);
			if (figure != nullptr) {
				if (getPermishen(j, i, p.x, p.y)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::isСheckForBlack() const
{
	Position p = board.getBlackKingPosition();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = board.getFigure(j, i);
			if (figure != nullptr) {
				if (getPermishen(j, i, p.x, p.y)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::isMateForWhite() 
{
	if (!isСheckForWhite()) return false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = board.getFigure(j, i);
			if (figure != nullptr) {
				if (figure->getColor() == figure->eWhite) {
					for (int y = 0; y < 8; y++) {
						for (int x = 0; x < 8; x++) {
							if (getPermishen(j, i, x, y)) {
								board.Move(j, i, x, y);
								bool check = isСheckForWhite();
								board.MoveBack();
								if (!check) return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool Game::isMateForBlack()
{
	if (!isСheckForBlack()) return false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Figure* figure = board.getFigure(j, i);
			if (figure != nullptr) {
				if (figure->getColor() == figure->eBlack) {
					for (int y = 0; y < 8; y++) {
						for (int x = 0; x < 8; x++) {
							if (getPermishen(j, i, x, y)) {
								board.Move(j, i, x, y);
								bool check = isСheckForBlack();
								board.MoveBack();
								if (!check) return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

void Game::CancelLastMove()
{
	board.MoveBack();
	cnt--;
}

string Game::getLastColor() const
{
	if (cnt % 2 != 0) return "White";
	return "Black";
}

bool Game::getPermishen(int x1, int y1, int x2, int y2) const
{
	Figure* figure = board.getFigure(x1, y1);
	Figure::Color color = figure->getColor();
	Figure::Name name = figure->getName();
	Figure* figure2 = board.getFigure(x2, y2);
	if (name == Figure::pawn) {
		if (color == Figure::eBlack) {
			bool aHead = x1 == x2 && (y2 == y1 - 1 || y1 == 6 && y2 == y1 - 2) && y2 > 0 && board.getFigure(x2, y2) == nullptr;
			bool strikeLeft = x2 - x1 == -1 && y2 - y1 == -1 && figure2 != nullptr && figure2->getColor() != color;
			bool strikeRight = x2 - x1 == 1 && y2 - y1 == -1 && figure2 != nullptr && figure2->getColor() != color;
			return aHead || strikeLeft || strikeRight;
		}
		if (color == Figure::eWhite) {
			bool aHead = x1 == x2 && (y2 == y1 + 1 || y1 == 1 && y2 == y1 + 2) && y2 < 7 && board.getFigure(x2, y2) == nullptr;
			bool strikeLeft = x2 - x1 == 1 && y2 - y1 == 1 && figure2 != nullptr && figure2->getColor() != color;
			bool strikeRight = x2 - x1 == -1 && y2 - y1 == 1 && figure2 != nullptr && figure2->getColor() != color;
			return aHead || strikeLeft || strikeRight;
		}
	}
	if (name == Figure::queen) {
		bool ok = true;
		if (figure2 != nullptr && figure2->getColor() == color) ok = false;
		bool freeSpace = board.isFreeSpaceBetween(x1, y1, x2, y2);
		return (abs(x1 - x2) == abs(y1 - y2) || (x1 == x2 || y1 == y2)) && ok && freeSpace;
	}
	if (name == Figure::bishop) {
		bool ok = true;
		if (figure2 != nullptr && figure2->getColor() == color) ok = false;
		bool freeSpace = board.isFreeSpaceBetween(x1, y1, x2, y2);
		return (abs(x1 - x2) == abs(y1 - y2)) && ok && freeSpace;
	}
	if (name == Figure::king) {
		bool ok = true;
		if (figure2 != nullptr && figure2->getColor() == color) ok = false;
		bool freeSpace = board.isFreeSpaceBetween(x1, y1, x2, y2);
		return abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1 && ok && freeSpace;
	}
	if (name == Figure::kNight) {
		bool ok = true;
		if (figure2 != nullptr && figure2->getColor() == color) ok = false;
		return  abs(x1 - x2) == 1 && abs(y1 - y2) == 2 || abs(x1 - x2) == 2 && abs(y1 - y2) == 1 && ok ; 
	}
	if (name == Figure::rook) {
		bool ok = true;
		if (figure2 != nullptr && figure2->getColor() == color) ok = false;
		bool freeSpace = board.isFreeSpaceBetween(x1, y1, x2, y2);
		return (x1 == x2 || y1 == y2) && ok && freeSpace;
	}
	return false;
}
