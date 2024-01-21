#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


void printBoard (const map < string, string> &boardPosition, const vector<string> &boardOrder);

vector<string> findLegalMoves(const bool whiteTurn, string piece, map < string, string> boardPosition);
vector<string> lineMoves (const bool whiteTurn, string position, const map < string, string> &boardPosition);
vector<string> diagonalMoves (const bool whiteTurn, string position, const map < string, string>& boardPosition);
vector<string> knightMoves (const bool whiteTurn, string position, const map < string, string>& boardPosition);


// Implement a function to see if a square is attacked by an enemy piece i.e. have an imaginary queen move from the
// square and go through all the capture options of the queen to see which enemy pieces have vision
// This can be used for checks, absolute pins and castles
bool squreAttacked(const bool& whiteTurn, string square, const map<string, string>& boardPosition);
bool absolutePin(string piece, map < string, string> boardPosition);
// Potentially only need 2 --> check legal moves, if none, check if check and return either stalemate or checkmate

bool check(map < string, string> boardPosition,const bool whiteTurn);
bool checkmate(map < string, string> boardPosition,const bool whiteTurn);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);

// Returns a move based on a square and horizontal/vertical offset (x, y). Checks for out of bounds
string singleMove(const bool& whiteTurn, string position, const int& x, const int& y, const map<string, string>& boardPosition);
vector<string> moveWhitePawn(string position, map<string, string> boardPosition);
vector<string> moveBlackPawn(string position, map<string, string> boardPosition);
string findPiecePosition(string piece, map<string, string> boardPosition);
string checkCollision(const bool &whiteTurn, const string &position, const map<string, string> &boardPosition);
void moveLoop(const bool& whiteTurn, const string& position, const int& fileOffset, const int& rankOffset,
	vector<string>& moves, const map<string, string>& boardPosition);
void pawnPromotion(vector<string>& moves, const int &i);