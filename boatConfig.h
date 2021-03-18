#pragma once

class boatClass {
  private: 
    vector <boat> boats;
    int amountOfBoatTiles;
  public: 
  boatClass(){
    amountOfBoatTiles = 0;
    ifstream config;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':');
          lineType = convertToUpper(lineType);
          if(lineType == "BOAT"){
            string typeOfBoat;
            getline(configStrStream, typeOfBoat, ',');
            int tileSize = getIntFromFile(configStrStream, ','); 
            amountOfBoatTiles += tileSize;
            addBoat(typeOfBoat, tileSize);
          }
        }
      }
			config.close();
  }
  
  void listBoats() {
    for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
      cout << "\nBoat " << i + 1 << ": " << boats[i].name << " (" << boats[i].size << ")";
    }
  }
  void addBoat(string name, int size) {
      boats.push_back({
        name,
        size
      });
  }
 vector <boat> getBoats(){
   return boats;
 }
 bool boatsFitOnBoard(int* boardSize){
   int boardArea = boardSize[0] * boardSize[1];
   if(amountOfBoatTiles < boardArea){
     return true;
   } else {
     cout << "\nToo many boats for the size of board please reconfigure the 'adaship_config.ini' and restart\n";
     exit(0);
     return false;
   }
 }
};