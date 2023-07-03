#include "pawn.h"
#include <iostream>

Pawn::Pawn() {
	this->posX = 0;
	this->posY = 0;
	this->color = "";
	this->isInGame = false;
}

Pawn::Pawn(int posY, int posX, std::string color) {
	this->posX = posX;
	this->posY = posY;
	this->color = color;
	this->isInGame = true;
}

int Pawn::getPosX() {
	return this->posX;
}

int Pawn::getPosY() {
	return this->posY;
}

bool Pawn::getStatus() {
	return this->isInGame;
}

void Pawn::choose() {
	std::cout << "Wybrano pionek na polu: [" << this->posX << "," << this->posY << "]\n";
}

void Pawn::changePosition(int newY, int newX) {
	this->posX = newX;
	this->posY = newY;
}

void Pawn::changeStatus(){
	this->isInGame= false;
}

Crown::Crown() {
	this->posX = 0;
	this->posY = 0;
	this->color = "";
	this->isInGame = false;
}

Crown::Crown(int posY, int posX, std::string color) {
	this->posX = posX;
	this->posY = posY;
	this->color = color;
	this->isInGame = false;
}

void Crown::born(int newY, int newX){
	this->posX = newX;
	this->posY = newY;
	this->isInGame = true;
}