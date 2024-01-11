#include "functions.h"

// W = White, B = Black. Pieces numbered from left to right, bottom up.
const vector<string> whitePieces = { "WR1", "WN1", "WB1", "WQ", "WK" , "WB2" , "WN2" , "WR2"
								, "WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"
};
const vector<string> blackPieces = { "BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"
									, "BR1", "BN1", "BB1", "BQ", "BK" , "BB2" , "BN2" , "BR2"
};

void printBoard(const map<string, string> &boardPosition, const vector<string> &boardOrder) {

	vector<string> printRow; // Arrange squares for printing
	auto it2 = boardOrder.rbegin();

	for (int i = 63; i > -1; it2++, i--) {

		printRow.push_back(boardPosition.at(boardOrder.at(i)));
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
vector<string> findLegalMoves(bool whiteTurn, string piece, map<string, string> boardPosition)
{

	stringstream ss;
	vector<string> moves = {};
	ss << piece[1] << findPiecePosition(piece, boardPosition); // e.g. PA2

	if (piece[1] == 'P' && whiteTurn) {
		moves = moveWhitePawn(ss.str(), boardPosition);
	}
	
	/* Executed in other functions
	for (int i = 0; i < moves.size(); ++i) {

		moves[i] = checkCollision(whiteTurn, moves[i], boardPosition);
	}
	*/
	return moves;
}

vector<string> checkDiagonals(bool whiteTurn, string piece, map<string, string> boardPosition)
{
	char file = piece[1];
	char rank = piece[2];
	
	vector<string> moves = {};
	string nextMove = "";
	// cout << string{file} << " and " << rank << endl;

	while (file <= 'H' && rank <= 8) {

		++file;
		++rank;
		nextMove = checkCollision(whiteTurn, string{ file, rank }, boardPosition);
		if (nextMove != "") {
			moves.push_back(nextMove);
		}
	}
	return moves;
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

vector<string> moveWhitePawn(string piecePos, map<string, string> boardPosition)
{
	vector<string> moves = {};
	char file = piecePos[1];
	char rank = piecePos[2];

	string nextMove = checkCollision(true, string{ file, char(rank+1) }, boardPosition);

	if (nextMove != "" && nextMove.size() < 3) { // nextMove would be e.g. A2x if there's something
												 // to capture but pawns cannot capture forward
		moves.push_back(nextMove);

		// If a collision happened 1 square ahead, no need to check 2 squares
		if (rank == '2') {
			nextMove = checkCollision(true, string{ file, char(rank + 2) }, boardPosition);
			if (nextMove != "" && nextMove.size() < 3) { 
				moves.push_back(nextMove);
			}
		}
	}
	if (file > 'A') {
		nextMove = checkCollision(true, string{ char(file-1), char(rank+1)}, boardPosition);
		if (nextMove != "" && nextMove.size() == 3) { // Pawns must be able to capture to move diagonally
			moves.push_back(nextMove);
		}
	}
	if (file < 'H') {
		nextMove = checkCollision(true, string{ char(file + 1), char(rank+1) }, boardPosition);
		if (nextMove != "" && nextMove.size() == 3) {
			moves.push_back(nextMove);
		}
	}

	// TODO: En passant. If rank == 6, check previous move

	return moves;

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

	if (boardPosition[position] == ".") {
		return position;
	}
	else if (boardPosition[position][0] == turn) {
		return "";
	}
	else {
		return position + 'x';
	}
	

}
