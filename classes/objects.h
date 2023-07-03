#if !defined(__OBJECTS_H)
#define __OBJECTS_H
#include "classes/board.h"
#include "classes/pawn.h"
#include "classes/player.h"

//Generowanie planszy i pionków
Board board;
Pawn blackPawns[12] = {
    Pawn(0,1,"black"),
    Pawn(0,3,"black"),
    Pawn(0,5,"black"),
    Pawn(0,7,"black"),
    Pawn(1,0,"black"),
    Pawn(1,2,"black"),
    Pawn(1,4,"black"),
    Pawn(1,6,"black"),
    Pawn(2,1,"black"),
    Pawn(2,3,"black"),
    Pawn(2,5,"black"),
    Pawn(2,7,"black")
};
Pawn whitePawns[12] = {
    Pawn(5,0,"white"),
    Pawn(5,2,"white"),
    Pawn(5,4,"white"),
    Pawn(5,6,"white"),
    Pawn(6,1,"white"),
    Pawn(6,3,"white"),
    Pawn(6,5,"white"),
    Pawn(6,7,"white"),
    Pawn(7,0,"white"),
    Pawn(7,2,"white"),
    Pawn(7,4,"white"),
    Pawn(7,6,"white")
};

Crown blackCrowns[12];
Crown whiteCrowns[12];

//tworzenie graczy
Player player1;
Player player2;

#endif
