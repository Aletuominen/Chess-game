#include "playgame.h"
#include "functions.h"

void movePiece(bool whiteTurn, map<string, string> boardPosition) {

	while (true) {

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
			string piecePosition = findPiecePosition(input, boardPosition);
			if (piecePosition == ""){
				cout << "Invalid piece" << endl;
				continue;
			}
			else{
				cout << "Moving piece " << boardPosition[piecePosition] << " on square " << piecePosition << endl;
				cout << "Legal moves are: " << legalMoves(true, input, boardPosition)[0]
					 << ", " << legalMoves(true, input, boardPosition)[1] << endl
					 ;
						
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
