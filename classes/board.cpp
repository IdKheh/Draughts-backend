#include "board.h"
#include <iostream>

// W TABLICY:
// -1 -> pole wylaczone z gry, 0 -> puste pole, 1 -> bialy pionek, 2 -> czarny pionek
Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (((i == 0 || i == 2) && j % 2 == 1) || (i == 1 && j % 2 == 0)) {
				this->layout[i][j] = 2;
			}
			else if (((i == 5 || i == 7) && j % 2 == 0) || (i == 6 && j % 2 == 1)) {
				this->layout[i][j] = 1;
			}
			else if ((i == 3 && j % 2 == 0) || (i == 4 && j % 2 == 1)) {
				this->layout[i][j] = 0;
			}
			else {
				this->layout[i][j] = -1;
			}
		}
	}
}

int Board::getBoard(int y, int x)
{
	return layout[y][x];
}

// WYSWIETLANIE W KONSOLI:
// O -> bialy pionek, X -> czarny pionek, W -> czarna damka, M -> biała damka
void Board::show() {
	std::cout << "Aktualny stan planszy:\n" << "    0   1   2   3   4   5   6   7\n";
	for (int i = 0; i < 8; i++) {
		std::cout <<"   ________________________________\n";
		std::cout << i << " |";
		for (int j = 0; j < 8; j++) {
			switch (layout[i][j]) {
				case -1:
					std::cout << "---";
					break;
				case 0: 
					std::cout << "   ";
					break;
				case 1:
					std::cout << " O ";
					break;
				case 2:
					std::cout << " X ";
					break;
				case 3:
					std::cout << " M ";
					break;
				case 4:
					std::cout << " W ";
					break;
			}
			std::cout << "|";
			if (j == 7) {
				std::cout << "\n";
			}
		}
	}
}

// 0 -> brak ruch�w, 1 -> tylko ruch w lewo, 2 -> tylko ruch w prawo, 3 -> ruch w lewo albo w prawo,  
int Board::checkMoves(int x, int y, std::string color) {
	int moves = 0;
	if (color == "white") {
		if (y - 1 >= 0 && x - 1 >= 0) {
			if (layout[y - 1][x - 1] == 0) {
				moves = 1;
			}
		}
		if (y - 1 >= 0 && x + 1 < 8) {
			if (layout[y - 1][x + 1] == 0) {
				moves = 2;
			}
		}
		if (y - 1 >= 0 && x - 1 >= 0 && x + 1 < 8) {
			if (layout[y - 1][x + 1] == 0 && layout[y - 1][x - 1] == 0) {
				moves = 3;
			}
		}
	}
	if (color == "black") {
		if (y + 1 < 8 && x - 1 >= 0) {
			if (layout[y + 1][x - 1] == 0) {
				moves = 1;
			}
		}
		if (y + 1 < 8 && x + 1 < 8) {
			if (layout[y + 1][x + 1] == 0) {
				moves = 2;
			}
		}
		if (y + 1 < 8 && x - 1 >= 0 && x + 1 < 8) {
			if (layout[y + 1][x + 1] == 0 && layout[y + 1][x - 1] == 0) {
				moves = 3;
			}
		}
	}
	return moves;
}
//  analogicznie 0 -> brak, 1 mozliwosc bicia: 1 -> lewo dół, 2 -> lewo góra, 3 -> prawo dół, 4 -> prawo góra,
//	2 mozliwosci bicia: 5-> gora, 6 -> dol, 7-> prawo, 8-> lewo 
//	3 mozliwosci bicia: 9 -> gora dol prawo,  10 -> dol gora lewo, 11 ->prawo dol lewo, 12-> lewo gora prawo
int Board::checkCapture(int x, int y, std::string color) {
	int capture = 0, enemy, enemyCrown;
	if (color == "black")
	{
		enemy = 1;
		enemyCrown = 3;
	}
	else
	{
		enemy = 2;
		enemyCrown = 4;
	}
	// 1 mozliwosc bicia
		if (y + 2 <8 && x - 2 >= 0) {
			if (((layout[y + 1][x - 1] == enemy)|| (layout[y + 1][x - 1] == enemyCrown))&&(layout[y + 2][x - 2] == 0)) {
				capture = 1;
			}
		}
		if (y - 2 >= 0 && x - 2 >= 0) {
			if (((layout[y - 1][x - 1] == enemy)||(layout[y - 1][x - 1] == enemyCrown))&&(layout[y - 2][x - 2] == 0)) {
				capture = 2;
			}
		}
		if (y + 2 < 8 && x + 2 < 8) {
			if (((layout[y + 1][x + 1] == enemy)|| (layout[y + 1][x + 1] == enemyCrown))&&(layout[y + 2][x + 2] == 0)) {
				capture = 3;
			}
		}
		if (y - 2 >= 0 && x + 2 < 8) {
			if (((layout[y - 1][x + 1] == enemy)|| (layout[y - 1][x + 1] == enemyCrown))&&(layout[y - 2][x + 2] == 0)) {
				capture = 4;
			}
		}
	// 2 mozliwosc bicia:
		if ((y - 2 >= 0 && x - 2 >= 0)&&(y - 2 >= 0 && x + 2 < 8)) {
			if (((layout[y - 1][x - 1] == enemy)||(layout[y - 1][x - 1] == enemyCrown))&&(layout[y - 2][x - 2] == 0)&&((layout[y - 1][x + 1] == enemy)|| (layout[y - 1][x + 1] == enemyCrown))&&(layout[y - 2][x + 2] == 0)) {
				capture = 5;
			}
		}
		if ((y + 2 < 8 && x - 2 >= 0) && (y + 2 < 8 && x + 2 < 8)) {
			if (((layout[y + 1][x - 1] == enemy)||(layout[y + 1][x - 1] == enemyCrown))&&(layout[y + 2][x - 2] == 0) && ((layout[y + 1][x + 1] == enemy)|| (layout[y + 1][x + 1] == enemyCrown)) && (layout[y + 2][x + 2] == 0)) {
				capture = 6;
			}
		}
		if ((y + 2 < 8 && x + 2 < 8) && (y - 2 >= 0 && x + 2 < 8)) {
			if (((layout[y + 1][x + 1] == enemy)||(layout[y + 1][x + 1] == enemyCrown)) && (layout[y + 2][x + 2] == 0) && ((layout[y - 1][x + 1] == enemy)|| (layout[y - 1][x + 1] == enemyCrown)) && (layout[y - 2][x + 2] == 0)) {
				capture = 7;
			}
		}
		if ((y + 2 < 8 && x - 2 >= 0) && ((y - 2 >= 0 && x - 2 >= 0))) {
			if (((layout[y + 1][x - 1] == enemy)|| (layout[y + 1][x - 1] == enemyCrown)) && (layout[y + 2][x - 2] == 0) && ((layout[y - 1][x - 1] == enemy)|| (layout[y - 1][x - 1] == enemyCrown)) && (layout[y - 2][x - 2] == 0)) {
				capture = 8;
			}
		}
		if ((y - 2 >= 0 && x - 2 >= 0) && (y + 2 < 8 && x + 2 < 8)) {
			if (((layout[y - 1][x - 1] == enemy) || (layout[y - 1][x - 1] == enemyCrown)) && (layout[y - 2][x - 2] == 0) && ((layout[y + 1][x + 1] == enemy) || (layout[y + 1][x + 1] == enemyCrown)) && (layout[y + 2][x + 2] == 0)) {
				capture = 13;
			}
		}
		if ((y + 2 < 8 && x - 2 >= 0) && (y - 2 <= 0 && x + 2 < 8)) {
			if (((layout[y + 1][x - 1] == enemy) || (layout[y + 1][x - 1] == enemyCrown)) && (layout[y + 2][x - 2] == 0) && ((layout[y - 1][x + 1] == enemy) || (layout[y - 1][x + 1] == enemyCrown)) && (layout[y - 2][x + 2] == 0)) {
				capture = 14;
			}
		}
	// 3 mozliwosci bicia:
		if ((y + 2 <8 && x - 2 >= 0)&&(y - 2 >= 0 && x - 2 >= 0)&&(y + 2 < 8 && x + 2 < 8)) {
			if (((layout[y + 1][x - 1] == enemy)|| (layout[y + 1][x - 1] == enemyCrown))&&(layout[y + 2][x - 2] == 0)&&((layout[y - 1][x - 1] == enemy)|| (layout[y - 1][x - 1] == enemyCrown))&&(layout[y - 2][x - 2] == 0)&&((layout[y + 1][x + 1] == enemy)|| (layout[y + 1][x + 1] == enemyCrown))&&(layout[y + 2][x + 2] == 0)) {
				capture = 9;
			}
		}
		if ((y + 2 < 8 && x + 2 < 8)&&(y - 2 >= 0 && x + 2 < 8)&&(y - 2 >= 0 && x - 2 >= 0)) {
			if (((layout[y + 1][x + 1] == enemy)|| (layout[y + 1][x + 1] == enemyCrown))&&(layout[y + 2][x + 2] == 0)&&((layout[y - 1][x + 1] == enemy)|| (layout[y - 1][x + 1] == enemyCrown))&&(layout[y - 2][x + 2] == 0)&&((layout[y - 1][x - 1] == enemy)||(layout[y - 1][x - 1] == enemyCrown))&&(layout[y - 2][x - 2] == 0)) {
				capture = 10;
			}
		}
		if ((y + 2 <8 && x - 2 >= 0)&&(y + 2 < 8 && x + 2 < 8)&&(y - 2 >= 0 && x + 2 < 8)) {
			if (((layout[y + 1][x - 1] == enemy)||(layout[y + 1][x - 1] == enemyCrown))&&(layout[y + 2][x - 2] == 0)&&((layout[y + 1][x + 1] == enemy)|| (layout[y + 1][x + 1] == enemyCrown))&&(layout[y + 2][x + 2] == 0)&&((layout[y - 1][x + 1] == enemy)||(layout[y - 1][x + 1] == enemyCrown))&&(layout[y - 2][x + 2] == 0)) {
				capture = 11;
			}
		}
		if ((y - 2 >= 0 && x - 2 >= 0)&&(y - 2 >= 0 && x + 2 < 8)&&(y + 2 <8 && x - 2 >= 0)) {
			if (((layout[y - 1][x - 1] == enemy)|| (layout[y - 1][x - 1] == enemyCrown))&&(layout[y - 2][x - 2] == 0)&&((layout[y - 1][x + 1] == enemy)||(layout[y - 1][x + 1] == enemyCrown))&&(layout[y - 2][x + 2] == 0)&&((layout[y + 1][x - 1] == enemy)|| (layout[y + 1][x - 1] == enemyCrown))&&(layout[y + 2][x - 2] == 0)) {
				capture = 12;
			}
		}
	return capture;
}

void Board::update(int posY, int posX, int change) {
	this->layout[posY][posX] = change;
}

// funkcja sprawdza czy istnieje dany ruch na dana pozycje  
bool Board::checkMovesCrown(int x_crown, int y_crown, int x_destination, int y_destination) {
	bool moves = false;
	
		if (y_destination >= 0 && x_destination >= 0 && y_destination<y_crown && x_destination < x_crown) {
			int x = x_crown;
			int y = y_crown;
			while (x > x_destination && y > y_destination) {
				if (layout[y][x] != 0) {
					moves = false;
					return moves;
				}
				else{
					y -= 1;
					x -= 1;
				}
			}
			moves = true;
		}
		if (y_destination < 8 && x_destination >= 0 && y_destination > y_crown && x_destination < x_crown) {
			int x = x_crown;
			int y = y_crown;
			while (x > x_destination && y > y_destination) {
				if (layout[y][x] != 0) {
					moves = false;
					return moves;
				}
				else{
					y += 1;
					x -= 1;
				}
			}
			moves = true;
		}
		if (y_destination >= 0 && x_destination < 8 && y_destination < y_crown && x_destination > x_crown) {
			int x = x_crown;
			int y = y_crown;
			while (x > x_destination && y > y_destination) {
				if (layout[y][x] != 0) {
					moves = false;
					return moves;
				}
				else{
					y -= 1;
					x += 1;
				}
			}
			moves = true;
		}
		if (y_destination < 8 && x_destination < 8 && y_destination > y_crown && x_destination > x_crown) {
			int x = x_crown;
			int y = y_crown;
			while (x > x_destination && y > y_destination) {
				if (layout[y][x] != 0) {
					moves = false;
					return moves;
				}
				else{
					y += 1;
					x += 1;
				}
			}
			moves = true;
		}	
	return moves;
}

int Board::searchCaptures(int yCrown, int xCrown, std::string color) // rozpisane binarnie 
{
	int enemyPawn, enemyCrown, moves = 0, x = xCrown, y = yCrown;
	if (color == "black") {
		enemyPawn = 1;
		enemyCrown = 3;
	}
	else {
		enemyPawn = 2;
		enemyCrown = 4;
	}

	x = xCrown;
	y = yCrown;
	while (x >= 0 && y >= 0) {
		if (layout[y + 1][x + 1] == 0 && (layout[y][x] == enemyCrown || layout[y][x] == enemyPawn) && layout[y - 1][x - 1] == 0)
		{
			moves += 1;
			break;
		}
		else {
			y -= 1;
			x -= 1;
		}
	}

	x = xCrown;
	y = yCrown;
	while (x >= 0 && y < 8) {
		if (layout[y - 1][x + 1] == 0 && (layout[y][x] == enemyCrown || layout[y][x] == enemyPawn) && layout[y + 1][x - 1] == 0)
		{
			moves += 2;
			break;
		}
		else {
			y += 1;
			x -= 1;
		}
	}

	x = xCrown;
	y = yCrown;
	while (x < 8 && y >= 0) {
		if (layout[y + 1][x - 1] == 0 && (layout[y][x] == enemyCrown || layout[y][x] == enemyPawn) && layout[y - 1][x + 1] == 0)
		{
			moves += 4;
			break;
		}
		else {
			y -= 1;
			x += 1;
		}
	}

	x = xCrown;
	y = yCrown;
	while (x < 8 && y < 8) {
		if (layout[y - 1][x - 1] == 0 && (layout[y][x] == enemyCrown || layout[y][x] == enemyPawn) && layout[y + 1][x + 1] == 0)
		{
			moves += 8;
			break;
		}
		else {
			y += 1;
			x += 1;
		}
	}
	return moves;
}