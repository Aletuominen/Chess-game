#include "functions.h"

// W = White, B = Black. Pieces numbered from left to right, bottom up.
const vector<string> whitePieces = { "WR1", "WN1", "WB1", "WQ1", "WK" , "WB2" , "WN2" , "WR2"
								, "WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"
};
const vector<string> blackPieces = { "BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"
									, "BR1", "BN1", "BB1", "BQ1", "BK" , "BB2" , "BN2" , "BR2"
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

vector<string> findLegalMoves(const bool whiteTurn, string piece, map<string, string> boardPosition)
{

	vector<string> moves = {};

	if (piece[1] == 'P' && whiteTurn) {
		moves = moveWhitePawn(findPiecePosition(piece, boardPosition), boardPosition);
	}
	else if (piece[1] == 'P' && !whiteTurn) {
		moves = moveBlackPawn(findPiecePosition(piece, boardPosition), boardPosition);
	}
	else if (piece[1] == 'B') {
		moves = diagonalMoves(whiteTurn, findPiecePosition(piece, boardPosition), boardPosition);
	}
	else if (piece[1] == 'R') {
		moves = lineMoves(whiteTurn, findPiecePosition(piece, boardPosition), boardPosition);
	}
	else if (piece[1] == 'Q') {
		moves = lineMoves(whiteTurn, findPiecePosition(piece, boardPosition), boardPosition);
		vector<string> diagMoves = diagonalMoves(whiteTurn, findPiecePosition(piece, boardPosition), boardPosition);
		moves.insert(moves.end(), diagMoves.begin(), diagMoves.end());
	}
	else if (piece[1] == 'N') {
		moves = knightMoves(whiteTurn, findPiecePosition(piece, boardPosition), boardPosition);
	}

	return moves;
}

vector<string> lineMoves(const bool whiteTurn, string position, const map<string, string>& boardPosition)
{
	vector<string> moves = {};

	moveLoop(whiteTurn, position, 1, 0, moves, boardPosition);
	moveLoop(whiteTurn, position, 0, 1, moves, boardPosition);
	moveLoop(whiteTurn, position, -1, 0, moves, boardPosition);
	moveLoop(whiteTurn, position, 0, -1, moves, boardPosition);

	return moves;

}

vector<string> diagonalMoves(const bool whiteTurn, string position, const map<string, string> &boardPosition)
{
	vector<string> moves = {};

	moveLoop(whiteTurn, position, -1, -1, moves, boardPosition);
	moveLoop(whiteTurn, position, 1, -1, moves, boardPosition);
	moveLoop(whiteTurn, position, -1, 1, moves, boardPosition);
	moveLoop(whiteTurn, position, 1, 1, moves, boardPosition);
	
	return moves;
}

vector<string> knightMoves(const bool whiteTurn, string position, const map<string, string>& boardPosition)
{
	vector<string> moves = {};
	string move = "";
	vector<int> knightDirections = { -1, 1, -2, 2 };

	for (int i : knightDirections) {
		for (int j : knightDirections) {
			if (abs(i) == abs(j)) {
				continue;
			}
			move = singleMove(whiteTurn, position, i, j, boardPosition);
			if (move != "") {
				moves.push_back(move);
			}
		}
	}
	return moves;
}

bool squreAttacked(const bool& whiteTurn, string square, const map<string, string>& boardPosition)
{
	// char turn = whiteTurn ? 'W' : 'B';
	
	// Create an imaginary Queen in the position to find out which opponent pieces have vision
	// Add knight moves on top
	vector<string> potentialAttackers = lineMoves(whiteTurn, square, boardPosition);
	vector<string> diagMoves = diagonalMoves(whiteTurn, square, boardPosition);
	vector<string> NMoves = knightMoves(whiteTurn, square, boardPosition);

	potentialAttackers.insert(potentialAttackers.end(), diagMoves.begin(), diagMoves.end());

	return true;

}

bool check(map<string, string> boardPosition, const bool whiteTurn)
{
	return false;
}

bool checkmate(map<string, string> boardPosition, const bool whiteTurn)
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

string singleMove(const bool& whiteTurn, string position, const int& x, const int& y
				, const map<string, string>& boardPosition)
{
	char new_x = position[0] + x;
	char new_y = position[1] + y;

	if ((new_x - 'A' | 'H' - new_x | new_y - '1' | '8' - new_y) >= 0) {
		return checkCollision(whiteTurn, string{ new_x , new_y }, boardPosition);
	}
	return "";
}

vector<string> moveWhitePawn(string position, map<string, string> boardPosition)
{
	vector<string> moves = {};
	char file = position[0];
	char rank = position[1];

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
	const size_t sizeOfMoves = moves.size();	// We will be appending "moves" and don't
	for (int i = 0; i < sizeOfMoves; ++i) { // want the original size condition to change
		if (moves[i][1] == '8') {
			pawnPromotion(moves, i);
		}
	}
	// TODO: Promotion. If rank == 7, give promotion options
	// TODO: En passant. If rank == 6, check previous move

	return moves;

}

vector<string> moveBlackPawn(string position, map<string, string> boardPosition)
{

	vector<string> moves = {};
	char file = position[0];
	char rank = position[1];

	string nextMove = checkCollision(false, string{ file, char(rank - 1) }, boardPosition);

	// if rank == 2 : check promotion
	if (nextMove != "" && nextMove.size() < 3) { // nextMove would be e.g. A2x if there's something
												 // to capture but pawns cannot capture forward
		moves.push_back(nextMove);

		// If a collision happened 1 square ahead, no need to check 2 squares, hence nested if clauses
		if (rank == '7') {
			nextMove = checkCollision(false, string{ file, char(rank - 2) }, boardPosition);

			if (nextMove != "" && nextMove.size() < 3) {
				moves.push_back(nextMove);
			}
		}
	}
	if (file > 'A') {
		nextMove = checkCollision(false, string{ char(file - 1), char(rank - 1) }, boardPosition);

		if (nextMove != "" && nextMove.size() == 3) { // Pawns can only move diagonally if there's a capture
			moves.push_back(nextMove);
		}
	}
	if (file < 'H') {
		nextMove = checkCollision(false, string{ char(file + 1), char(rank -1) }, boardPosition);

		if (nextMove != "" && nextMove.size() == 3) {
			moves.push_back(nextMove);
		}
	}
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
string checkCollision(const bool &whiteTurn, const string &position, const map<string, string> &boardPosition){

	char turn = whiteTurn ? 'W' : 'B';
	if (boardPosition.at(position) == ".") {
		return position;
	}
	else if (boardPosition.at(position)[0] == turn) {
		return "";
	}
	else {
		return position + 'x';
	}
	

}

void moveLoop(const bool& whiteTurn, const string& position, const int& fileOffset, const int& rankOffset,
				  vector<string> &moves, const map<string,string> &boardPosition)
{
	string nextMove = "";

	char file = position[0];
	char rank = position[1];

	char fileBound = 'H' + 1; // I 9 boundaries used for positive incrementation, adjust
	char rankBound = '8' + 1; // according to Offset parameter. If offset parameter is 0, 
							  // boundaries in that direction don't matter
	if (fileOffset == -1) {
		fileBound = 'A' - 1;
	} 
	if (rankOffset == -1) {
		rankBound = '1' - 1;
	}

	// Pre-increment values and check if destination square is outside of the board. This ensures that
	// vertical moves along the H file, for example, are allowed but not diagonal moves to the right
	file += fileOffset;
	rank += rankOffset;
	while (file != fileBound && rank != rankBound) {

		nextMove = checkCollision(whiteTurn, string{ file, rank}, boardPosition);
		if (nextMove == "") { // Friendly piece, no need to check further
			return;
		}
		else if (nextMove.size() > 2) { // Capture available, no need to check further
			moves.push_back(nextMove);
			return;
		}
		moves.push_back(nextMove);
		file += fileOffset;
		rank += rankOffset;
	}

}

// Indexing vector with const int and only using push_back should never invalidate the order
void pawnPromotion(vector<string>& moves, const int& i)
{
	const char pieces[5] = "QRNB"; // legal promotions
	stringstream ss;

	for (int piece = 0; piece < strlen(pieces); ++piece) {
		ss << moves.at(i) << '=' << pieces[piece];
		moves.push_back(ss.str());
		cout << ss.str() << endl;
		stringstream().swap(ss);
	}
	return;
}
