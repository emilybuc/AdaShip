#pragma once
#include "gameFuncs.h"

void oneVsComp(){
  bool endGame = false;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
  bool notSalvoMode = false;

  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Turn\n\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    endGame = playerShootMissile(computerBoard, notSalvoMode);
    endGame = isEndGame(playersBoard, computerBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\nComputers Turn\n\nComputers Board\n";
    computerBoard.outputBoard();
    cout << "\nTarget Board\n";
    playersBoard.outputBoard();
    computerShootMissile(playersBoard, notSalvoMode);
    endGame = isEndGame(playersBoard, computerBoard);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void twoPlayerGame(){
  bool notSalvoMode = false;
  bool endGame = false;
  system("clear");
  cout << "\t\t\tPlayer one set up!";
  boardClass playerOneBoard;
  playerOneBoard.setShipsMenu();
  system("clear");
  cout << "\t\t\tPlayer two set up!";
  boardClass playerTwoBoard;
  playerTwoBoard.setShipsMenu();
  //set up two boards for two player

  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    system("clear");
    cout << "Player One's Turn\n\nYour Board\n";
    playerOneBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerTwoBoard.outputBoard();
    endGame = playerShootMissile(playerTwoBoard, notSalvoMode);
    endGame = isEndGame(playerOneBoard, playerTwoBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on
    system("clear");
    cout << "Player Two's Turn\n\nYour Board\n";
    playerTwoBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerOneBoard.outputBoard();
    endGame = playerShootMissile(playerOneBoard, notSalvoMode);
    endGame = isEndGame(playerTwoBoard, playerOneBoard);
    system("clear");
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void oneVsCompSalvo(){
  string input;
  bool salvoMode = true;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
  bool endGame = false;
  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Turn\n";
    int amountOfMissiles = playersBoard.salvoMode();
    while(amountOfMissiles != 0){
      cout << "\nYour Board\n";
      playersBoard.outputBoard();
      cout << "\nTarget Board\n";
      computerBoard.outputBoard();
      cout << "You have (" << amountOfMissiles << ") Missile(s)";
      endGame = playerShootMissile(computerBoard, true);
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfMissiles--;
    }
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\nComputers Turn\n";
    cout << "\nComputers Board\n";
    computerBoard.outputBoard();
    cout << "\nTarget Board\n";
    playersBoard.outputBoard();
    int amountOfComputersMissiles = computerBoard.salvoMode();
    cout << "The computer has (" << amountOfComputersMissiles << ") Missile(s)";
    while(amountOfComputersMissiles != 0){
      computerShootMissile(playersBoard, salvoMode);
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfComputersMissiles--;
    }
    cout << "\nEnter any key to finish the computers turn: ";
    getline(cin, input);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void twoPlayerGameSalvo(){
  string input;
  bool salvoMode = true;
  boardClass playersBoard;
  playersBoard.setShipsMenu();
  boardClass computerBoard;
  computerBoard.computerPlayerBoard();
  bool endGame = false;
  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Turn\n";
    int amountOfMissiles = playersBoard.salvoMode();
    while(amountOfMissiles != 0){
      cout << "\nYour Board\n";
      playersBoard.outputBoard();
      cout << "\nTarget Board\n";
      computerBoard.outputBoard();
      cout << "You have (" << amountOfMissiles << ") Missile(s)";
      endGame = playerShootMissile(computerBoard, true);
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfMissiles--;
    }
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\nComputers Turn\n";
    cout << "\nComputers Board\n";
    computerBoard.outputBoard();
    cout << "\nTarget Board\n";
    playersBoard.outputBoard();
    int amountOfComputersMissiles = computerBoard.salvoMode();
    cout << "The computer has (" << amountOfComputersMissiles << ") Missile(s)";
    while(amountOfComputersMissiles != 0){
      computerShootMissile(playersBoard, salvoMode);
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfComputersMissiles--;
    }
    cout << "\nEnter any key to finish the computers turn: ";
    getline(cin, input);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}