#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"

int getIntFromFile(stringstream& lineStream, char delimiter);
void shootMissile(boardClass& board);
bool isEndGame(boardClass &playersBoard, boardClass &computerBoard);

void OneVsComp(){
  bool gameStarted = false;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
  bool endGame = false;
  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    shootMissile(computerBoard);
    endGame = isEndGame(playersBoard, computerBoard);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
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
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    loop = false;
  }
}

bool isEndGame(boardClass &playersBoard, boardClass &computerBoard){
  if(playersBoard.hasGameEnded()){
    cout << "You lost against a computer, what are you doing?\n";
    return true;
  } else if(computerBoard.hasGameEnded()){
    cout << "You won!";
    return true;
  }
  return false;
}
