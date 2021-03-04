#pragma once

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
    
    void outputBoard(){
      for (int letter = 0; letter < board.size(); letter++){
        cout << letter; 
      }
      cout << endl;
      for (int i =0; i < board.size(); i++){

        for (int j = 0; j < board[i].size(); j++){
          cout << board[i][j].hit;
        }
      }
    }
};