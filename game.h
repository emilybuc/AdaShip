#pragma once
#include "config.h"
#include "board.h"
#include "boatConfig.h"
int getIntFromFile(stringstream& lineStream, char delimiter);

void OneVsComp(){
  bool gameStarted = true;
  boardClass playersBoard;
  playersBoard.outputPlayersBoard(gameStarted, false);
  playersBoard.setShips();
}