#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

using namespace std;


void printBoard (std::map < std::string, std::string> boardPosition, std::vector<std::string> boardOrder);

std::vector<std::string> legalMoves (std::string piece, std::map < std::string, std::string> boardPosition);
std::vector<std::string> checkDiagonals (std::string piece, std::map < std::string, std::string> boardPosition);
std::vector<std::string> checkLines (std::string piece, std::map < std::string, std::string> boardPosition);
bool absolutePin(std::string piece, std::map < std::string, std::string> boardPosition);
//Potentially only need 2 --> check legal moves, if none, check if check and return either stalemate or checkmate
bool check(std::map < std::string, std::string> boardPosition, bool whiteTurn);
bool checkmate(std::map < std::string, std::string> boardPosition, bool whiteTurn);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);