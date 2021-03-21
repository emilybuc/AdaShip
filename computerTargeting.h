#pragma once

class computerTargeting {
  private: 
    struct coordinates {
      int x;
      int y;
      bool hit;
    };
    vector <coordinates> coordOfhit;

    void setCoordOfHit(coordinates coordinateToAdd){
      coordOfhit.push_back({ coordinateToAdd });
    }

  public: 
  computerTargeting(){
    setCoordOfHit({ 0, 0, false });
    //Initalise one value so the if statement doesnt error
  }
  void shootMissile(boardClass &board, bool salvoMode){
    if(coordOfhit[coordOfhit.size() - 1].hit){
      seekTarget(board);
    } else {
      board.randomCoordinates();
    }
    int localCoords[2];
    localCoords[0] = board.getCoordinates()[0];
    localCoords[1] = board.getCoordinates()[1];
    if(board.setHit()){
      setCoordOfHit({ localCoords[0], localCoords[1], true });
      cout << "\nComputers missile hit!\n";
      } else {
      setCoordOfHit({ localCoords[0], localCoords[1], false });
      cout << "\nComputers missile missed\n";
    }
    string endTurn;
    if(!salvoMode){
      cout << "Enter any key to finish the computers turn: ";
      getline(cin, endTurn);
    }
  }
  void seekTarget(boardClass &board){
    int coordOfhitSize = coordOfhit.size() - 1;
    int randomDirection = rand() % 4;

    int directions[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
    int xMovement = directions[randomDirection][0]; 
    int yMovement = directions[randomDirection][1]; 

    int x = coordOfhit[coordOfhitSize].x += xMovement;
    int y = coordOfhit[coordOfhitSize].y += yMovement;

    if(board.setCoordinates(x, y)){
      return;
    } else {
      seekTarget(board);
    }
  }
};