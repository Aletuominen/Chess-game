#include "playgame.h"
#include "functions.h"

void movePiece(bool whiteTurn, map<string, string> boardPosition) {

	bool validPiece = false;

	while (true) {

		if (validPiece) {
			// Show legal moves, ask to confirm move
			break;
		}
		string input = "";
		cout << "Please select a piece to move: ";
		cin >> input;

		//Move to more reasonable function (parseInput):
		if (size(input) < 2) {
			cout << "Invalid piece, input too short" << endl;
		}
		else if (whiteTurn && (input[0] == 'B')) {
			cout << "You cannot move black's pieces!" << endl;
		}
		else if (!whiteTurn && (input[0] == 'W')) {
			cout << "You cannot move white's pieces!" << endl;
		}

		else {
			for (auto it = boardPosition.begin(); it != boardPosition.end(); it++) {

				if (input == it->second) {
					cout << "Moving piece " << it->second << " on square " << it->first << endl;
					validPiece = true;
				}

			}
			if (!validPiece) {
				cout << "Invalid piece" << endl;
			}
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
		movePiece(whiteTurn, boardPosition);

		whiteTurn = !whiteTurn;

		printBoard(boardPosition, boardOrder);

	}
}
