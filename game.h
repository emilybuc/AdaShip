#pragma once
#include "config.h"
#include "board.h"

void OneVsComp(){
  controller newGame;
  newGame.getConfigBoats();
  int* boardCoordinates = newGame.getConfigBoard();
  boardClass playersBoard(boardCoordinates[0], boardCoordinates[1]);
  playersBoard.outputBoard();
  newGame.listBoats();
  // vector<vector<tile>> board1 = newGame.getBoard();

}