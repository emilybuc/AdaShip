#include <iostream>
#include <fstream>//This allows my file to access a filestream
#include <sstream>
#include <string>
using namespace std;

int getIntFromFile(stringstream& lineStream, char delimiter);
void menu(void);
bool isNo(string input);


//Header files
#include "game.h"



int main() {
  menu();
  return 0;
}

void menu(void) {
	string choice = "-1"; //declare and initialise an integer type variable
	do { //set up a continuous loop
		cout << "\nAdaShip! not like battleships in anyway:\n";
		cout << "\t1. One player v computer game\n";

		cout << "\n\t0. Quit\n";

		cout << "\nPlease enter option to run primer (e.g. 1 for Primer 01): ";
    getline(cin, choice);
    if(isNo(choice)){
      int choiceInt = stoi(choice);
      //Had to change the input because using cin and getline in the same application was causing bugs
      switch(choiceInt) {
        case 1: OneVsComp(); break;
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
      if(input[i] == '-' && i == 0){
        return true;
        //Checking if the first digit is a - (for a minus number)
      }
      return false;
      //if it isnt a digit then return 
    } 
  }
  return true;
}

int getIntFromFile(stringstream& lineStream, char delimiter){
  string value;
  getline(lineStream, value, delimiter);
  int convertedToInt = stoi(value);
  return convertedToInt;
}