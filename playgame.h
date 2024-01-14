#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Takes move command as input from user, validates move and updates game board / scoresheet
// Return 1 if move successful, otherwise return 0
int movePiece(const bool whiteTurn, vector<string> &scoreSheet, map<string
			, string> &boardPosition, const vector<string> &boardOrder);

void playGame(map<string, string> boardPosition, const vector<string> &boardOrder);
string parseInput(const bool whiteTurn, const vector<string> &scoreSheet, 
	const map<string,string> &boardPosition, const vector<string> &boardOrder);
void updateBoard(map<string, string>& boardPosition, const string& piecePosition, string input,
				const string& selectedMove, vector<string> &scoreSheet);
string selectMove(map<string,string> const &boardPosition, const vector<string> &legalMoves, 
				const string &piecePosition);
