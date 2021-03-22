#pragma once

class computerTargeting {
  private: 
    struct coordinates {
      int x;
      int y;
      bool hit;
    };
    vector <coordinates> coordOfHit;

    void setCoordOfHit(coordinates coordinateToAdd){
      coordOfHit.push_back({ coordinateToAdd });
    }

  public: 
  computerTargeting(){
    setCoordOfHit({ 0, 0, false });
    //Initalise one value so the if statement doesnt error
  }
  void shootMissile(boardClass &board, bool salvoMode, string boardTitle = "Your Updated Board"){
    int coordOfHitIndex = coordOfHit.size() - 1;
    while (0 <= coordOfHitIndex){
      if(coordOfHit[coordOfHitIndex].hit){
        break;
      }
      coordOfHitIndex--;
    }
    if(coordOfHit[coordOfHitIndex].hit){
      seekTarget(board, coordOfHitIndex);
    } else {
      board.randomCoordinates();
    }
    int localCoords[2];
    localCoords[0] = board.getCoordinates()[0];
    localCoords[1] = board.getCoordinates()[1];
    if(board.setHit()){
      setCoordOfHit({ localCoords[0], localCoords[1], true });
      cout << "\nMissile hit!\n";
      } else {
      setCoordOfHit({ localCoords[0], localCoords[1], false });
      cout << "\nMissile missed!\n";
    }

    string endTurn;
    if(!salvoMode){
      cout << "\n" << boardTitle << "\n";
      board.outputBoard();
      cout << "\nEnter any key to finish the computers turn: ";
      getline(cin, endTurn);
    }
  }
  void seekTarget(boardClass &board, int coordOfHitIndex){
    int directions[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
    for(int i = 0; i <= 3; i++){
      int xMovement = directions[i][0]; 
      int yMovement = directions[i][1]; 

      int x = coordOfHit[coordOfHitIndex].x + xMovement;
      int y = coordOfHit[coordOfHitIndex].y + yMovement;

      if(board.setCoordinates(x, y)){
        break;
      } else if (i == 3){
        board.randomCoordinates();
        //All squares around the hit tile have already been hit try a random coordinate
        break;
      }
    }
  }
};