#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"

int getIntFromFile(stringstream& lineStream, char delimiter);
void shootMissile(boardClass& board);

void OneVsComp(){
  bool gameStarted = false;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
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
    shootMissile(computerBoard);
    endgame = false;
  	} while(endgame != true);
}

void shootMissile(boardClass &board){
  string input;
  bool loop = true;
  while(loop == true){
    cout << "\nPlease enter the coordinates of the missile you want to fire or type (A) for an automatic missile: ";
    getline(cin, input);
    if(input == "a" || input == "A"){
      board.randomCoordinates();
    } else if (!board.validateInput(input)){
        cout << "That coordinate isnt valid, please retry";
        break;
    }
    if(board.setHit()){
      cout << "\nYour missile hit!\n";
    } else {
    cout << "\nYour missile missed\n";
    }
    cout << "Press any key to finish your turn: ";
    getline(cin, input);
    loop = false;
  }
}
