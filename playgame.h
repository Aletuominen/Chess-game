#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


void movePiece(const bool whiteTurn, vector<string> &scoreSheet, map<string
			, string> &boardPosition, vector<string> boardOrder);
void playGame(map<string, string> boardPosition, vector<string> boardOrder);
string parseInput(const bool whiteTurn, const vector<string> &scoreSheet, 
	const map<string,string> &boardPosition, const vector<string> &boardOrder);