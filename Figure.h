#pragma once
class Figure{
  
public:
	enum Color { eBlack, eWhite };
	enum Name { pawn, bishop, kNight, rook, queen, king };
	Figure(Name name, Color color);
	Color getColor() const;
	Name getName() const;
  
private:
	Color color;
	Name name;
  
};
