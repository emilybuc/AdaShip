#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct boat {
	string name;
	int size;
};
struct tile {
  char hit;
  char hasBoat;
  bool hasMine;
};