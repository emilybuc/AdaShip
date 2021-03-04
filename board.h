#pragma once
#include <iomanip>

class boardClass {
  private:
    vector<vector<tile>> board;
  public:
    boardClass(int x, int y){
      for(int xAxis = 0; xAxis <= x - 1; xAxis++){
        vector<tile>temp;
        for(int yAxis = 0; yAxis <= y - 1; yAxis++){
          temp.push_back({false, false, false});
        }
        board.push_back(temp);
      }
      // for (int i =0; i<tiles.size(); i++){
      //   for (int j = 0; j < tiles[i].size(); j++){
      //     cout << tiles[i][j].hit;
      //   }
      // }
    }
    
    void outputPlayersBoard(bool gameStarted, bool playersBoard){
      // board[0][0].hasShip = 'B';
      for (char letter = 'A'; letter <= 'J'; letter++){
        //change!! this for variable size
        cout << setw(4) << letter;
      }
      cout << endl;
      for (int i =0; i < board.size(); i++){
        int rowNumbers = i + 1;
        cout << setw(2) << rowNumbers;
        for (int j = 0; j < board[i].size(); j++){
           if (board[i][j].hit){
            cout << setw(2) << "H" << setw(2) << "|";
          } else if (board[i][j].hasShip && playersBoard){
            cout << setw(2) << board[i][j].hasShip << setw(2) << "|";
          } else if (board[i][j].hasMine == true && gameStarted == true){
            cout << setw(2) << "M" << setw(2) << "|";
          } else if(!board[i][j].hit){
            cout << setw(4) << " |" ;
          } 
      }
      cout << endl;
    }
    }
};