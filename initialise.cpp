#include "initialise.h"
#include "functions.h"
#include "playgame.h"


void setupBoard(){

	// Use a parallel implementation of map and vector to allow indexing
	// by either square index (0-63) or square notation (A1-H8)
	map<string, string> boardPosition = {};
	vector<string> boardOrder = {};

	//Initialise boardPosition map with square notation (A1-H8)
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			char A = 'A' + x;
			string xString(1, A);
			xString.append(to_string(y + 1));
			boardPosition[xString] = ".";
			boardOrder.push_back(xString);
		}
	}
	startingPieces(boardPosition, boardOrder);
	//printBoard(boardPosition, boardOrder);
	playGame(boardPosition, boardOrder);
}

