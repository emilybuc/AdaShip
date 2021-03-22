#pragma once
#include <iomanip>
#include <string>
#include <math.h> //floor
#include "boatConfig.h"

class boardClass {
  private:
    vector<vector<tile>> board;
    int boardCoordinates[2];
    int coordinates[2];
    boatClass gameBoatsClass;
    vector <boat> boatList;
    int tilesToHit;
  public:
    boardClass(){
      getConfigBoard();
      gameBoatsClass.boatsFitOnBoard(boardCoordinates);
      boatList = gameBoatsClass.getBoats();
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
          lineType = convertToUpper(lineType);
          if(lineType == "BOARD"){
            int x = getIntFromFile(configStrStream, 'x');
            int y = getIntFromFile(configStrStream, 'x');
            if(x <= 80 && y <= 80 && x >= 5 && x >= 5){
              boardCoordinates[0] = x;
              boardCoordinates[1] = y;
            } else {
              cout << "\nBoard needs to be between 5 and 80 height and width\nPlease reconfigure the 'adaship_config.ini' file\nExiting\n";
              exit(0);
            }
          }
        }
      }
			config.close();
		}
    void outputBoard(){
      cout << "  ";
      for (int i = 0; i < boardCoordinates[1]; i++){
        char letter = 'A';
          if(i <= 25){
            letter = letter + i;
            cout << "\t" << letter;
          } else if(i <= 51){
            int variation = i - 26;
            letter = letter + variation;
            cout << "  A" << letter;
          } else if(i <= 77){
            int variation = i - 52;
            letter = letter + variation;
            cout << "  B" << letter;
          } else if(i <= 103){
            int variation = i - 78;
            letter = letter + variation;
            cout << "  C" << letter;
          }
      }
      cout << endl;
      for (int i = 0; i < board.size(); i++){
        int rowNumbers = i + 1;
        cout << setw(2) << rowNumbers;
        for (int j = 0; j < board[i].size(); j++){
          // cout << "Hit: "<<board[j][i].hit << "\nHas Ship: " << board[j][i].hasShip;
           if (board[j][i].hit == 'H'){
            cout << "\t" << board[j][i].hit;
          } else if (board[j][i].hit == 'M'){
            cout <<"\t" << board[j][i].hit;
          } else if (board[j][i].hasShip && board[j][i].hasMine == true){
            cout << "  " << board[j][i].hasShip << "/Ø";
          } else if (board[j][i].hasShip){
            cout <<"\t" << board[j][i].hasShip;
          } else if (board[j][i].hasMine == true){
            cout << "\t" << "Ø" << setw(2);
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
	    do { //set up a continuous loop
        cout << "\nPlease choose from the following options\n1. Set boats manually\n2. Automatically set boats \n0. Quit\n\nOption: ";
        getline(cin, input);
        cout << endl;
        if(isNo(input)){
          int inputInt = stoi(input);
          switch(inputInt){
            case 1: 
              for (int i = 0; i < boatList.size(); i++){
                outputBoard();
                string input;
                gameBoatsClass.listBoats();
                cout << "\n\nPlease choose where you want the front of boat ("<< i + 1 <<") to go (eg. A5) or enter:\n1. To auto-place the rest of the boats\n2. To stop placing boats\n0. To quit\n\nInput:";
                getline(cin, input);
                if (input == "1"){
                  autoSetShips(i);
                  outputBoard();
                  break;
                } else if (input == "2"){
                  //This option can be used if the user has a large amount of boats that could potentially fit on the board as this is checked beforehand but they havent placed them in an optimised way so they can carry on with the game
                  break;
                } else if(input == "0"){
                  //this doesnt work
                  break;
                } else if (validateInput(input)){
                  cout << "Please choose which direction you want the rest of the boat to go (L)eft (R)ight (U)p (D)own:\n";
                  getline(cin, input);
                  if(!setShip(input, boatList[i])){
                    cout << "\nYou cant place a boat here, please try again!\n\n";
                    i--;
                  }
                } else {
                  cout << "That coordinate cannot be placed please try again \n";
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
    }
    
    bool validateInput(string input){
      int convertCharToCoord = 65;
      string xCoord, yCoord;
      for (int i = 0; i < input.size(); i++){
        if(isalpha(input[i])){
          xCoord += input[i];
        } else if(isdigit(input[i])){
          yCoord += input[i];
        } else {
          resetCoord();
          return false;
        }
      }

      int xCoordInt = 0;
      xCoord = convertToUpper(xCoord);

      for (int i = 0 ; i < xCoord.length(); i++){
        if(xCoord.length() == 1){
          xCoordInt = (xCoord[i] - convertCharToCoord);

        } else if (xCoord.length() == 2){
          switch (i){
            case 0:
             if(xCoord[i] == 'A'){
               xCoordInt += 26;
             } else if (xCoord[i] == 'B'){
               xCoordInt += 52;
             } else if (xCoord[i] == 'C'){
               xCoordInt += 78;
             }
              break;
            case 1:
              xCoordInt += (xCoord[i] - convertCharToCoord);
              break;
          }
        } else {
          return false;
        }
      }
      coordinates[0] = xCoordInt;
      coordinates[1] = stoi(yCoord) - 1;

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
    void autoSetShips(int i = 0){
      int amountOfTimesTried = 0;
      for (int j = i; j < boatList.size(); j++){
        randomCoordinates();
        int movementOnXorY = rand() % 2;
        int randomNumber = rand() % 4;
        // cout << amountOfTimesTried;
        if(!validateBoatPlacement(boatList[j], movementOnXorY, -1) && amountOfTimesTried <= 100){
          resetCoord();
          j--;
          amountOfTimesTried++;
          // cout << amountOfTimesTried << ", ";
        } else if(amountOfTimesTried > 100) {
          cout << "\nAmount of ships that can be placed has been met, please continue with set-up\n";
          break;
        } else {
          amountOfTimesTried = 0;
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
    int* getCoordinates(){
      return coordinates;
    }
    bool setHit(){
      if(board[coordinates[0]][coordinates[1]].hasShip && board[coordinates[0]][coordinates[1]].hasMine){
        board[coordinates[0]][coordinates[1]].hit = 'H';
        tilesToHit--;
        mineExplosion();
        resetCoord();
        return true;
      } else if(board[coordinates[0]][coordinates[1]].hasMine){
        board[coordinates[0]][coordinates[1]].hit = 'H';
        mineExplosion();
        resetCoord();
        return true;
      } else if(board[coordinates[0]][coordinates[1]].hasShip){
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
    int salvoMode(){
      int c = 0, b = 0, d = 0, s = 0, p = 0, numOfBoatsNotSunk = 0;
      for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++){
           if (board[i][j].hit == false && board[i][j].hasShip){
            switch(board[i][j].hasShip) {
              case 'C': c++; break; 
              case 'B': b++; break;
              case 'D': d++; break;
              case 'S': s++; break;
              case 'P': p++; break;
            }
          } 
        }
      }
      int boatsNotSunk[] = {c,b,d,s,p}; 
      for (int i = 0; i < 5; i++){ 
        if(boatsNotSunk[i] != 0){
          numOfBoatsNotSunk++;
        }
      }
      return numOfBoatsNotSunk;
    }
    void setMines(){
      cout << "\nCurrently placing mines...\nPlease note that mines are indicated with a Ø\n\n";
      //I used a different symbol for the mines than just the M character because of the overlap with the symbol used for miss.
      int loop = 5;
      while(loop != 0){
        // cout << loop << endl;
        randomCoordinates();
        if(board[coordinates[0]][coordinates[1]].hasMine == false){
          board[coordinates[0]][coordinates[1]].hasMine = true;
          loop--;
        }
        resetCoord();
      }
    }
    bool setCoordinates(int x, int y){
      coordinates[0] = x; 
      coordinates[1] = y;
      if(validateCoord(coordinates) && board[coordinates[0]][coordinates[1]].hit != 'H' && board[coordinates[0]][coordinates[1]].hit != 'M'){
        return true;
      } else {
        return false;
      }
    }



    
    private: 
    void emptyBoard(){
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          board[xAxis][yAxis] = {false, false, false};
        }
      }
    }
    void mineExplosion(){
      int localCoord[] = { coordinates[0], coordinates[1] }; 
      updateCoordToNewCoord(localCoord, -1, -1);
      updateCoordToNewCoord(localCoord, -1, 0);
      updateCoordToNewCoord(localCoord, -1, 1);
      updateCoordToNewCoord(localCoord, 0, -1);
      updateCoordToNewCoord(localCoord, 0, 1);
      updateCoordToNewCoord(localCoord, 1, -1);
      updateCoordToNewCoord(localCoord, 1, 0);
      updateCoordToNewCoord(localCoord, 1, 1);
    }

    void updateCoordToNewCoord(int* localCoord, int xAxisMovement, int yAxisMovement){
      coordinates[0] += xAxisMovement;
      coordinates[1] += yAxisMovement;
      if(validateCoord(coordinates)){
        setHit();
      }
        coordinates[0] = localCoord[0];
        coordinates[1] = localCoord[1];
        // when a mine hits another mine then it errors, that is because theres two of the same function running.
    }
};

//board.h