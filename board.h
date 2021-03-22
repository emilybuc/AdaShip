#pragma once
#include <iomanip>
#include <string>
#include <math.h> //floor
#include "boatConfig.h"

class boardClass {
  private:
    //set up my private variables
    vector<vector<tile>> board;
    //this is the 2d vector that will hold tiles
    int boardCoordinates[2];
    //this will be set from the adaship_config.ini and will be used to create the 2d vector
    int coordinates[2];
    //Im going to be using this throughout this class to know where i want to set the next coordinate, whether it be boat placement or missile placement
    boatClass gameBoatsClass;
    //set up an instance of boatClass so I can access the boats from my board class
    vector <boat> boatList;
    //my list of boats
    int tilesToHit;
    //this is the amount of tiles to hit to win the game, this is set when the boats are added to the board

  public:
    boardClass(){
      getConfigBoard();
      //set up the size of the board in this function
      gameBoatsClass.boatsFitOnBoard(boardCoordinates);
      //check that the amount of boats in the config will fit on the board
      boatList = gameBoatsClass.getBoats();
      //put the boats that have been set up into a vector
      coordinates[0] = 0;
      coordinates[1] = 0;
      tilesToHit = 0;
      //set these values to a default value;
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        vector<tile>temp;
        //create a temporary vector which will get pushed into the main vector to make up the 2d vector
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          temp.push_back({false, false, false});
          //fill the vector with default values 
        }
        board.push_back(temp);
        //push the temporary vector inside the board
      }
    }
    void outputBoard(){
      cout << "  ";
      for (int i = 0; i < boardCoordinates[0]; i++){
        //create the letters at the top based on how big the x axis is 
        char letter = 'A';
          if(i <= 25){
            letter = letter + i;
            //if the letters are only between A-Z just output these
            cout << "\t" << letter;
          } else if(i <= 51){
            int variation = i - 26;
            // this restart at A for the second letter
            letter = letter + variation;
            cout << "  A" << letter;
            //add an A to the start of the reference
          } else if(i <= 77){
            int variation = i - 52;
            //take away 52 to get back to the letter A
            letter = letter + variation;
            cout << "  B" << letter;
             //add a B to the start of the reference
          } else if(i <= 103){
            int variation = i - 78;
            //take away 78 to get back to the letter A
            letter = letter + variation;
            cout << "  C" << letter;
            //add a C to the start of the reference
          }
      }
      cout << endl;
      for (int i = 0; i < board.size(); i++){
        int rowNumbers = i + 1;
        cout << setw(2) << rowNumbers;
        //first set the row number
        for (int j = 0; j < board[i].size(); j++){
           if (board[j][i].hit == 'H'){
            cout << "\t" << board[j][i].hit;
            //if the tile has been hit then display H
          } else if (board[j][i].hit == 'M'){
            cout <<"\t" << board[j][i].hit;
            //if the tile has been hit but there was no ship then display M
          } else if (board[j][i].hasBoat && board[j][i].hasMine == true){
            cout << "  " << board[j][i].hasBoat << "/Ø";
            //if the tile has a boat and a mine then display the boat character and the mine character
          } else if (board[j][i].hasBoat){
            cout <<"\t" << board[j][i].hasBoat;
            //display boat character
          } else if (board[j][i].hasMine == true){
            cout << "\t" << "Ø" << setw(2);
            //display mine character
          } else {
            cout << "\t" << "-" ;
            //if the tile is empty 
          } 
        }
      cout << endl;
      }
    }

    void setBoatsMenu(){
      string input = "-1"; //declare and initialise an integer type variable
	    do { //set up a continuous loop
        cout << "\nPlease choose from the following options\n1. Set boats manually\n2. Automatically set boats \n0. Quit\n\nOption: ";
        //initial menu to ask if the user wants to set their own boats, automatically set them or quit
        getline(cin, input);
        cout << endl;
        if(isNo(input)){ //check if what they've entered is a number
          int inputInt = stoi(input); //convert to number
          switch(inputInt){ //switch statement for input
            case 1: 
              for (int i = 0; i < boatList.size(); i++){
                outputBoard(); //loop through the list of boats and set each one 
                string input;
                gameBoatsClass.listBoats(); //list all the boats
                cout << "\n\nPlease choose where you want the front of boat ("<< i + 1 <<") to go (eg. A5) or enter:\n1. To auto-place the rest of the boats\n2. To stop placing boats\n3. Reset Board\n0. To quit\n\nInput: ";
                //asking the user where they want to place the front of their boat
                getline(cin, input);
                if (input == "1"){
                  //if they type 1 then auto set their boats
                  autoSetBoats(i);
                  break;
                } else if (input == "2"){
                  //This option can be used if the user has a large amount of boats that could potentially fit on the board as this is checked beforehand but they havent placed them in an optimised way so they can carry on with the game
                  break;
                } else if(input == "3"){
                  i = 0;
                  //this doesnt reset the value to 0?
                  cout << "\nResetting board...\n";
                  resetBoard();
                } else if(input == "0"){
                  cout << "\nQuitting...\nGoodbye\n"; 
                  exit(0);
                  //quitting the game
                } else if (validateInput(input)){
                  //if they have put a valid coordinate in then ask them where they want the rest of their boat
                  cout << "\nPlease choose which direction you want the rest of the boat to go:\nL. Left\nR. Right\nU. Up\nD. Down\n\nInput: ";
                  getline(cin, input);
                  cout << endl;
                  if(!setBoat(input, boatList[i])){
                    cout << "\nYou cant place a boat here, please try again!\n\n";
                    i--;
                    //if they cant place a boat in the place they wanted to then output a message and go back to that boat by minusing i
                  }
                } else {
                  cout << "That coordinate cannot be placed please try again \n\n";
                  i--;
                  //if they've input a wrong coordinate then minus i and try again
                }
              }
              outputBoard();
              input = yOrN();
              //ask them if they are happy with the boat placement
              break;
            case 2: 
              autoSetBoats();
              //if they auto set boats call for this function to automatically set them
              outputBoard();
              input = yOrN();
              break;
            case 0: cout << "\nQuitting...\nGoodbye\n"; exit(0); break;
            default:
                cout << "\n'" << input << "' Is an invalid option  - please try again.";
                break;
            }; //error handling
        } else {
          cout << "\n'" << input << "' Is an invalid option  - please try again.\n"; 
        } //error handling
      } while(input != "0");
    }
    
    bool validateInput(string input){
      int convertCharToCoord = 65;
      //if you minus 65 from a char you will get the coordinates on the board
      string xCoord, yCoord;
      for (int i = 0; i < input.size(); i++){
        if(isalpha(input[i])){
          xCoord += input[i];
          //if the character is a letter then add it to this string, im splitting up the letters from numbers
        } else if(isdigit(input[i])){
          yCoord += input[i];
          //if the character is a number add it to this string
        } else {
          resetCoord();
          //if theyve inputted a special character return false and tell the user to input a correct coordinate
          return false;
        }
      }

      int xCoordInt = 0;
      xCoord = convertToUpper(xCoord);
      //convert this to uppercase

      for (int i = 0 ; i < xCoord.length(); i++){ // loop through xCoord
        if(xCoord.length() == 1){ //if the input only as one alpha digit just convert to coordinate
          xCoordInt = (xCoord[i] - convertCharToCoord);

        } else if (xCoord.length() == 2){ // if the letter part of the coordinate is double digits
          switch (i){
            case 0: // loop through each character of the string
             if(xCoord[i] == 'A'){
               xCoordInt += 26; //if character 1 is an A then add 26 to get the coordinates
             } else if (xCoord[i] == 'B'){
               xCoordInt += 52; //if character 1 is an A then add 52 to get the coordinates
             } else if (xCoord[i] == 'C'){
               xCoordInt += 78; //if character 1 is an A then add 78 to get the coordinates
             }
              break;
            case 1:
              xCoordInt += (xCoord[i] - convertCharToCoord); //add the second character onto the first one to get the final coordinate
              break;
          }
        } else {
          return false; //if there is no alpha characters in the coordinate then it is incorrect
        }
      }
      coordinates[0] = xCoordInt; //set the x coordinate
      coordinates[1] = stoi(yCoord) - 1; // convert the number portion of the coordinate to a number and minus 1 to get the coordinate

      if(validateCoord(coordinates)){
        //validate the coordinate to check it hasnt got a boat and is inside the board
        return true;
      } else {
        resetCoord();
        //if not then reset the coordinate variable and return false
        return false;
      }
    }

    void autoSetBoats(int i = 0){
      int amountOfTimesTried = 0;
      //this variable is set up so that the autoSetBoats only tries 100 times before carrying on with the game, if you have a lot of boats on the board and the computer has set them up so there isnt space for all of them it will only try 100 times before carrying on
      for (int j = i; j < boatList.size(); j++){
        randomCoordinates();
        //create random coordinates
        int movementOnXorY = rand() % 2;
        //randomly allocate if the boat is going to be placed sideways or upwards
        if(!validateBoatPlacement(boatList[j], movementOnXorY, -1) && amountOfTimesTried <= 100){ //pass the current boat, if its moving up or sideways, i also pass in -1 just for ease, as long as its random enough its ok
          resetCoord();
          j--;
          amountOfTimesTried++;
          // if the boat cant be placed then reset the coordinates and minus j 
        } else if(amountOfTimesTried > 100) {
          cout << "\nAmount of boats that can be placed has been met, please continue with set-up\n";
          //if the amount of boats has been met and the computer cannot place any more then continue
          break;
        } else {
          amountOfTimesTried = 0;
          //reset this value
          resetCoord();
        }
      }
    }

    int* getCoordinates(){
      return coordinates;
      //return coordinates to another function
    }

    bool setHit(){
      if(board[coordinates[0]][coordinates[1]].hasBoat && board[coordinates[0]][coordinates[1]].hasMine){ //use the coordinates array to find the coordinates on the board
        board[coordinates[0]][coordinates[1]].hit = 'H';
        //set the tile to = H
        tilesToHit--;
        //reduce this value so we know when the game ends
        mineExplosion();
        //call for the mine explosion function
        resetCoord();
        //reset the coordinates
        return true;
      } else if(board[coordinates[0]][coordinates[1]].hasMine){
        board[coordinates[0]][coordinates[1]].hit = 'H';
        //set tile to hit
        mineExplosion();
        //call for mine function
        resetCoord();
        return true;
      } else if(board[coordinates[0]][coordinates[1]].hasBoat){
        board[coordinates[0]][coordinates[1]].hit = 'H';
        //if the tile has a boat then set the tile to H for hit
        tilesToHit--; //minus the amount of tiles that need to be hit
        resetCoord();
        return true;
      } else {
        board[coordinates[0]][coordinates[1]].hit = 'M';
        //if none of these things are true then the missile has missed
        resetCoord();
        return false;
      }
    }
    void randomCoordinates(){
        bool loop = true;
        while(loop == true){
          coordinates[0] = rand() % boardCoordinates[0];
          coordinates[1] = rand() % boardCoordinates[1];
          //set a random coordinate that is within the board
          if(board[coordinates[0]][coordinates[1]].hit != 'H' || board[coordinates[0]][coordinates[1]].hit != 'M'){
            //as long as that value hasnt been hit before then carry on 
            loop = false;
          }
        }
        //set coordinates to a coordinate inside the board
    }
    bool hasGameEnded(){
      if(tilesToHit == 0){
        return true;
        //if there are no more tiles to hit then the game has ended
      } 
      return false;
    }
    int salvoMode(){
      int c = 0, b = 0, d = 0, s = 0, p = 0, numOfBoatsNotSunk = 0;
      //set up characters to be found to see how many ships are left
      for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++){
           if (board[i][j].hit == false && board[i][j].hasBoat){
             //if the boat hasnt been setHit
            switch(board[i][j].hasBoat) {
              case 'C': c++; break; 
              case 'B': b++; break;
              case 'D': d++; break;
              case 'S': s++; break;
              case 'P': p++; break;
              //add to these values
            }
          } 
        }
      }
      int boatsNotSunk[] = { c, b, d, s, p }; 
      //add them into an array
      for (int i = 0; i < 5; i++){ 
        if(boatsNotSunk[i] != 0){
          numOfBoatsNotSunk++;
          //if the values arent 0 then add to this variable
        }
      }
      return numOfBoatsNotSunk;
      //return how many boats havent been sunk
      //this function doesnt work if there is more than one of a particular type of boat
    }
    void setMines(){
      int loop = 5;
      //5 mines
      while(loop != 0){
        randomCoordinates();
        //get a random coordinate
        if(board[coordinates[0]][coordinates[1]].hasMine == false){
          //if the tile doesnt have a mine
          board[coordinates[0]][coordinates[1]].hasMine = true;
          //set the mine
          loop--;
        }
        resetCoord();
      }
    }
    bool setCoordinates(int x, int y){
      coordinates[0] = x; 
      coordinates[1] = y;
      //set up the coordinates from the input
      if(validateCoord(coordinates) && board[coordinates[0]][coordinates[1]].hit != 'H' && board[coordinates[0]][coordinates[1]].hit != 'M'){
        //if the coordinate hasnt been hit before then return true
        return true;
      } else {
        return false;
      }
    }

    
  private: 
    void getConfigBoard() {
			ifstream config;
      config.open("adaship_config.ini");
      //open the file
        if (config.is_open()){
        string line;
        while( getline(config,line)){
          //get each line and loop through
          stringstream configStrStream(line);
          string lineType;
          getline(configStrStream, lineType, ':');
          lineType = convertToUpper(lineType);
          //change to uppercase, this is for validation
          if(lineType == "BOARD"){
            //if the line is the board line
            int x = getIntFromFile(configStrStream, 'x');
            int y = getIntFromFile(configStrStream, 'x');
            //these functions return the line from the file and convert it to an int, it is in the main file
            if(x <= 80 && y <= 80 && x >= 5 && x >= 5){
              //if the coordinates are inbetween 5-80 then set the coordinates
              boardCoordinates[0] = x;
              boardCoordinates[1] = y;
            } else {
              cout << "\nBoard needs to be between 5 and 80 height and width\nPlease reconfigure the 'adaship_config.ini' file\nExiting\n";
              exit(0);
              //if not then exit and ask the user to change this
            }
          }
        }
      }
			config.close();
		}
    bool validateCoord(int* coord){
      if(coord[0] < boardCoordinates[0] && coord[1] < boardCoordinates[1] && coord[0] >= 0 && coord[1] >= 0){
        return true;
        //is the coordinate inside the board
      }
      return false;
    }

    void resetCoord(){
      coordinates[0] = 0;
      coordinates[1] = 0;
      //reset the coordinates back to 0
    }

    void inputBoatIntoCoordinate(boat currentBoat){
      char characterForBoard = currentBoat.name[0];
      //get the current boats name and get the first character
      board[coordinates[0]][coordinates[1]].hasBoat = characterForBoard;
      //change the tile to have a boat in it and set the character for the board
    }

    bool validateBoatPlacement(boat currentBoat, int movementOnXorY, int plusOrMinus1){
      int localBoatCoordinates[2] = { coordinates[0], coordinates[1] };
      //set a local variable
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        if(!validateCoord(localBoatCoordinates)){
          return false;
          //if the coordinate isnt valid then return false
        } else if(tileHasBoat(localBoatCoordinates) == true){
          return false;
          //if the tile is already occupied by a boat then return false
        } else {
          localBoatCoordinates[movementOnXorY] += plusOrMinus1;
          //I am checking before I actually input the values into the board whether the space is free and inside the board 
        }
      }
      for(int i = 0; i <= currentBoat.size - 1 ; i++){
        inputBoatIntoCoordinate(currentBoat);
        //placing the character into that coordinate
        coordinates[movementOnXorY] += plusOrMinus1;
        //moving the coordinate to the next tile
        tilesToHit++;
        //adding to the number of tiles that need to be hit for the game to be won
      }
      return true;
    } 
    bool tileHasBoat(int* localBoatCoordinates){
      if(!board[localBoatCoordinates[0]][localBoatCoordinates[1]].hasBoat){
        //if the tile does not have a boat return false
        return false;
      } else {
        return true;
      }
    }
    bool setBoat(string direction, boat currentBoat){
      bool successfulBoatPlacement;
      if (direction == "L" || direction == "l"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, -1);
        //the second argument is whether were moving the x axis or y axis and the third argument is what plane were moving on 
      } else if (direction == "R" || direction == "r"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 0, 1);

      } else if (direction == "U" || direction == "u"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, -1);

      } else if (direction == "D" || direction == "d"){
        successfulBoatPlacement = validateBoatPlacement(currentBoat, 1, 1);

      } else {
        cout << "\nThe character you entered was incorrect, try again\n";
        //if they didnt enter in a correct character
        return false;
      }
      resetCoord();
      if(successfulBoatPlacement == true){
        //if the placement was correct then reset the coordinates
        return true;
      } else {
        return false;
      }
    }
    void resetBoard(){
      for(int xAxis = 0; xAxis <= boardCoordinates[0] - 1; xAxis++){
        for(int yAxis = 0; yAxis <= boardCoordinates[1] - 1; yAxis++){
          board[xAxis][yAxis] = {false, false, false};
        }
      }
      //reset the whole board to false 
    }
    string yOrN(){
      string inputTryAgain; 
      cout << "\nAre you happy with this placement? Please type Y/N: ";
      getline(cin, inputTryAgain);
      //asking for Y/N input
      if(inputTryAgain == "Y" || inputTryAgain == "y"){
        return "0";
        //If yes then exit and go 
      } else if (inputTryAgain == "N" || inputTryAgain == "n"){
        cout << "Ok, please retry placing boats\n";
        resetBoard();
        return "-1";
        //exit
      } else {
        cout << "invalid input, try again \n";
        yOrN();
        //fall back if they enter something else
      }
      return "-1";
    }

    void mineExplosion(){
      int localCoord[] = { coordinates[0], coordinates[1] }; 
      //create a local variable so i can save the coordinate that the mine is occupying
      updateCoordToNewCoord(localCoord, -1, -1);
      updateCoordToNewCoord(localCoord, -1, 0);
      updateCoordToNewCoord(localCoord, -1, 1);
      updateCoordToNewCoord(localCoord, 0, -1);
      updateCoordToNewCoord(localCoord, 0, 1);
      updateCoordToNewCoord(localCoord, 1, -1);
      updateCoordToNewCoord(localCoord, 1, 0);
      updateCoordToNewCoord(localCoord, 1, 1);
      //hit all of the 8 squares around where the mine is
    }

    void updateCoordToNewCoord(int* localCoord, int xAxisMovement, int yAxisMovement){
      coordinates[0] += xAxisMovement;
      coordinates[1] += yAxisMovement;
      //update coordinates to the new x and y axis
      if(validateCoord(coordinates)){
        //if they are valid coordinates
        setHit();
        //set as hit
      }
      coordinates[0] = localCoord[0];
      coordinates[1] = localCoord[1];
      //change the coordinates back to the original coordinates for the next function call

      // when a mine hits another mine then it errors, that is because theres two of the same function running, I did not have enough time to fix this
    }
};