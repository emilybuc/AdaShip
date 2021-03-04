#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct boat {
	string name;
	int size;
};
struct tile {
  bool hit;
  char hasShip;
  bool hasMine;
};

class controller {
	private: 
		vector <boat> boats;
    int boardCoordinates[2];

	public: 
    controller(){}
		int* getConfigBoard() {
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
      return boardCoordinates;
			config.close();
		}
    vector <boat> getConfigBoats() {
			ifstream config;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':');
          if(lineType == "Boat"){
            string typeOfBoat;
            getline(configStrStream, typeOfBoat, ',');
            int tileSize = getIntFromFile(configStrStream, ','); 
            addBoat(typeOfBoat, tileSize);
          }
        }
      }
      return boats;
			config.close();
		}

    // void setBoard(int x, int y){
    //   for(int xAxis = 0; xAxis <= x - 1; xAxis++){
    //     vector<tile>temp;
    //     for(int yAxis = 0; yAxis <= y - 1; yAxis++){
    //       temp.push_back({false, false, false});
    //     }
    //     board.push_back(temp);
    //   }
    //   // for (int i =0; i<tiles.size(); i++){
    //   //   for (int j = 0; j < tiles[i].size(); j++){
    //   //     cout << tiles[i][j].hit;
    //   //   }
    //   // }
    // }
		void addBoat(string name, int size) {
			if(findBoat(name) < 0) {
				boats.push_back({
					name,
					size
				});
			}
		}

    int getIntFromFile(stringstream& lineStream, char delimiter){
      string value;
      getline(lineStream, value, delimiter);
      int convertedToInt = stoi(value);
      return convertedToInt;
    }

    void listBoats() {
			for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
				std::cout << "\nBoat " << i << ": " << boats[i].name << " (" << boats[i].size << ")";
			}
		}

		int findBoat(string name) {
			for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
				if(boats[i].name == name) { //matching name found?
					return i; //return index position
				}
			}
			return -1; //return invalid index as no match found
		}
};