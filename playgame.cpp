#include "playgame.h"
#include "functions.h"

void playGame(map<string, string> boardPosition, const vector<string> &boardOrder) {

	string gameResult = "";
	vector<string> scoreSheet = {};

	/* Add friendly / opponent pieces on third row to test collision detection
	boardPosition["B3"] = "BP9";
	boardPosition["E3"] = "WP9";
	*/

	// boardPosition["B7"] = "WP9"; // Promotion check

	bool whiteTurn = true;
	printBoard(boardPosition, boardOrder);

	while (true) {

		if (checkmate(boardPosition, whiteTurn)) {
			gameResult = "Checkmate for x";
			break;
		}
		if (movePiece(whiteTurn, scoreSheet, boardPosition, boardOrder) == 1) { // 1 if move completed successfully, otherwise
			//whiteTurn = !whiteTurn;											   // call function again without switching turn
			printBoard(boardPosition, boardOrder);
		}
	}
}

int movePiece(const bool whiteTurn, vector<string> &scoreSheet, 
	map<string, string> &boardPosition, const vector<string> &boardOrder) {

		string input = parseInput(whiteTurn, scoreSheet, boardPosition, boardOrder);
		vector<string> legalMoves = findLegalMoves(whiteTurn, input, boardPosition);

		while (size(legalMoves) == 0) {
			cout << "Piece has no legal moves. Please select another piece." << endl;
			input = parseInput(whiteTurn, scoreSheet, boardPosition, boardOrder);
			legalMoves = findLegalMoves(whiteTurn, input, boardPosition);
		}

		string piecePosition = findPiecePosition(input, boardPosition);
		string selectedMove = selectMove(boardPosition, legalMoves, piecePosition);

		if (selectedMove == "") { // Player did not select a move
			return 0;
		}
		updateBoard(boardPosition, piecePosition, input, selectedMove, scoreSheet);
		return 1;
}


string parseInput(const bool whiteTurn, const vector<string> &scoreSheet,
			   const map<string, string>& boardPosition , const vector<string>& boardOrder){

	// Add more options for starting game, selecting side etc. Separate function for other options

	string input = "";

	while (true) {

		if (whiteTurn) {
			cout << "White to move. ";
		}
		else {
			cout << "Black to move. ";
		}
		cout << "Please select a piece: ";
		cin >> input;

		if (input == "showmoves") {
			for (auto move : scoreSheet) {
				cout << move << endl;
			}
		}
		else if (input.find("attacked") == !string::npos) {
			squreAttacked(whiteTurn, string{ input[input.size() - 2], input[input.size() - 1] }, boardPosition);
			continue;
		}

		else if (input == "print") {
			printBoard(boardPosition, boardOrder);
		}

		if (size(input) < 2) {
			cout << "Invalid piece, input too short" << endl;
		}
		else if (whiteTurn && (input[0] != 'W')) {
			cout << "Please select a white piece, starting with W" << endl;
		}
		else if (!whiteTurn && (input[0] != 'B')) {
			cout << "Please select a black piece, starting with B" << endl;
		}
		else {
			for (auto mapIter : boardPosition) {
				if (mapIter.second == input) {
					return input;
				}
			}
		}

	}
}

// selectedMove is guaranteed to be 2-5 characters as per checks by other functions
void updateBoard(map<string, string>& boardPosition, const string& piecePosition, string input,
				 const string& selectedMove, vector<string> &scoreSheet)
{
	boardPosition[piecePosition] = ".";
	if (selectedMove.at(selectedMove.size() - 2) == '=') { // Pawn promotion
		// Add 3 at the end to avoid conflicts. Need to increment in case of multiple promotions of same type.
		boardPosition[selectedMove.substr(0, 2)] = string{ input[0], selectedMove.at(selectedMove.size()-1), '3'};
	}
	else {
		boardPosition[selectedMove.substr(0, 2)] = input;
	}
	scoreSheet.push_back(input.append(selectedMove));
	return;
}

string selectMove(map<string, string> const& boardPosition, const vector<string>& legalMoves, 
				const string& piecePosition)
{
	// A3x notation will have to do for now, implement proper algebraic notation later

	cout << "Moving piece " << boardPosition.at(piecePosition) << " on square " << piecePosition << endl;
	cout << "Legal moves are: ";

	for (string nextMove : legalMoves) {
		cout << nextMove << ", ";
	}
	cout << endl;

	string selectedMove = "";
	cout << "Please select one of the moves or type \"cancel\" to select another piece" << endl;
	
	while (true){

		cin >> selectedMove;
		if (selectedMove == "cancel") {
			return "";
		}
		else if (find(legalMoves.begin(), legalMoves.end(), selectedMove) != legalMoves.end()) {
			cout << "Move successful " << endl;
			return selectedMove;
		}
		else {
			cout << "Invalid move. Please select another move or type \"cancel\" to select another piece" << endl;
		}
	}
}
