#include <iostream>
#include <fstream>//This allows my file to access a filestream
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int getIntFromFile(stringstream& lineStream, char delimiter);
void menu(void);
bool isNo(string input);
string convertToUpper(string word);


//Header files
#include "gameModes.h"
#include "board.h"

int main() {
  srand((unsigned) time(NULL));
  //to get a random number by using the time
  menu();
  return 0;
}

void menu(void) {
	string choice = "-1"; //declare and initialise an integer type variable
	do { //set up a continuous loop
		cout << "\nAdaShip! not like battleships in anyway:\n";
		cout << "\t1. One player v computer game\n";
    cout << "\t2. Two player game\n";
    cout << "\t3. One player v computer game (salvo)\n";
    cout << "\t4. Two player game (salvo)\n";
    cout << "\t5. One player v computer (hidden mines) game\n";
    cout << "\t6. Two player (hidden mines) game\n";
    cout << "\t7. Computer v computer (hidden mines) game\n";

		cout << "\n\t0. Quit\n";

		cout << "\nPlease enter option to run that type of game: ";
    getline(cin, choice);
    if(isNo(choice)){
      int choiceInt = stoi(choice);
      //Had to change the input because using cin and getline in the same application was causing bugs
      switch(choiceInt) {
        case 1: oneVsComp(); break;
        case 2: twoPlayerGame(); break;
        case 3: oneVsCompSalvo(); break;
        case 4: twoPlayerGameSalvo(); break;
        case 5: oneVsCompMines(); break;
        case 6: twoPlayerGameMines(); break;
        case 7: compVsCompMines(); break;
        
        case 0: cout << "Exiting"; break;
        default:
          cout << "\n'" << choice << "' Is an invalid option  - please try again.";
          break;
      }
    } else {
      cout << "\n'" << choice << "' Is an invalid option  - please try again.";
    }
	} while(choice != "0");
	cout << " - Done\n\n";
}

bool isNo(string input){
  for (int i = input.length() - 1; i >= 0; i--){
    //looping through the string to find if its a digit, if it isnt then return false
    if(!isdigit(input[i])){
      return false;
    } 
  }
  return true;
}

int getIntFromFile(stringstream& lineStream, char delimiter){
  string value;
  getline(lineStream, value, delimiter);
  //the value from before the delimiter
  int convertedToInt = stoi(value);
  //convert it to an int
  return convertedToInt;
}

string convertToUpper(string word){
  for (int i=0; i < word.length() ; i++ ){ 
      word[i] = toupper(word[i]);
      //iterating through each character to convert it to uppercase
  }
  return word;
}