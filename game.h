#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"

int getIntFromFile(stringstream& lineStream, char delimiter);
bool playerShootMissile(boardClass& board);
bool isEndGame(boardClass &playersBoard, boardClass &computerBoard);
void computerShootMissile(boardClass &playersBoard);

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
    cout << "\nYour Turn\n\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    endGame = playerShootMissile(computerBoard);
    endGame = isEndGame(playersBoard, computerBoard);
    if(endGame)break;

    cout << "\nComputers Turn\n\nComputers Board\n";
    computerBoard.outputBoard();
    cout << "\nTarget Board\n";
    playersBoard.outputBoard();
    computerShootMissile(playersBoard);
    endGame = isEndGame(playersBoard, computerBoard);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

bool playerShootMissile(boardClass &board){
  string input;
  bool loop = true;
  while(loop == true){
    cout << "\nPlease enter the coordinates of the missile you want to fire or type (A) for an automatic missile: ";
    getline(cin, input);
    if(input == "a" || input == "A"){
      board.randomCoordinates();
    } else if (input == "q" || input == "Q"){
        loop = false;
        return true;
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
    return false;
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

void computerShootMissile(boardClass &board){
  board.randomCoordinates();
  if(board.setHit()){
      cout << "\nComputers missile hit!\n";
    } else {
    cout << "\nComputers missile missed\n";
  }
  string endTurn;
  cout << "Enter any key to finish the computers turn: ";
  getline(cin, endTurn);
}
