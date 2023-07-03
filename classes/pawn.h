#if !defined(__PAWN_H)
#define __PAWN_H
#include <string>

class Pawn {
protected:
	int posX;
	int posY;
	bool isInGame;
public:
	std::string color;
	Pawn();
	Pawn(int  posY, int posX, std::string color);
	int getPosX();
	int getPosY();
	bool getStatus();
	void choose();
	void changePosition(int, int);
	void changeStatus();
};
class Crown : public Pawn {

public:
	Crown();
	Crown(int posY, int posX, std::string color);
	void born(int, int);
};
#endif
