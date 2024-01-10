#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


void printBoard (map < string, string> boardPosition, vector<string> boardOrder);

vector<string> legalMoves (bool whiteTurn, string piece, map < string, string> boardPosition);
vector<string> checkDiagonals (string piecePos, map < string, string> boardPosition);
vector<string> checkLines (string piecePos, map < string, string> boardPosition);
bool absolutePin(string piece, map < string, string> boardPosition);
//Potentially only need 2 --> check legal moves, if none, check if check and return either stalemate or checkmate
bool check(map < string, string> boardPosition, bool whiteTurn);
bool checkmate(map < string, string> boardPosition, bool whiteTurn);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);
string findPiecePosition(string piece, map<string, string> boardPosition);
string checkCollision(bool whiteTurn, string position, map<string, string> boardPosition);