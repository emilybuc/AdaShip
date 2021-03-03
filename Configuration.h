#pragma once 
using namespace std;
#include <fstream>//This allows my file to access a filestream
#include <sstream>//String stream 
#include <string>
// struct Boat {
//   string typeOfBoat;
//   string tileSize;
// };

// struct Board {
//   string x;
//   string y;
// };

class Configuration {
  private:
    // Boat arrayOfBoats[5];
    // Board currentGameboard;
  public:
    Configuration(){
      cout << "hello";
    };
    void getBoard(){
      cout << "board";
    }
};