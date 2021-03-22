#pragma once

class boatClass {
  private: 
    vector <boat> boats;
    int amountOfBoatTiles;
    //set up my private variables
  public: 
  boatClass(){
    amountOfBoatTiles = 0;
    //set up the default 
    ifstream config;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){ // read each line
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':'); // break on : 
          lineType = convertToUpper(lineType); //change the lineType to upper case for validation
          if(lineType == "BOAT"){
            string typeOfBoat;
            getline(configStrStream, typeOfBoat, ','); // make this into the type of boat
            int tileSize = getIntFromFile(configStrStream, ',');  // and get the tile size, this function returns an int
            amountOfBoatTiles += tileSize;
            addBoat(typeOfBoat, tileSize);
            //add the boat into the vector of boats
          }
        }
      }
			config.close(); // close config
  }
  
  void listBoats() {
    for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
      cout << "\nBoat " << i + 1 << ": " << boats[i].name << " (" << boats[i].size << ")";
    } // output the list of boats
  }
  void addBoat(string name, int size) {
      boats.push_back({
        name,
        size
      }); // add the boat into the boats vector
  }
 vector <boat> getBoats(){
   return boats;
 }// return the vector of boats
 bool boatsFitOnBoard(int* boardSize){
   int boardArea = boardSize[0] * boardSize[1];
   //get the board area
   if(amountOfBoatTiles < boardArea){
     return true;
     //check that the amount of tiles that the boats occupy will actually fit on the board that has been configured
   } else {
     cout << "\nToo many boats for the size of board please reconfigure the 'adaship_config.ini' and restart\n";
     //if the board is too small for the amount of boats then exit the program and ask them to reconfigure the file
     exit(0);
     return false;
   }
 }
};