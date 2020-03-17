#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include "NQueen.h"

int inline RANDOM_VAL(int n) { return rand() % n; }

class HillClimbingRandomRestart {

public:
	int N = 8;
	int steps;
	int restarts;
	int heuristic;

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
        for (int j = i + 1; j < board.size(); j++ ) 
            if (board.at(i).ifConflict(board.at(j))) heuristics++;
            
    return heuristics;
}

std::vector<NQueen> HillClimbingRandomRestart :: nextBoard(std::vector<NQueen> currentBoard) {

	std::vector<NQueen> bestBoard(N), temp(N);
	int currentHeuristic = findHeuristic(currentBoard);
	int bestHeuristic = currentHeuristic;

	bestBoard = currentBoard;
	temp = bestBoard;


    for (int i = 0; i < N; i++) {
        if (i > 0) {
        	NQueen q(currentBoard.at(i - 1).getRow(), currentBoard.at(i - 1).getCol());
        	temp.at(i - 1) = q; 
        }
        NQueen q(0, temp.at(i).getCol());
        temp[i] = q;
        
        for (int j = 0; j < N; j++) {
            
            int tempH = findHeuristic(temp);
            
            if (tempH < bestHeuristic) {
                bestHeuristic = tempH;
                bestBoard = temp;
            }
            
            if (temp.at(i).getRow() != N-1) temp.at(i).move();
        }
    }
    
    if (bestHeuristic == currentHeuristic) {
        restarts++;
        bestBoard = generateBoard();
        heuristic = findHeuristic(bestBoard);
    } else  heuristic = bestHeuristic;

    steps++;
    
    return bestBoard;
    
}

int main() {

	const int n = 8;
	
	HillClimbingRandomRestart algo;

	std::vector<NQueen> board = algo.generateBoard();
	algo.printState(board);

	int presentHeuristic = algo.findHeuristic(board);

    while (presentHeuristic != 0) {
        board = algo.nextBoard(board);
        presentHeuristic  = algo.heuristic;
    }

    algo.printState(board);
    
    std::cout << "Steps: " << algo.steps << "\n"; 
    std::cout << "Restarts: " << algo.restarts << "\n";

	return 0;
}