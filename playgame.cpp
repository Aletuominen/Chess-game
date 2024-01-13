#include "playgame.h"
#include "functions.h"

void movePiece(const bool whiteTurn, vector<string> &scoreSheet, 
	map<string, string> &boardPosition, vector<string> boardOrder) {

		string input = parseInput(whiteTurn, scoreSheet, boardPosition, boardOrder);

		vector<string> legalMoves = findLegalMoves(whiteTurn, input, boardPosition);

		while (size(legalMoves) == 0) {
			cout << "Piece has no legal moves. Please select another piece." << endl;
			input = parseInput(whiteTurn, scoreSheet, boardPosition, boardOrder);
			legalMoves = findLegalMoves(whiteTurn, input, boardPosition);
		}

		string piecePosition = findPiecePosition(input, boardPosition);
		cout << "Moving piece " << boardPosition[piecePosition] << " on square " << piecePosition << endl;
		cout << "Legal moves are: ";
		for (string nextMove : legalMoves) {
				cout << nextMove << ", ";
		}
		cout << endl;

		// A3x notation will have to do for now, implement proper algebraic notation later
		cout << "Please select one of the moves: ";
		string selectedMove = {};
		cin >> selectedMove;
		if (find(legalMoves.begin(), legalMoves.end(), selectedMove) != legalMoves.end()) {
			// updateBoard()
			boardPosition[piecePosition] = ".";
			boardPosition[selectedMove.substr(0, 2)] = input;
			cout << endl <<  " Move successful " << endl;
			scoreSheet.push_back(input.append(selectedMove));
			return;
				
		}
		else {
			cout << "Invalid move. Returning to input." << endl;
			parseInput(whiteTurn, scoreSheet, boardPosition, boardOrder);
		}

}
void playGame(map<string, string> boardPosition, vector<string> boardOrder){

	string gameResult = "";
	vector<string> scoreSheet = {};

	/*Add friendly / opponent pieces on third row to test collision detection
	boardPosition["B3"] = "BP9";
	boardPosition["E3"] = "WP9";
	*/

	bool whiteTurn = false; // will flip to white before moving first piece

	while (true){

		printBoard(boardPosition, boardOrder);

		if (checkmate(boardPosition, whiteTurn)){
			gameResult = "Checkmate for x";
			break;
		}

		whiteTurn = !whiteTurn;
		movePiece(whiteTurn, scoreSheet, boardPosition, boardOrder);

		// whiteTurn = !whiteTurn;


	}
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
