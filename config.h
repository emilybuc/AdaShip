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
  bool hasShip;
  bool hasMine;
};

class controller {
	private: 
		vector <boat> boats;
    vector<vector<tile>> tiles;

	public: 
		void readConfig() {
			ifstream config;
      int i = 0;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':');
          if(lineType == "Board"){
            string xString, yString;
            getline(configStrStream, xString, 'x');
            getline(configStrStream, yString, 'x');
            int x = stoi(xString);
            int y = stoi(yString);
            setBoard(x, y);
          } else if(lineType == "Boat"){
            string typeOfBoat, tileSize;
            getline(configStrStream, typeOfBoat, ',');
            getline(configStrStream, tileSize, ','); 
            int tileSizeInt = stoi(tileSize);
            addBoat(typeOfBoat, tileSizeInt);
          }
          i++;
        }
      }
			config.close();
		}

    void setBoard(int x, int y){
      for(int xAxis = 0; xAxis <= x - 1; xAxis++){
        vector<tile>temp;
        for(int yAxis = 0; yAxis <= y - 1; yAxis++){
          // cout << "x =" << xAxis << endl;
          temp.push_back({false, false, false});
        }
        tiles.push_back(temp);
      }
      for (int i =0; i<tiles.size(); i++){
        for (int j = 0; j < tiles[i].size(); j++){
          cout << tiles[i][j].hit;
        }
      }
    }
		void addBoat(string name, int size) {
			if(findBoat(name) < 0) {
				boats.push_back({
					name,
					size
				});
			}
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

		int countBoats() {
			return boats.size();
		}

};


int config() {
  controller game;

	cout << "\n\nRead config file";
	game.readConfig();

	cout << "\n";
	return 0;
}