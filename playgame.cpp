#include "playgame.h"
#include "functions.h"

void movePiece(bool whiteTurn, map<string, string> boardPosition, vector<string> boardOrder) {


	// Add friendly / opponent pieces on third row to test collision detection
	boardPosition["B3"] = "BP9";
	boardPosition["E3"] = "WP9";

	while (true) {

		string input = "";
		cout << "Please select a piece to move: ";
		cin >> input;

		if (!parseInput(whiteTurn, input, boardPosition, boardOrder)) {
			continue;
		}

		string piecePosition = findPiecePosition(input, boardPosition);
		if (piecePosition == "") {
			cout << "Invalid piece" << endl;
			continue;
		}
		else {
			cout << "Moving piece " << boardPosition[piecePosition] << " on square " << piecePosition << endl;
			vector<string> legalMoves = findLegalMoves(true, input, boardPosition);
			cout << "Legal moves are: ";
			for (string nextMove : legalMoves) {
				 cout << nextMove << ", ";
			}
			cout << endl;

				

			}
		


	}

}
void playGame(map<string, string> boardPosition, vector<string> boardOrder){

	string gameResult = "";

	bool whiteTurn = true; // false for black's turn

	while (true){

		if (checkmate(boardPosition, whiteTurn)){
			gameResult = "Checkmate for x";
			break;
		}
		movePiece(whiteTurn, boardPosition, boardOrder);

		whiteTurn = !whiteTurn;

		printBoard(boardPosition, boardOrder);

	}
}

int parseInput(bool whiteTurn, string input, 
			   const map<string, string>& boardPosition , const vector<string>& boardOrder){

	if (input == "print") {
		printBoard(boardPosition, boardOrder);
		return 0;
	}
	if (size(input) < 2) {
		cout << "Invalid piece, input too short" << endl;
		return 0;
	}
	else if (whiteTurn && (input[0] != 'W')) {
		cout << "Please select a white piece, starting with W" << endl;
		return 0;
	}
	else if (!whiteTurn && (input[0] != 'B')) {
		cout << "Please select a black piece, starting with B" << endl;
		return 0;
	}
	return 1;
}
