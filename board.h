#pragma once
#include <iomanip>
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
            boardCoordinates[0] = x;
            boardCoordinates[1] = y;
          }
        }
      }
			config.close();
		}
    void outputPlayersBoard(bool gameStarted, bool playersBoard){
      // board[0][0].hasShip = 'B';
      for (char letter = 'A'; letter <= 'J'; letter++){
        //change!! this for variable size
        cout << setw(4) << letter;
      }
      cout << endl;
      for (int i =0; i < board.size(); i++){
        int rowNumbers = i + 1;
        cout << setw(2) << rowNumbers;
        for (int j = 0; j < board[i].size(); j++){
           if (board[i][j].hit){
            cout << setw(2) << "H" << setw(2) << "|";
          } else if (board[i][j].hasShip && playersBoard){
            cout << setw(2) << board[i][j].hasShip << setw(2) << "|";
          } else if (board[i][j].hasMine == true && gameStarted == true){
            cout << setw(2) << "M" << setw(2) << "|";
          } else if(!board[i][j].hit){
            cout << setw(4) << " |" ;
          } 
        }
      cout << endl;
      }
    }
    void setShips(){
      boatClass gameBoatsClass;
      vector <boat> boatList = gameBoatsClass.getBoats();
      for (int i = 0; i < boatList.size(); i++){
        string choice;
        gameBoatsClass.listBoats();
        cout << endl << "Please choose where you want to place Boat "<< i + 1 << ":\n";
        getline(cin, choice);
        validateInput(choice);
        // cout << boatCoordinates[0] << ", " << boatCoordinates[1];
      }
    }
    bool validateInput(string input){
      int convertCharToCoord = 65;
      int convertIntToCoord = 48;
      int ten = 10;
      for (int i = 0; i < input.size(); i++){
        if(isalpha(input[i])){
          cout << "in alpha";
          int uppercaseChar = toupper(input[i]);
          boatCoordinates[0] += (uppercaseChar - convertCharToCoord);
          break;
        } else if(isdigit(input[i])){
          if(isdigit(input[i + 1])){
            string value = to_string(input[i]);
            int valueInt = stoi(value);
            int minus48 = valueInt -= convertIntToCoord;
            int finalNum = minus48 *= 10;


            string value2 = to_string(input[i + 1]);
            int valueInt2 = stoi(value2);
            int minus482 = valueInt2 -= convertIntToCoord;
            finalNum = finalNum + minus482;
            cout << finalNum; 
          }
          // cout << "in digit";
          // boardCoordinates[1] = input[i];
          // cout << boardCoordinates[1];
          break;
        } else {
          return false;
        }
      }
      if(validateCoord(boardCoordinates)){
        return true;
      }
      return false;
    }
    // int convertArrayToInt(int input){
    //   string value = to_string(input[i]);
    //   int valueInt = stoi(value);
    //   int minus48 = valueInt -= 48;
    // }
    bool validateCoord(int* boatCoord){
      return true;
    }
};
