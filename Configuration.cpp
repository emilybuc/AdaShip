#include <fstream>//This allows my file to access a filestream
#include <sstream>//String stream 
#include "Configuration.h"
using namespace std;


Configuration::Configuration(){
  ifstream config;
      int i = 0;
      config.open("adaship_config.ini");
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          stringstream configStrStream(line);
          //Assign a string stream from each line of the csv so i can access data from inside the string
          string lineType;
          getline(configStrStream, lineType, ':');
          if(lineType == "Board"){
            string x, y;
            getline(configStrStream, x, 'x');
            getline(configStrStream, y, 'x');
            currentGameboard = {x , y};
          } else if(lineType == "Boat"){
            string typeOfBoat, tileSize;
            getline(configStrStream, typeOfBoat, ',');
            getline(configStrStream, tileSize, ','); 
            arrayOfBoats[i] = { typeOfBoat, tileSize };
          }
          i++;
        }
      }
};

// Configuration::getBoard(){
//   return currentGameboard;
// }

// class Configuration{
//   private:
//     struct Boat {
//       string typeOfBoat;
//       string tileSize;
//     };
//     struct Board {
//       string x;
//       string y;
//     };
//     Boat arrayOfBoats[5];
//     Board currentGameboard;
//   public:
//     Configuration(){
      
//     }
//   Board getBoard(){
//     
//   }
//   Boat* getBoats(){
//     return arrayOfBoats;
//   }
// };
