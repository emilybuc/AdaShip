#pragma once
#include "config.h"
#include "board.h"

void OneVsComp(){
  controller newGame;
  newGame.getConfigBoats();
  bool gameStarted = true;
  int* boardCoordinates = newGame.getConfigBoard();
  boardClass playersBoard(boardCoordinates[0], boardCoordinates[1]);
  playersBoard.outputPlayersBoard(gameStarted, false);
  // vector<vector<tile>> board1 = newGame.getBoard();

}