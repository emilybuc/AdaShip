#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"

bool playerShootMissile(boardClass &board, bool salvoMode = false){
  //take a default parameter of salvoMode being false
  string input;
  bool loop = true;
  while(loop == true){
    cout << "\nPlease enter the coordinates of the missile you want to fire or \nA. for an automatic missile\nQ. to Quit\nInput: ";
    getline(cin, input);
    //take input
    if(input == "a" || input == "A"){
      //random coordinates if they input A
      board.randomCoordinates();
    } else if (input == "q" || input == "Q"){
      //Not sure this works
        loop = false;
        return true;
    } else if (!board.validateInput(input)){
        cout << "That coordinate isnt valid, please retry";
        return false;
        //ask them to retry
    }
    if(board.setHit()){
      cout << "\nYour missile hit!\n";
      //if sethit is true then the missile hit
    } else {
      cout << "\nYour missile missed\n";
    }
    if(!salvoMode){
      //when salvo mode is false this doesnt ask for input every time they shoot a missile
      cout << "Enter any key to finish your turn: ";
      getline(cin, input);
      //take input 
    }
    loop = false;
  }
  return false;
}

bool isEndGame(boardClass &playersBoard, boardClass &otherPlayersBoard){
  if(playersBoard.hasGameEnded()){
    cout << "You lost against a computer, what are you doing?\n";
    //if the players board the game has ended then the computer won
    return true;
  } else if(otherPlayersBoard.hasGameEnded()){
    cout << "You won!";
    //if the other players board has game ended then you won
    return true;
  }
  return false;
}

