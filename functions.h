#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


void printBoard (const map < string, string> &boardPosition, const vector<string> &boardOrder);

vector<string> findLegalMoves(const bool whiteTurn, string piece, map < string, string> boardPosition);
vector<string> checkDiagonals (const bool whiteTurn, string piecePos, const map < string, string> &boardPosition);
vector<string> checkLines (string piecePos, map < string, string> boardPosition);
bool absolutePin(string piece, map < string, string> boardPosition);
// Potentially only need 2 --> check legal moves, if none, check if check and return either stalemate or checkmate

bool check(map < string, string> boardPosition,const bool whiteTurn);
bool checkmate(map < string, string> boardPosition,const bool whiteTurn);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);
vector<string> moveWhitePawn(string piecePos, map<string, string> boardPosition);
vector<string> moveBlackPawn(string piecePos, map<string, string> boardPosition);
string findPiecePosition(string piece, map<string, string> boardPosition);
string checkCollision(const bool &whiteTurn, const string &position, const map<string, string> &boardPosition);
void diagonalLoop(const bool& whiteTurn, const string& position, const char& fileBound, const char& rankBound,
	vector<string>& moves, const map<string, string>& boardPosition);
void pawnPromotion(vector<string>& moves, const int &i);