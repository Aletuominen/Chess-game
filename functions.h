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
bool check(std::map < std::string, std::string> boardPosition);
bool checkmate(std::map < std::string, std::string> boardPosition);
void startingPieces(map<string, string>& boardPosition, vector<string>& boardOrder);