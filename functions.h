#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


void printBoard (const map < string, string> &boardPosition, const vector<string> &boardOrder);

vector<string> findLegalMoves(bool whiteTurn, string piece, map < string, string> boardPosition);
vector<string> checkDiagonals (bool whiteTurn, string piecePos, map < string, string> boardPosition);
vector<string> checkLines (string piecePos, map < string, string> boardPosition);
bool absolutePin(string piece, map < string, string> boardPosition);
//Potentially only need 2 --> check legal moves, if none, check if check and return either stalemate or checkmate
bool check(map < string, string> boardPosition, bool whiteTurn);
bool checkmate(map < string, string> boardPosition, bool whiteTurn);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);
vector<string> moveWhitePawn(string piecePos, map<string, string> boardPosition);
vector<string> moveBlackPawn(bool whiteTurn, string piecePos, map<string, string> boardPosition);
string findPiecePosition(string piece, map<string, string> boardPosition);
string checkCollision(bool whiteTurn, string position, map<string, string> boardPosition);