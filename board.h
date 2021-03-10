#pragma once
#include <iomanip>
#include <string>
#include <math.h>       /* floor */
#include "boatConfig.h"

class boardClass {
  private:
    vector<vector<tile>> board;
    int boardCoordinates[2];
    int boatCoordinates[2];
  public:
    boardClass(){
      getConfigBoard();
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        vector<tile>temp;
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          temp.push_back({false, false, false});
        }
        board.push_back(temp);
      }
      // for (int i =0; i<tiles.size(); i++){
      //   for (int j = 0; j < tiles[i].size(); j++){
      //     cout << tiles[i][j].hit;
      //   }
      // }
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
            boardCoordinates[0] = y;
            boardCoordinates[1] = x;
          }
        }
      }
			config.close();
		}
    void outputPlayersBoard(bool gameStarted, bool playersBoard){
      //change function to output AA and BA etc doesnt work atm
      cout << "  ";
      int alpha = 26;
      for (char letter = 'A'; letter <= boardCoordinates[1] + 64; letter++){
        int variation = floor(letter / alpha);
        if(variation == 2){
          cout << "\t" << letter;
        } else if (variation == 3){
          char secondletter = letter - (variation * alpha);
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
           if (board[i][j].hit){
            cout << "\t" << "H";
          } else if (board[i][j].hasShip && playersBoard){
            cout <<"\t" << board[i][j].hasShip;
          } else if (board[i][j].hasMine == true && gameStarted == true){
            cout << "\t" << "M" << setw(2);
          } else if(!board[i][j].hit){
            cout << "\t" << "-" ;
          } 
        }
      cout << endl;
      }
    }

    void setShipsMenu(){
      boatClass gameBoatsClass;
      vector <boat> boatList = gameBoatsClass.getBoats();

      string input = "-1"; //declare and initialise an integer type variable
	    do { //set up a continuous loop
        cout << "\nPlease choose from the following options\n1. Set boats manually\n2. Automatically set boats \n0. Quit\n\n";
        getline(cin, input);
        if(isNo(input)){
          int inputInt = stoi(input);
          switch(inputInt){
            case 1: 
              for (int i = 0; i < boatList.size(); i++){
                outputPlayersBoard(false, true);
                string choice;
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
              }
              outputPlayersBoard(false, true);
              cout << "Are you happy with this placement? Please type Y/N"; break;
            case 2: 
                for (int i = 0; i < boatList.size(); i++){
                  boatCoordinates[0] = rand() % boardCoordinates[0];
                  boatCoordinates[1] = rand() % boardCoordinates[1];
                  cout << "i = " << i << endl;
                  if(!autoSetShips(boatList[i])){
                    i--;
                  }
                }
                outputPlayersBoard(false, true);
                break;
            case 0: break;
            default:
                cout << "\n'" << input << "' Is an invalid option  - please try again.";
                break;
            };
        }
      } while(input != "0");
      cout << "Goodbye\n";
    }
    bool validateInput(string input){
      int convertCharToCoord = 65;
      int convertIntToCoord = 48;
      for (int i = 0; i < input.size(); i++){
        if(isalpha(input[i])){
          int uppercaseChar = toupper(input[i]);
          boatCoordinates[1] += (uppercaseChar - convertCharToCoord);
        } else if(isdigit(input[i])){
          if(isdigit(input[i + 1])){
            int firstDigit = convertArrayToInt(input[i]) * 10;
            int secondDigit = convertArrayToInt(input[i + 1]);
            int finalNum = (firstDigit + secondDigit);
            boatCoordinates[0] = finalNum - 1;
            break;
          } else {
            boatCoordinates[0] = convertArrayToInt(input[i]) - 1;
          }
        } else {
          resetBoatCoord();
          return false;
        }
      }
      if(validateCoord(boatCoordinates)){
        return true;
      } else {
        resetBoatCoord();
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

    bool validateCoord(int* boatCoord){
      if(boatCoord[0] < boardCoordinates[0] && boatCoord[1] < boardCoordinates[1] && boatCoord[0] >= 0 && boatCoord[1] >= 0){
        return true;
      }
      return false;
    }
    
    void resetBoatCoord(){
      boatCoordinates[0] = 0;
      boatCoordinates[1] = 0;
    }
    void inputShipIntoCoordinate(boat currentBoat){
      char characterForBoard = currentBoat.name[0];
      board[boatCoordinates[0]][boatCoordinates[1]].hasShip = characterForBoard;

    }
    int setShip(string direction, boat currentBoat){
      int localBoatCoordinates[2] = { boatCoordinates[0], boatCoordinates[1] };
      bool successfulBoatPlacement;
      if (direction == "L" || direction == "l"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, -1);

      } else if (direction == "R" || direction == "r"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, 1);

      } else if (direction == "U" || direction == "u"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, -1);

      } else if (direction == "D" || direction == "d"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, 1);

      } else {
        cout << "The character you entered was incorrect, try again";
        return 1;
      }
      if(successfulBoatPlacement == true){
        resetBoatCoord();
        return true;
      } else {
        resetBoatCoord();
        return false;
      }
    }

    bool validateBoatPlacement(boat currentBoat, int movementOnXorY, int plusOrMinus1){
      int localBoatCoordinates[2] = { boatCoordinates[0], boatCoordinates[1] };
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        if(!validateCoord(localBoatCoordinates)){
          return false;
        } else if(tileHasShip(localBoatCoordinates) == true){
          cout << "tile has a ship" << endl;
          return false;
        } else {
          localBoatCoordinates[movementOnXorY] += plusOrMinus1;
        }
      }
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        inputShipIntoCoordinate(currentBoat);
        boatCoordinates[movementOnXorY] += plusOrMinus1;
      }
      return true;
    } 
    bool tileHasShip(int* localBoatCoordinates){
      if(!board[localBoatCoordinates[1]][localBoatCoordinates[0]].hasShip){
        return false;
      } else {
        return true;
      }
    }
    bool autoSetShips(boat currentBoat){
      int movementOnXorY = rand() % 2;
      int randomNumber = rand() % 4;
      int arrayWithPlusOrMinus1[4] = {-1, 1, 1,-1};
      cout << movementOnXorY;
      int plusOrMinus1 = arrayWithPlusOrMinus1[randomNumber];
      
      if(!validateBoatPlacement(currentBoat, movementOnXorY, -1)){
        resetBoatCoord();
        return false;
      } else {
        resetBoatCoord();
        outputPlayersBoard(false, true);
        return true;
      }
    }
};

