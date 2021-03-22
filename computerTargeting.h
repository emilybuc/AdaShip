#pragma once

class computerTargeting {
  private: 
    struct coordinates {
      int x;
      int y;
      bool hit;
    };
    //local object for coordinates so the computer player knows which was the last coordinates that were hit
    vector <coordinates> coordOfHit;
    //store these in a vector

    void setCoordOfHit(coordinates coordinateToAdd){
      coordOfHit.push_back({ coordinateToAdd });
      //private function to add a new coordinate to the vector
    }

  public: 
  computerTargeting(){
    setCoordOfHit({ 0, 0, false });
    //Initalise one value so the if statement doesnt error
  }
  void shootMissile(boardClass &board, bool salvoMode = false, string boardTitle = "Your Updated Board"){ //I am passing in the reference to the board so that when I change anything in the board I am updating the original class, I am also using a default parameter for the output string
  //I am also taking in a salvoMode variable because I dont want the board output and enter key every time a missile is shot
    int coordOfHitIndex = coordOfHit.size() - 1;
    //the size of the coordOfHit vector
    while (0 <= coordOfHitIndex){
      //loop through the whole of the coordOfHit vector
      //I am starting at the end of the vector to find the most recently hit coordinate
      if(coordOfHit[coordOfHitIndex].hit){
        //break when youve found the index of the most recently hit coordinate
        break;
      }
      coordOfHitIndex--;
      //go backwards through the vector
    }
    if(coordOfHit[coordOfHitIndex].hit){
      // if a coordinate that has been hit can be found then call for seek target function
      seekTarget(board, coordOfHitIndex);
    } else {
      board.randomCoordinates();
      //if no coordinates can be found then choose random coordinates
    }
    int localCoords[2];
    localCoords[0] = board.getCoordinates()[0];
    localCoords[1] = board.getCoordinates()[1];
    //get the coordinates of the coordinates that are about to be hit
    if(board.setHit()){
      setCoordOfHit({ localCoords[0], localCoords[1], true });
      //if the coordinates were hit then add to the vector saying true
      cout << "\nMissile hit!\n";
      //output message
      } else {
      setCoordOfHit({ localCoords[0], localCoords[1], false });
      //if the coordinates were hit then add to the vector saying false
      cout << "\nMissile missed!\n";
      //output message
    }

    string endTurn;
    if(!salvoMode){
      //if salvo mode is false then output the board and enter key
      cout << "\n" << boardTitle << "\n";
      board.outputBoard();
      cout << "\nEnter any key to finish the computers turn: ";
      getline(cin, endTurn);
    }
  }
  void seekTarget(boardClass &board, int coordOfHitIndex){
    //reference pointer to the board
    int directions[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
    //these are the 4 directions that a boat could be in if the middle square had been hit
    for(int i = 0; i <= 3; i++){
      int xMovement = directions[i][0]; 
      int yMovement = directions[i][1]; 
      //get the first movement 
      //I did originally make this a random selection from the directions array but sometimes it would choose the same direction more than once and then would default to a random coordinate so i thought it would be more efficient if it cycled through them instead of just defaulting to random if it couldnt find a coordinate to hit

      int x = coordOfHit[coordOfHitIndex].x + xMovement;
      int y = coordOfHit[coordOfHitIndex].y + yMovement;
      //change the x and y to the new coordinate that wants to be hit

      if(board.setCoordinates(x, y)){
        // loop through the directions and check if they can be hit
        break;
      } else if (i == 3){
        board.randomCoordinates();
        //All squares around the hit tile have already been hit try a random coordinate
        break;
      }
    }
  }
};