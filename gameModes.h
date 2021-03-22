#pragma once
#include "gameFuncs.h"
#include "computerTargeting.h"

void oneVsComp(){
  bool endGame = false;
  boardClass playersBoard;
  playersBoard.setBoatsMenu();
  //set up the players board

  boardClass computerBoard;
  computerTargeting computerPlayer;
  computerBoard.autoSetBoats();
  //set up the computers board aswell as the class for the computer player

  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Turn\n\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    //output both boards so the user can see where they want to hit

    endGame = playerShootMissile(computerBoard);
    //if they shoot and they press Q then set end game to true
    if(endGame)break;
    endGame = isEndGame(playersBoard, computerBoard);
    if(endGame)break;
    //check the state
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\nComputers Turn\n";
    computerPlayer.shootMissile(playersBoard);
    //shoot a missile on the players board
    endGame = isEndGame(playersBoard, computerBoard);
  	} while(endGame != true);
    //while endgame doesnt = true then carry on looping
    cout << "\nThe game has ended, I hope you had fun\n";
}

void twoPlayerGame(){
  bool endGame = false;

  system("clear");
  cout << "\t\t\tPlayer one set up!";
  boardClass playerOneBoard;
  playerOneBoard.setBoatsMenu();
  system("clear");

  cout << "\t\t\tPlayer two set up!";
  boardClass playerTwoBoard;
  playerTwoBoard.setBoatsMenu();
  //set up two boards for two players

  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    system("clear");
    cout << "Player One's Turn\n\nYour Board\n";
    playerOneBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerTwoBoard.outputBoard();
    endGame = playerShootMissile(playerTwoBoard);
    if(endGame)break;
    endGame = isEndGame(playerOneBoard, playerTwoBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on
    system("clear");
    //clear the previous screen so the second player can play
    cout << "Player Two's Turn\n\nYour Board\n";
    playerTwoBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerOneBoard.outputBoard();
    endGame = playerShootMissile(playerOneBoard);
    //allow the second player to shoot a missile
    endGame = isEndGame(playerTwoBoard, playerOneBoard);
    system("clear");
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void oneVsCompSalvo(){
  string input;
  bool salvoMode = true;
  boardClass playersBoard;
  playersBoard.setBoatsMenu();

  boardClass computerBoard;
  computerTargeting computerPlayer;
  computerBoard.autoSetBoats();
  bool endGame = false;
  system("clear");

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
      //output the number of missiles the player has
      endGame = playerShootMissile(computerBoard, true);
      //this will loop for as long as the player has missiles
      if(endGame)break;
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfMissiles--;
    }
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\n\bComputers Turn\n";
    int amountOfComputersMissiles = computerBoard.salvoMode();
    //this function returns the amount of ships that havent been sunk
    cout << "\nThe computer has (" << amountOfComputersMissiles << ") Missile(s)\n";
    //this outputs the amount of missiles the computer has
    while(amountOfComputersMissiles != 0){
      computerPlayer.shootMissile(playersBoard, salvoMode);
      endGame = isEndGame(playersBoard, computerBoard);
      if(endGame)break;
      amountOfComputersMissiles--;
      //minus amount of missiles
    }
    cout << "\nYour Updated Board\n";
    playersBoard.outputBoard();
    cout << "\nEnter any key to finish the computers turn: ";
    getline(cin, input);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void twoPlayerGameSalvo(){
  bool salvoMode = true;
  bool endGame = false;
  string input;

  system("clear");
  cout << "\t\t\tPlayer one set up!";
  boardClass playerOneBoard;
  playerOneBoard.setBoatsMenu();
  system("clear");
  cout << "\t\t\tPlayer two set up!";
  boardClass playerTwoBoard;
  playerTwoBoard.setBoatsMenu();
  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "Player One's Turn\n";
    int amountOfMissilesPlayerOne = playerOneBoard.salvoMode();
    while(amountOfMissilesPlayerOne != 0){
      cout << "\nYour Board\n";
      playerOneBoard.outputBoard();
      cout << "\nTarget Board\n";
      playerTwoBoard.outputBoard();
      cout << "You have (" << amountOfMissilesPlayerOne << ") Missile(s)";
      endGame = playerShootMissile(playerTwoBoard, salvoMode);
      if(endGame)break;
      endGame = isEndGame(playerOneBoard, playerTwoBoard);
      if(endGame)break;
      amountOfMissilesPlayerOne--;

    }
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    //exit out of function if the game has been exited or won by the player before moving on

    system("clear");
    cout << "Player Two's Turn\n";
    int amountOfMissilesPlayerTwo = playerTwoBoard.salvoMode();
    while(amountOfMissilesPlayerTwo != 0){
      cout << "\nYour Board\n";
      playerTwoBoard.outputBoard();
      cout << "\nTarget Board\n";
      playerOneBoard.outputBoard();
      cout << "You have (" << amountOfMissilesPlayerTwo << ") Missile(s)";
      endGame = playerShootMissile(playerOneBoard, salvoMode);
      if(endGame)break;
      endGame = isEndGame(playerTwoBoard, playerOneBoard);
      if(endGame)break;
      amountOfMissilesPlayerTwo--;
    }
    cout << "Enter any key to finish your turn: ";
    getline(cin, input);
    system("clear");
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void oneVsCompMines(){
  bool endGame = false;
  string input;

  //set up for the player
  boardClass playersBoard;
  playersBoard.setBoatsMenu();
  cout << "\nCurrently placing mines...\nPlease note that mines are indicated with a Ø\n\n";
  //I used a different symbol for the mines than just the M character because of the overlap with the symbol used for miss. 
  playersBoard.setMines();
  //set mines for the players board
  playersBoard.outputBoard();
  cout << "\nYour mines have been placed, enter any key to continue: ";
  getline(cin, input);

  //set up for the computer player 
  boardClass computerBoard;
  computerTargeting computerPlayer;
  computerBoard.autoSetBoats();
  computerBoard.setMines();

  system("clear");
  //I saw that there were lots of security concerns about the above line that clears the console, I would not use this command in production code
  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nYour Turn\n\nYour Board\n";
    playersBoard.outputBoard();
    cout << "\nTarget Board\n";
    computerBoard.outputBoard();
    endGame = playerShootMissile(computerBoard);
    if(endGame)break;
    endGame = isEndGame(playersBoard, computerBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on

    cout << "\nComputers Turn\n";
    computerPlayer.shootMissile(playersBoard);
    endGame = isEndGame(playersBoard, computerBoard);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}

void twoPlayerGameMines(){
  bool endGame = false;
  string input;

  //set up for the first player
  cout << "\t\t\tPlayer one set up!";
  system("clear");
  boardClass playerOneBoard;
  playerOneBoard.setBoatsMenu();
  cout << "\nCurrently placing mines...\nPlease note that mines are indicated with a Ø\n\n";
  //I used a different symbol for the mines than just the M character because of the overlap with the symbol used for miss.
  playerOneBoard.setMines();
  playerOneBoard.outputBoard();
  cout << "\nYour mines have been placed, enter any key to continue: ";
  getline(cin, input);
  system("clear");

  //set up for the second player
  system("clear");
  cout << "\t\t\tPlayer two set up!";
  boardClass playerTwoBoard;
  playerTwoBoard.setBoatsMenu();
  playerTwoBoard.setMines();
  playerTwoBoard.outputBoard();
  cout << "\nYour mines have been placed, enter any key to continue: ";
  getline(cin, input);

  system("clear");

  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    system("clear");
    cout << "Player One's Turn\n\nYour Board\n";
    playerOneBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerTwoBoard.outputBoard();
    endGame = playerShootMissile(playerTwoBoard);
    if(endGame)break;
    endGame = isEndGame(playerOneBoard, playerTwoBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on
    system("clear");
    cout << "Player Two's Turn\n\nYour Board\n";
    playerTwoBoard.outputBoard();
    cout << "\nTarget Board\n";
    playerOneBoard.outputBoard();
    endGame = playerShootMissile(playerOneBoard);
    endGame = isEndGame(playerTwoBoard, playerOneBoard);
    if(endGame)break;
    system("clear");
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}


void compVsCompMines(){
  bool endGame = false;
  bool salvoMode = false;
  string input;

  //set up for the player
  boardClass compOneBoard;
  computerTargeting compPlayerOne;
  compOneBoard.autoSetBoats();
  compOneBoard.setMines();
  //set up for the computer player 
  boardClass compTwoBoard;
  computerTargeting compPlayerTwo;
  compTwoBoard.autoSetBoats();
  compTwoBoard.setMines();

  cout << "\t\t\tLet the game commence!\n";
	do { //set up a continuous loop
    cout << "\nComputer One's Turn\n";
    compPlayerOne.shootMissile(compTwoBoard, salvoMode, "Computer Player Two's Board");
    //passing in the second variable because I need to pass in the 3rd variable of what i want to be outputted above the board
    endGame = isEndGame(compOneBoard, compTwoBoard);
    if(endGame)break;
    //exit out of function if the game has been exited or won by the player before moving on
    cout << "\nComputer Two's Turn\n";
    compPlayerTwo.shootMissile(compOneBoard, salvoMode, "Computer Player One's Board");
    endGame = isEndGame(compTwoBoard, compOneBoard);
  	} while(endGame != true);
    cout << "\nThe game has ended, I hope you had fun\n";
}