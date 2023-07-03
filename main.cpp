#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "classes/board.h"
#include "classes/pawn.h"
#include "classes/player.h"
#include "classes/objects.h"

// 0=false -> ruch białych, 1=true -> ruch czarnych
bool turnOf = false;
int how_many_blackCrowns = 0;
int how_many_whiteCrowns = 0;

//zapis do pliku statystyk (data, nicki graczy i kto wygrał)
std::ofstream statsFile;
std::ifstream statsFileInput;

char* getTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

void rulesOfGame()
{
    std::cout << "\t\tZASADY GRY\n --------------------------------------------\n 1) Pionki poruszaja sie tylko do przodu.\n";
    std::cout << " 2) Pionki bija do przodu oraz do tylu po skosie.\n 3) Istnieja bicia wielokrotne.\n 4) Gdy pionek dotrze do przeciwnej krawedzi, to pionek staje sie damka.\n";
    std::cout << " 5) Damki moga poruszac sie do przodu oraz do tylu o dowolna ilosc pol.\n";
    std::cout << " 6) Gra skonczy sie jesli jeden z graczy zbije wszystkie pionki drugiego lub gracz nie bedzie mial mozliwosci ruchu.\n\n\n";
}

void gameStart() {
    int menuOption = 0;
    statsFile.open("stats/results.txt", std::ios::app);
    statsFileInput.open("stats/results.txt");
    std::string menu = "------------------------\nMENU:\n1. Rozpocznij gre\n2. Zasady gry\n3. Wyniki poprzednich gier\n------------------------\n";
    std::cout << menu;
    while (menuOption != 1) {
        std::cin >> menuOption;
        if (menuOption == 2) {
            rulesOfGame();
            std::cout << menu;
        }
        if (menuOption == 3) {
            std::string stats;
            int counter = 0;
            while (statsFileInput >> stats) {
                std::cout << stats <<" ";
                counter++;
                if (counter == 10) {
                    std::cout << "\n";
                    counter = 0;
                }
            }
            std::cout << "\n" << menu;
        }
    }
    std::string username;
    std::cout << "Podaj imie pierwszego gracza: ";
    std::cin >> username;
    player1.setName(username);
    std::cout << "Podaj imie drugiego gracza: ";
    std::cin >> username;
    player2.setName(username);
    board.show();
}

void capture(std::string color, int x_zbitego, int y_zbitego)
{
    if(color=="black")
        for(int j=0;j<12;j++)   
            if(whitePawns[j].getPosX() == x_zbitego && whitePawns[j].getPosY() == y_zbitego && whitePawns[j].getStatus()== true)
                {
                    whitePawns[j].changeStatus();
                    board.update(whitePawns[j].getPosY(), whitePawns[j].getPosX(), 0);
                }
        for (int j = 0; j < 12; j++)
            if (whiteCrowns[j].getPosX() == x_zbitego && whiteCrowns[j].getPosY() == y_zbitego)
            {
                board.update(whiteCrowns[j].getPosY(), whiteCrowns[j].getPosX(), 0);
            }
        
    if (color == "white")
        for(int j=0;j<12;j++)   
            if(blackPawns[j].getPosX() == x_zbitego && blackPawns[j].getPosY() == y_zbitego && blackPawns[j].getStatus()== true)
            {
                blackPawns[j].changeStatus();
                board.update(blackPawns[j].getPosY(), blackPawns[j].getPosX(), 0);
            }
        for (int j = 0; j < 12; j++)
            if (blackCrowns[j].getPosX() == x_zbitego && blackCrowns[j].getPosY() == y_zbitego)
            {
                board.update(blackCrowns[j].getPosY(), blackCrowns[j].getPosX(), 0);
            }
}
void captureCrown(std::string color, int x_zbitego, int y_zbitego)
{
    if (color == "black")
        for (int j = 0; j < 12; j++)
            if (whiteCrowns[j].getPosX() == x_zbitego && whiteCrowns[j].getPosY() == y_zbitego && whiteCrowns[j].getStatus() == true)
            {
                whiteCrowns[j].changeStatus();
                board.update(whiteCrowns[j].getPosY(), whiteCrowns[j].getPosX(), 0);
            }

    if (color == "white")
        for (int j = 0; j < 12; j++)
            if (blackCrowns[j].getPosX() == x_zbitego && blackCrowns[j].getPosY() == y_zbitego && blackCrowns[j].getStatus() == true)
            {
                blackCrowns[j].changeStatus();
                board.update(blackCrowns[j].getPosY(), blackCrowns[j].getPosX(), 0);
            }
}

void captureMove(int i, std::string color, int bicie) //by odciazyc troche funkcje turn
{
    int moveNumber = 0;
    std::cout << "Mozliwe bicie pionka na polu: 1 -> [";
    switch (bicie)
    {
        case 1:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 2:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 3:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 4:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 5:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 6:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                break;
            }
        case 7:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 8:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 13:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 14:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 9:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "3 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                std::cout << "3 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 10:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "3 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "3 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "3 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 11:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                std::cout << "3 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                std::cout << "3 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        case 12:
            if (color == "black") {
                std::cout << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << blackPawns[i].getPosX() + 1 << ", " << blackPawns[i].getPosY() - 1 << "]\n";
                std::cout << "3 -> [" << blackPawns[i].getPosX() - 1 << ", " << blackPawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
            if (color == "white") {
                std::cout << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                std::cout << "2 -> [" << whitePawns[i].getPosX() + 1 << ", " << whitePawns[i].getPosY() - 1 << "]\n";
                std::cout << "3 -> [" << whitePawns[i].getPosX() - 1 << ", " << whitePawns[i].getPosY() + 1 << "]\n";
                while (moveNumber != 1 && moveNumber != 2 && moveNumber != 3) {
                    std::cin >> moveNumber;
                }
                if (moveNumber == 1) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                if (moveNumber == 3) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 2);
                    board.show();
                }
                break;
            }
        default:
            break;
    }
}

void MovesCaptureCrown(int bicie, int i, int y_des, int x_des, std::string color) // rozpisane binarnie 
{
    int enemyPawn, enemyCrown, moves = 0;
    if (color == "black") {
        enemyPawn = 1;
        enemyCrown = 3;
        int xCrown = blackCrowns[i].getPosX();
        int yCrown = blackCrowns[i].getPosY();
        int x = blackCrowns[i].getPosX();
        int y = blackCrowns[i].getPosY();
        switch (bicie) {
        case 1:
            while (x_des <= x && x_des < xCrown && y_des <= y && y_des < yCrown)
            {
                if (board.getBoard(y - 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x + 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x - 1, y - 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y -= 1;
                }
            }
            break;

        case 2:
            while (x_des <= x && x_des<xCrown && y_des > y && y >= yCrown)
            {
                if (board.getBoard(y + 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x + 1) == 0)
                {

                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x - 1, y + 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y += 1;
                }
            }
            break;
        case 3:
            while (y_des <= y && y_des<yCrown && x_des >= x && x_des>xCrown)
            {
                if (board.getBoard(y - 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x - 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x + 1, y - 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y -= 1;
                }
            }
            break;
        case 4:
            while (x_des >= x && x_des > xCrown && y_des >= y && y_des > yCrown)
            {
                if (board.getBoard(y + 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x - 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x + 1, y + 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y += 1;
                }
            }
            break;

        default:
            break;
        }
    }
    else {
        enemyPawn = 2;
        enemyCrown = 4;
        int xCrown = whiteCrowns[i].getPosX();
        int yCrown = whiteCrowns[i].getPosY();
        int x = whiteCrowns[i].getPosX();
        int y = whiteCrowns[i].getPosY();
        switch (bicie) {
        case 1:
            while (x_des <= x && x_des < xCrown && y_des <= y && y_des < yCrown)
            {
                if (board.getBoard(y - 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x + 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x - 1, y - 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y -= 1;
                }
            }
            break;

        case 2:
            while (x_des <= x && x_des<xCrown && y_des > y && y >= yCrown)
            {
                if (board.getBoard(y + 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x + 1) == 0)
                {

                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x - 1, y + 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y += 1;
                }
            }
            break;
        case 3:
            while (y_des <= y && y_des<yCrown && x_des >= x && x_des>xCrown)
            {
                if (board.getBoard(y - 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x - 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x + 1, y - 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y -= 1;
                }
            }
            break;
        case 4:
            while (x_des >= x && x_des > xCrown && y_des >= y && y_des > yCrown)
            {
                if (board.getBoard(y + 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x - 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x + 1, y + 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y += 1;
                }
            }
            break;

        default:
            break;
        }
    }

}

void changeWhiteToQueen(int i) {
    if (whitePawns[i].getPosY() == 0)
    {
        whitePawns[i].changeStatus();
        whiteCrowns[how_many_whiteCrowns] = Crown(whitePawns[i].getPosY(), whitePawns[i].getPosX(), "white");
        whiteCrowns[how_many_whiteCrowns].born(whitePawns[i].getPosY(), whitePawns[i].getPosX());
        board.update(whiteCrowns[how_many_whiteCrowns].getPosY(), whiteCrowns[how_many_whiteCrowns].getPosX(), 3);
        how_many_whiteCrowns++;
        board.show();
    }
}

void changeBlackToQueen(int i) {
    if (blackPawns[i].getPosY() == 7)
    {
        blackPawns[i].changeStatus();
        blackCrowns[how_many_blackCrowns] = Crown(blackPawns[i].getPosY(), blackPawns[i].getPosX(), "black");
        blackCrowns[how_many_blackCrowns].born(blackPawns[i].getPosY(), blackPawns[i].getPosX());
        board.update(blackCrowns[how_many_blackCrowns].getPosY(), blackCrowns[how_many_blackCrowns].getPosX(), 4);
        how_many_blackCrowns++;
        board.show();
    }
}

void turn() {
    int x;
    int y;
    int bicie;
    int moveNumber = 0;
    int captureCounter = 0;
    if (turnOf) {
        std::cout << "-----------------\nRuch gracza: " << player2.getName() << " (czarne pionki X)\n";
    }
    else {
        std::cout << "-----------------\nRuch gracza: " << player1.getName() << " (biale pionki O)\n";
    }
    std::cout << "Wybierz pionek (podaj jego wspolrzedne): \n";
    std::cin >> x;
    std::cin >> y;
    for (int i = 0; i < 12; i++) {
        if (blackPawns[i].getPosX() == x && blackPawns[i].getPosY() == y && turnOf && blackPawns[i].getStatus() == true) {
            blackPawns[i].choose();

            if ((board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) == 0) &&
                (board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) == 0)) {
                std::cout << "Pionek nie moze wykonac zadnego ruchu, wybierz inny\n";
                turn();
                return;
            }

            bicie = board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color);
            while (bicie)
            {
                std::cout << "Istnieje bicie. Chcesz je wykonac? [T/N]\n";
                std::string bijemy;
                std::cin >> bijemy;
                if (bijemy == "T" || bijemy == "Tak" || bijemy == "tak" || bijemy == "t")
                {
                    captureCounter++;
                    captureMove(i, blackPawns[i].color, bicie);
                    changeBlackToQueen(i);
                }
                if (bijemy == "N" || bijemy == "Nie" || bijemy == "nie" || bijemy == "n")
                {
                    break;
                }
                bicie = board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color);
            }
            if (captureCounter == 0) {
                std::cout << "Wybierz ruch - ";
                switch (board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color)) {
                case 1:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << blackPawns[i].getPosX() - 1
                        << "," << blackPawns[i].getPosY() + 1 << "]\n";
                    while (moveNumber != 1) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                        blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() - 1);
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                        board.show();
                    }
                    break;
                case 2:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << blackPawns[i].getPosX() + 1
                        << "," << blackPawns[i].getPosY() + 1 << "]\n";
                    while (moveNumber != 1) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                        blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() + 1);
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                        board.show();
                    }
                    break;
                case 3:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << blackPawns[i].getPosX() - 1
                        << "," << blackPawns[i].getPosY() + 1 << "], 2 -> [" << blackPawns[i].getPosX() + 1
                        << "," << blackPawns[i].getPosY() + 1 << "]\n";
                    while (moveNumber != 1 && moveNumber != 2) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                        blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() - 1);
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                        board.show();
                    }
                    if (moveNumber == 2) {
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                        blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() + 1);
                        board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                        board.show();
                    }
                    break;
                }
                changeBlackToQueen(i);
                turnOf = !turnOf;
                return;
            }
            else {
                turnOf = !turnOf;
                return;
            }
        }
        if (whitePawns[i].getPosX() == x && whitePawns[i].getPosY() == y && !turnOf && whitePawns[i].getStatus() == true) {
            whitePawns[i].choose();
            if (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) == 0 &&
                (board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) == 0)) {
                std::cout << "Pionek nie moze wykonac zadnego ruchu, wybierz inny\n";
                turn();
                return;
            }

            bicie = board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color);
            while (bicie)
            {
                std::cout << "Istnieje bicie. Chcesz je wykonac? [T/N]\n";
                std::string bijemy;
                std::cin >> bijemy;
                if (bijemy == "T" || bijemy == "Tak" || bijemy == "tak" || bijemy == "t")
                {
                    captureCounter++;
                    captureMove(i, whitePawns[i].color, bicie);
                    changeWhiteToQueen(i);
                }
                if (bijemy == "N" || bijemy == "Nie" || bijemy == "nie" || bijemy == "n")
                {
                    break;
                }
                bicie = board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color);
            }

            if (captureCounter == 0) {
                std::cout << "Wybierz ruch - ";
                switch (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color)) {
                case 1:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << whitePawns[i].getPosX() - 1
                        << "," << whitePawns[i].getPosY() - 1 << "]\n";
                    while (moveNumber != 1) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                        whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() - 1);
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                        board.show();
                    }
                    break;
                case 2:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << whitePawns[i].getPosX() + 1
                        << "," << whitePawns[i].getPosY() - 1 << "]\n";
                    while (moveNumber != 1) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                        whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() + 1);
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                        board.show();
                    }
                    break;
                case 3:
                    std::cout << "dostepne ruchy na pola: 1 -> [" << whitePawns[i].getPosX() - 1
                        << "," << whitePawns[i].getPosY() - 1 << "], 2 -> [" << whitePawns[i].getPosX() + 1
                        << "," << whitePawns[i].getPosY() - 1 << "]\n";
                    while (moveNumber != 1 && moveNumber != 2) {
                        std::cin >> moveNumber;
                    }
                    if (moveNumber == 1) {
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                        whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() - 1);
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                        board.show();
                    }
                    if (moveNumber == 2) {
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                        whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() + 1);
                        board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                        board.show();
                    }
                    break;
                }
                changeWhiteToQueen(i);
                turnOf = !turnOf;
                return;
            }
            else {
                turnOf = !turnOf;
                return;
            }
        }
    }
    for (int i = 0; i < 12; i++) { // ruchy damek
        if (blackCrowns[i].getPosX() == x && blackCrowns[i].getPosY() == y && turnOf)
        {
            int x_des, y_des, bicie = board.searchCaptures(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), blackCrowns[i].color);
            blackCrowns[i].choose();
            std::string bijemy;
            int costam; //nie mam juz pomyslu na nazwanie tej zmiennej, ogolnie chodzi o to, ze bedzie mowila programowi ktore z 4 bic ma on wykonac

            while (bicie)
            {
                std::cout << "Istnieje bicie. Chcesz je wykonac? [T/N]\n";
                std::cin >> bijemy;
                if (bijemy == "T" || bijemy == "Tak" || bijemy == "tak" || bijemy == "t")
                {
                    switch (bicie) // wyswietla mozliwe bicia
                    {
                    case 1:
                        std::cout << "Dostepne bicie na godzinie 10\n";
                        break;
                    case 2:
                        std::cout << "Dostepne bicie na godzinie 2\n";
                        break;
                    case 3:
                        std::cout << "Dostepne bicia na godzinie 2 i 10\n";
                        break;
                    case 4:
                        std::cout << "Dostepne bicie na godzinie 8\n";
                        break;
                    case 5:
                        std::cout << "Dostepne bicia na godzinie 8 i 10\n";
                        break;
                    case 6:
                        std::cout << "Dostepne bicia na godzinie 2 i 8\n";
                        break;
                    case 7:
                        std::cout << "Dostepne bicia na godzinie 2, 8 i 10\n";
                        break;
                    case 8:
                        std::cout << "Dostepne bicie na godzinie 5\n";
                        break;
                    case 9:
                        std::cout << "Dostepne bicia na godzinie 5 i 10\n";
                        break;
                    case 10:
                        std::cout << "Dostepne bicia na godzinie 2 i 5\n";
                        break;
                    case 11:
                        std::cout << "Dostepne bicia na godzinie 2, 5 i 10\n";
                        break;
                    case 12:
                        std::cout << "Dostepne bicia na godzinie 5 i 8\n";
                        break;
                    case 13:
                        std::cout << "Dostepne bicia na godzinie 5, 8 i 10\n";
                        break;
                    case 14:
                        std::cout << "Dostepne bicia na godzinie 2, 5 i 8\n";
                        break;
                    case 15:
                        std::cout << "Dostepne bicia na godzinie 2, 5, 8 i 10\n";
                        break;
                    default:
                        break;
                    }
                    std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
                    std::cin >> x_des >> y_des;
                    while ((x_des > 8 || x_des < 0 || y_des>8 || y_des < 0) && (board.getBoard(y_des, x_des) != 0)) {
                        std::cout << "Tego ruchu nie mozesz wykonac. Podaj inne wspolrzedne gdzie zostac przesuniety pionek\n";
                        std::cin >> x_des >> y_des;
                    }

                    if (x_des < blackCrowns[i].getPosX() && y_des < blackCrowns[i].getPosY()) {
                        costam = 1;
                    }
                    else if (x_des < blackCrowns[i].getPosX() && y_des > blackCrowns[i].getPosY()) {
                        costam = 2;
                    }
                    else if (x_des > blackCrowns[i].getPosX() && y_des < blackCrowns[i].getPosY()) {
                        costam = 3;
                    }
                    else if (x_des > blackCrowns[i].getPosX() && y_des > blackCrowns[i].getPosY()) {
                        costam = 4;
                    }
                    MovesCaptureCrown(costam, i, y_des, x_des, blackCrowns[i].color); /// zrob by zamiast bicie byl tutaj ruch z pozycji powyzej zrob jeszcze tez mozliwosc wybrania sobie kierunku bicia
                    board.show();
                    turnOf = !turnOf;
                    return;
                }
                if (bijemy == "N" || bijemy == "Nie" || bijemy == "nie" || bijemy == "n")
                {
                    break;
                }
                bicie = board.checkCapture(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), blackCrowns[i].color);
            }

            std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
            std::cin >> x_des >> y_des;

            while ((board.checkMovesCrown(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), x_des, y_des) == false) &&
                (board.searchCaptures(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), blackCrowns[i].color) == 0)) {
                char wybor;
                std::cout << "Pionek nie moze wykonac tego ruchu. Chcesz wybrać inny ruch czy wybrac inny pionek?\n";
                std::cout << "a) ruch\n";
                std::cout << "b) pionek\n";
                std::cout << "Wybor: ";
                std::cin >> wybor;
                if (wybor == 'b' || wybor == 'B') {
                    turn(); return;
                }
                else {
                    std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
                    std::cin >> x_des >> y_des;
                }
            }
            if (board.checkMovesCrown(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), x_des, y_des)) {
                board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                blackCrowns[i].changePosition(y_des, x_des);
                board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                board.show();
                turnOf = !turnOf;
                return;
            }
        }

        if (whiteCrowns[i].getPosX() == x && whiteCrowns[i].getPosY() == y && !turnOf)
        {
            int x_des, y_des, bicie = board.searchCaptures(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), whiteCrowns[i].color);
            whiteCrowns[i].choose();
            std::string bijemy;

            while (bicie)
            {
                std::cout << "Istnieje bicie. Chcesz je wykonac? [T/N]\n";
                std::cin >> bijemy;
                if (bijemy == "T" || bijemy == "Tak" || bijemy == "tak" || bijemy == "t")
                {
                    switch (bicie)
                    {
                    case 1:
                        std::cout << "Dostepne bicie na godzinie 10\n";
                        break;
                    case 2:
                        std::cout << "Dostepne bicie na godzinie 2\n";
                        break;
                    case 3:
                        std::cout << "Dostepne bicia na godzinie 2 i 10\n";
                        break;
                    case 4:
                        std::cout << "Dostepne bicie na godzinie 8\n";
                        break;
                    case 5:
                        std::cout << "Dostepne bicia na godzinie 8 i 10\n";
                        break;
                    case 6:
                        std::cout << "Dostepne bicia na godzinie 2 i 8\n";
                        break;
                    case 7:
                        std::cout << "Dostepne bicia na godzinie 2, 8 i 10\n";
                        break;
                    case 8:
                        std::cout << "Dostepne bicie na godzinie 5\n";
                        break;
                    case 9:
                        std::cout << "Dostepne bicia na godzinie 5 i 10\n";
                        break;
                    case 10:
                        std::cout << "Dostepne bicia na godzinie 2 i 5\n";
                        break;
                    case 11:
                        std::cout << "Dostepne bicia na godzinie 2, 5 i 10\n";
                        break;
                    case 12:
                        std::cout << "Dostepne bicia na godzinie 5 i 8\n";
                        break;
                    case 13:
                        std::cout << "Dostepne bicia na godzinie 5, 8 i 10\n";
                        break;
                    case 14:
                        std::cout << "Dostepne bicia na godzinie 2, 5 i 8\n";
                        break;
                    case 15:
                        std::cout << "Dostepne bicia na godzinie 2, 5, 8 i 10\n";
                        break;
                    default:
                        break;
                    }
                    std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
                    std::cin >> x_des >> y_des;
                    MovesCaptureCrown(bicie, i, y_des, x_des, whiteCrowns[i].color); /// zrob by zamiast bicie byl tutaj ruch z pozycji powyzej zrob jeszcze tez mozliwosc wybrania sobie kierunku bicia
                    board.show();
                    turnOf = !turnOf;
                    return;
                }
                if (bijemy == "N" || bijemy == "Nie" || bijemy == "nie" || bijemy == "n")
                {
                    break;
                }
                bicie = board.checkCapture(whiteCrowns[i].getPosX(), whiteCrowns[i].getPosY(), whiteCrowns[i].color);
            }

            std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
            std::cin >> x_des >> y_des;

            while ((board.checkMovesCrown(whiteCrowns[i].getPosX(), whiteCrowns[i].getPosY(), x_des, y_des) == false) &&
                (board.searchCaptures(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), whiteCrowns[i].color) == 0)) {
                char wybor;
                std::cout << "Pionek nie moze wykonac tego ruchu. Chcesz wybrać inny ruch czy wybrac inny pionek?\n";
                std::cout << "a) ruch\n";
                std::cout << "b) pionek\n";
                std::cout << "Wybor: ";
                std::cin >> wybor;
                if (wybor == 'b' || wybor == 'B') {
                    turn(); return;
                }
                else {
                    std::cout << "Podaj wspolrzedne gdzie zostac przesuniety pionek\n";
                    std::cin >> x_des >> y_des;
                }
            }
            if (board.checkMovesCrown(whiteCrowns[i].getPosX(), whiteCrowns[i].getPosY(), x_des, y_des)) {
                board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                whiteCrowns[i].changePosition(y_des, x_des);
                board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 3);
                board.show();
                turnOf = !turnOf;
                return;
            }
        }

    }
    std::cout << "Blad, na tym polu nie ma pionka tego gracza\n";
    turn();
}

bool hasPawns(std::string color) {
    if (color == "black") {
        for (int i = 0; i < 12; i++) {
            if ((blackPawns[i].getStatus() == true &&
               (board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) != 0 ||
               board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) != 0)) ||
               blackCrowns[i].getStatus() == true) {
                return true;
            }
        }
        return false;
    }
    if (color == "white") {
        for (int i = 0; i < 12; i++) {
            if ((whitePawns[i].getStatus() == true &&
               (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) != 0 ||
               board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) != 0)) ||
               whiteCrowns[i].getStatus() == true) {
                return true;
            }
        }
        return false;
    }
}

int main()
{
    gameStart();
    while (hasPawns("black") && hasPawns("white")) {
        turn();
    }
    std::string winner;
    winner = turnOf ? player1.getName() : player2.getName();
    std::cout << "WYGRANA GRACZA: " << winner;
    statsFile << getTime() << player1.getName() << " vs " << player2.getName() << "\tZwyciezca: " << winner << "\n\n";
    statsFile.close();
    statsFileInput.close();
}
