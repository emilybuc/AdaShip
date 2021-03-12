#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"
int getIntFromFile(stringstream& lineStream, char delimiter);

void OneVsComp(){
  bool gameStarted = false;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
  string input;
  bool endgame = false;
  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    gameStarted = true;
    cout << "\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    cout << "\nPlease enter the coordinates of the missle you want to fire: ";
    getline(cin, input);
  	} while(input != "0" || endgame != true);
}