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

    

	public: 
    controller(){}



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


};