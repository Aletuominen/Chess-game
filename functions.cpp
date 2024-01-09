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