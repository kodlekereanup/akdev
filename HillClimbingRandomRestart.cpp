#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include "NQueen.h"

int inline RANDOM_VAL(int n) { return rand() % n; }

class HillClimbingRandomRestart {

	int N = 8;
	int steps;
	int restarts;
	int heuristic;
public:
	std::vector<NQueen> generateBoard();
	void printState(std::vector<NQueen>);
	int findHeuristic(std::vector<NQueen>);
	std::vector<NQueen> nextBoard(std::vector<NQueen>);

};

std::vector<NQueen> HillClimbingRandomRestart :: generateBoard() {
	std::vector<NQueen> initBoard(N);
	srand(time(0));
	for(int i = 0; i < N; i++) {
		NQueen t(RANDOM_VAL(N), i);
		initBoard.at(i) = t;
	}
	return initBoard;
}

void HillClimbingRandomRestart :: printState(std::vector<NQueen> board) {
	bool temp[N][N];

	memset(temp, false, sizeof(temp));
	
	for(int i = 0; i < N; i++) 
		temp[board[i].getRow()][board[i].getCol()] = true;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(temp[i][j]) std::cout << "Q ";
			else std::cout << ". ";
		}
		std::cout << "\n";
	}

	std::cout << "\n\n";

	for(int i = 0; i < N; i++) {
		std::cout << board.at(i).getRow() << " " <<  board.at(i).getCol() << "\n";
	}

} 

int HillClimbingRandomRestart :: findHeuristic(std::vector<NQueen> board) {
	int heuristics = 0;
	for (int i = 0; i < board.size(); i++) 
        for (int j= i + 1; j < board.size(); j++ ) 
            if (board.at(i).ifConflict(board.at(j))) heuristics++;
            
    return heuristics;
}

int main() {

	const int n = 8;
	
	HillClimbingRandomRestart algo;

	std::vector<NQueen> board = algo.generateBoard();
	algo.printState(board);

	return 0;
}