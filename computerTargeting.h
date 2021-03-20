#pragma once

class computerTargeting {
  private: 
    struct coordinates {
      int x;
      int y;
      bool hit;
      string foundShip;
    };
    vector <coordinates> coordOfhit;

  public: 
  computerTargeting(){}

  void shootMissile(boardClass &board, bool salvoMode){
    // if(coordOfhit[coordOfhit.size()-1].foundShip){
    //   seekTarget();
    // } else {
      board.randomCoordinates();
    // }
    int localCoords[2];
    localCoords[0] = board.getCoordinates()[0];
    localCoords[1] = board.getCoordinates()[1];
    if(board.setHit()){
      coordOfhit.push_back({
        localCoords[0],
        localCoords[1],
        true,
       });
      // cout << coordOfhit[0].x << ", "<< coordOfhit[0].y;
      cout << "\nComputers missile hit!\n";
      } else {
      coordOfhit.push_back({
        localCoords[0],
        localCoords[1],
        false
       });
      cout << "\nComputers missile missed\n";
    }
    string endTurn;
    if(!salvoMode){
      cout << "Enter any key to finish the computers turn: ";
      getline(cin, endTurn);
    }
  }
  void seekTarget(){
    int coordOfhitSize = coordOfhit.size() - 1;
    
  }
};