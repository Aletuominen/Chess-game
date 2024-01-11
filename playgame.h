#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;


void movePiece(bool whiteTurn, map<string, string> boardPosition, vector<string> boardOrder);
void playGame(map<string, string> boardPosition, vector<string> boardOrder);
int parseInput(bool whiteTurn, string input, const map<string,string> &boardPosition, const vector<string> &boardOrder);