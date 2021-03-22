#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"

bool playerShootMissile(boardClass &board, bool salvoMode){
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
        return false;
    }
    if(board.setHit()){
      cout << "\nYour missile hit!\n";
    } else {
    cout << "\nYour missile missed\n";
    }
    if(!salvoMode){
      cout << "Enter any key to finish your turn: ";
      getline(cin, input);
    }
    loop = false;
  }
  return false;
}

bool isEndGame(boardClass &playersBoard, boardClass &otherPlayersBoard){
  if(playersBoard.hasGameEnded()){
    cout << "You lost against a computer, what are you doing?\n";
    return true;
  } else if(otherPlayersBoard.hasGameEnded()){
    cout << "You won!";
    return true;
  }
  return false;
}

