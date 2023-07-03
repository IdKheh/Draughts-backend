#if !defined(__BOARD_H)
#define __BOARD_H
#include <string>

class Board {
private:
	int layout[8][8];
public:
	Board();
	void show();
	void update(int, int, int);
	int getBoard(int, int);
	int checkMoves(int, int, std::string);
	int checkCapture(int, int, std::string);

	bool checkMovesCrown(int, int, int, int); // funkcja sprawdza czy mozemy wykonac dany ruch, a nie jakie mamy mozliwosci
	int searchCaptures(int, int, std::string color);
};

#endif
