#include "functions.h"

// W = White, B = Black. Pieces numbered from left to right, bottom up.
const vector<string> whitePieces = { "WR1", "WN1", "WB1", "WQ", "WK" , "WB2" , "WN2" , "WR2"
								, "WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"
};
const vector<string> blackPieces = { "BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"
									, "BR1", "BN1", "BB1", "BQ", "BK" , "BB2" , "BN2" , "BR2"
};

void printBoard(map<string, string> boardPosition, vector<string> boardOrder) {

	vector<string> printRow; // Arrange squares for printing
	auto it2 = boardOrder.rbegin();

	for (int i = 63; i > -1; it2++, i--) {

		printRow.push_back(boardPosition[boardOrder[i]]);
		if (printRow.size() == 8) {
			for (int cell = 0; cell < 8; cell++) {
				cout << setw(5) << printRow[7 - cell];
			}
			cout << endl;
			printRow.clear();
		}
	}
}
// Separate function for each piece type?
vector<string> legalMoves(bool whiteTurn, string piece, map<string, string> boardPosition)
{

	stringstream ss;
	ss << piece[1] << findPiecePosition(piece, boardPosition); // e.g. PA2
	vector<string> moves = checkDiagonals(ss.str(), boardPosition);
	

	for (auto move : moves) {
		move = checkCollision(whiteTurn, move, boardPosition);
	}

	return moves;
}

vector<string> checkDiagonals(string piece, map<string, string> boardPosition)
{
	char file = piece[1];
	char rank = piece[2];
	char file1 = file - 1;
	char rank1 = rank + 1;
	
	file += 1;
	rank += 1;
	
	// cout << string{file} << " and " << rank << endl;

	string square1 = string{ file, rank };
	string square2 = string{ file1, rank1 };


	return {square1, square2};

	// Need to check which pieces are on the tiles
	return { boardPosition[to_string(file + 1) + to_string(rank + 1)],
			boardPosition[to_string(file - 1) + to_string(rank + 1)]
	};
}

vector<string> checkLines(string piece, map<string, string> boardPosition)
{
	return vector<string>();
}

bool checkmate(map<string, string> boardPosition, bool whiteTurn)
{
	return false;
}

void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder) {
	// Place the pieces in their starting positions
	auto it = boardOrder.begin();
	for (int i = 0; i < 16; it++, i++) {
		boardPosition[boardOrder[i]] = whitePieces[i];
	}

	auto it2 = boardOrder.rbegin();
	for (int i = 0; i < 16; it2++, i++) {
		boardPosition[boardOrder[i + 48]] = blackPieces[i];
	}

}

string findPiecePosition(string piece, map<string, string> boardPosition)
{
	for (auto it = boardPosition.begin(); it != boardPosition.end(); it++) {
		if (piece == it->second) {
			return it->first;
		}
	}
	return "";
}

// Free square: return original square
// Occupied by friendly piece: return empty string
// Occupied by opponent piece: return original square and x
string checkCollision(bool whiteTurn, string position, map<string, string> boardPosition){

	char turn = whiteTurn ? 'W' : 'B';

	if (boardPosition[position] == "") {
		return position;
	}
	else if (boardPosition[position][0] == turn) {
		return "";
	}
	else {
		return position + 'x';
	}
	

}
