#pragma once
#include <iomanip>
#include <string>
#include <math.h>       /* floor */
#include "boatConfig.h"

class boardClass {
  private:
    vector<vector<tile>> board;
    int boardCoordinates[2];
    int coordinates[2];
    boatClass gameBoatsClass;
    vector <boat> boatList;
    bool showMines;
    bool playersBoard;
    int tilesToHit;
  public:
    boardClass(){
      getConfigBoard();
      boatList = gameBoatsClass.getBoats();
      showMines = false;
      coordinates[0] = 0;
      coordinates[1] = 0;
      tilesToHit = 0;
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        vector<tile>temp;
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          temp.push_back({false, false, false});
        }
        board.push_back(temp);
      }
    }
    void getConfigBoard() {
			ifstream config;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':');
          if(lineType == "Board"){
            int x = getIntFromFile(configStrStream, 'x');
            int y = getIntFromFile(configStrStream, 'x');
            boardCoordinates[0] = x;
            boardCoordinates[1] = y;
          }
        }
      }
			config.close();
		}
    void outputBoard(){
      //change function to output AA and BA etc doesnt work atm
      cout << "  ";
      int alpha = 26;
      for (char letter = 'A'; letter <= boardCoordinates[0] + 64; letter++){
        int variation = floor(letter / alpha);
        if(variation == 2){
          cout << "\t" << letter;
        } else if (variation == 3){
          char secondletter = letter - (variation * alpha);
          system("Color F3");
          cout << "\t" << "A" << secondletter;
        } else if (variation == 4){
          char secondletter = letter - (variation * alpha);
          cout << "\t" << "B" << secondletter;
        } else if (variation == 5){
          char secondletter = letter - (variation * alpha);
          cout << "\t" << "C" << secondletter;
        }
      }
      // board[0][0].hasMine = true;
      cout << endl;
      for (int i = 0; i < board.size(); i++){
        int rowNumbers = i + 1;
        cout << setw(2) << rowNumbers;
        for (int j = 0; j < board[i].size(); j++){
           if (board[j][i].hit == 'H'){
            cout << "\t" << board[j][i].hit;
          } else if (board[j][i].hit == 'M'){
            cout <<"\t" << board[j][i].hit;
          } else if (board[j][i].hasShip && playersBoard){
            cout <<"\t" << board[j][i].hasShip;
          } else if (board[j][i].hasMine == true && showMines == true){
            cout << "\t" << "M" << setw(2);
          } else if(!board[j][i].hit){
            cout << "\t" << "-" ;
          } 
        }
        //Display an opposite way because the board is upside down
      cout << endl;
      }
    }

    void setShipsMenu(){
      string input = "-1"; //declare and initialise an integer type variable
      playersBoard = true;
	    do { //set up a continuous loop
        cout << "\nPlease choose from the following options\n1. Set boats manually\n2. Automatically set boats \n0. Quit\n\n";
        getline(cin, input);
        if(isNo(input)){
          int inputInt = stoi(input);
          switch(inputInt){
            case 1: 
              for (int i = 0; i < boatList.size(); i++){
                outputBoard();
                string choice, option;
                cout << "\nPlease choose an option: \n(M) Manually place next boat\n(A) Auto-place the rest of the boats\n(Q) Quit\nOption:";
                getline(cin, option);
                //instead of doing 2 menus maybe do one and validate if they've inputted A or Q if they want to quit instead of 2 menus 
                if(option == "M" || option == "m"){
                  cout << endl << "Please choose where you want the front of boat ("<< i + 1 <<") to go (eg. A5)" << "\n";
                  gameBoatsClass.listBoats();
                  cout << "\n\n";
                  getline(cin, choice);
                  bool validInput = validateInput(choice);
                  if(validInput == true){
                    cout << "Please choose which direction you want the rest of the boat to go (L)eft (R)ight (U)p (D)own:\n";
                    getline(cin, choice);
                    if(!setShip(choice, boatList[i])){
                      cout << "\nYou cant place a boat here, please try again!\n\n";
                      i--;
                    }
                  } else {
                    //sort out some validation for input
                    cout << "That coordinate cannot be placed please try again \n";
                    i--;
                  }
                } else if (option == "A" || option == "a"){
                    autoSetShips(i);
                    outputBoard();
                    break;
                } else if (option == "Q" || option == "q"){
                  //this doesnt work
                  input = "0";
                } else {
                    cout << "\n'" << option << "' Is an invalid option  - please try again.\n";
                    i--;
                }
              }
              input = yOrN();
              break;
            case 2: 
              //maybe change this to a variable so its easier to understand
              autoSetShips(0);
              outputBoard();
              input = yOrN();
              break;
            case 0: break;
            default:
                cout << "\n'" << input << "' Is an invalid option  - please try again.";
                break;
            };
        } 
      } while(input != "0");
      showMines = true;
    }
    bool validateInput(string input){
      int convertCharToCoord = 65;
      int convertIntToCoord = 48;
      for (int i = 0; i < input.size(); i++){
        if(isalpha(input[i])){
          cout << input[i] << endl;
          int uppercaseChar = toupper(input[i]);
          coordinates[0] += (uppercaseChar - convertCharToCoord);
        } else if(isdigit(input[i])){
          if(isdigit(input[i + 1])){
            int firstDigit = convertArrayToInt(input[i]) * 10;
            int secondDigit = convertArrayToInt(input[i + 1]);
            int finalNum = (firstDigit + secondDigit);
            coordinates[1] = finalNum - 1;
            break;
          } else {
            coordinates[1] = convertArrayToInt(input[i]) - 1;
          }
        } else {
          resetCoord();
          return false;
        }
      }
      cout << coordinates[0] << ", " << coordinates[1] << endl;
      if(validateCoord(coordinates)){
        return true;
      } else {
        resetCoord();
        return false;
      }
    }
    int convertArrayToInt(int input){
      int convertToInt = 48;
      string inputToString = to_string(input);
      int inputInt = stoi(inputToString);
      int convertFromAsciiToInt = inputInt -= convertToInt;
      return convertFromAsciiToInt;
    }

    bool validateCoord(int* coord){
      if(coord[0] < boardCoordinates[0] && coord[1] < boardCoordinates[1] && coord[0] >= 0 && coord[1] >= 0){
        return true;
      }
      return false;
    }
    
    void resetCoord(){
      coordinates[0] = 0;
      coordinates[1] = 0;
    }
    void inputShipIntoCoordinate(boat currentBoat){
      char characterForBoard = currentBoat.name[0];
      board[coordinates[0]][coordinates[1]].hasShip = characterForBoard;

    }
    int setShip(string direction, boat currentBoat){
      bool successfulBoatPlacement;
      if (direction == "L" || direction == "l"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, -1);

      } else if (direction == "R" || direction == "r"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, 1);

      } else if (direction == "U" || direction == "u"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, -1);

      } else if (direction == "D" || direction == "d"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, 1);

      } else {
        cout << "The character you entered was incorrect, try again";
        return 1;
      }
      if(successfulBoatPlacement == true){
        resetCoord();
        return true;
      } else {
        resetCoord();
        return false;
      }
    }

    bool validateBoatPlacement(boat currentBoat, int movementOnXorY, int plusOrMinus1){
      int localBoatCoordinates[2] = { coordinates[0], coordinates[1] };
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        if(!validateCoord(localBoatCoordinates)){
          return false;
        } else if(tileHasShip(localBoatCoordinates) == true){
          return false;
        } else {
          localBoatCoordinates[movementOnXorY] += plusOrMinus1;
        }
      }
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        inputShipIntoCoordinate(currentBoat);
        coordinates[movementOnXorY] += plusOrMinus1;
        tilesToHit++;
      }
      return true;
    } 
    bool tileHasShip(int* localBoatCoordinates){
      if(!board[localBoatCoordinates[0]][localBoatCoordinates[1]].hasShip){
        return false;
      } else {
        return true;
      }
    }
    void autoSetShips(int i){
      for (int j = i; j < boatList.size(); j++){
        randomCoordinates();
        int movementOnXorY = rand() % 2;
        int randomNumber = rand() % 4;
        
        if(!validateBoatPlacement(boatList[j], movementOnXorY, -1)){
          resetCoord();
          j--;
        } else {
          resetCoord();
        }
      }
    }
    string yOrN(){
      string inputTryAgain; 
      cout << "\nAre you happy with this placement? Please type Y/N: ";
      getline(cin, inputTryAgain);
      //asking for Y/N input
      if(inputTryAgain == "Y" || inputTryAgain == "y"){
        return "0";
        //If yes then exit and go 
      } else if (inputTryAgain == "N" || inputTryAgain == "n"){
        cout << "Ok, please retry placing boats\n";
        emptyBoard();
        return "-1";
        //Isnt exiting the function 
        //exit
      } else {
        cout << "invalid input, try again \n";
        yOrN();
        return "-1";
        //fall back if they enter something else
      }
    }
    void emptyBoard(){
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          board[xAxis][yAxis] = {false, false, false};
        }
      }
    }
    void computerPlayerBoard(){
      //maybe change this to a variable so its easier to understand
      playersBoard = true;
      autoSetShips(0);
    }
    int* getCoordinates(){
      return coordinates;
    }
    bool setHit(){
      if(board[coordinates[0]][coordinates[1]].hasShip){
        board[coordinates[0]][coordinates[1]].hit = 'H';
        tilesToHit--;
        resetCoord();
        return true;
      } else {
        board[coordinates[0]][coordinates[1]].hit = 'M';
        resetCoord();
        return false;
      }
    }
    void randomCoordinates(){
        bool loop = true;
        while(loop == true){
          coordinates[0] = rand() % boardCoordinates[0];
          coordinates[1] = rand() % boardCoordinates[1];
          if(board[coordinates[0]][coordinates[1]].hit != 'H' || board[coordinates[0]][coordinates[1]].hit != 'M'){
            loop = false;
          }
        }
        //set coordinates to a coordinate inside the board
    }
    bool hasGameEnded(){
      if(tilesToHit == 0){
        return true;
      } 
      return false;
    }
};

//board.h