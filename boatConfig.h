#pragma once


class boatClass {
  private: 
    vector <boat> boats;
  public: 
  boatClass(){
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
			config.close();
  }
  
  void listBoats() {
    for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
      std::cout << "\nBoat " << i << ": " << boats[i].name << " (" << boats[i].size << ")";
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
  int findBoat(std::string name) {
    for (int i = 0; i < boats.size(); i++ ) {	//loop through each boat		
      if(boats[i].name == name) { //matching name found?
        return i; //return index position
      }
    }
  return -1; //return invalid index as no match found
}
};