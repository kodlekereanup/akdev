#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <fstream>
#include "NQueen.h"

int inline RANDOM_VAL(int n) { return rand() % n; }

class HillClimbingRandomRestart {
	int N;
	int steps;
	int restarts;
	int heuristic;
public:

	HillClimbingRandomRestart(int n)  : N(n) { }

	int getSteps();
	int getRestarts();
	int getHeuristic();

	std::vector<NQueen> generateBoard();
	void printState(std::vector<NQueen>);
	
	int findHeuristic(std::vector<NQueen>);
	std::vector<NQueen> nextBoard(std::vector<NQueen>);

};

int HillClimbingRandomRestart :: getSteps()    { return steps;     }

int HillClimbingRandomRestart :: getRestarts() { return restarts;  }

int HillClimbingRandomRestart :: getHeuristic() { return heuristic; }

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

	std::cout << "\n\n";
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(temp[i][j]) std::cout << "Q ";
			else std::cout << ". ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";

	/*
	for(int i = 0; i < N; i++) {
		std::cout << board.at(i).getRow() << " " <<  board.at(i).getCol() << "\n";
	}
	*/
} 

int HillClimbingRandomRestart :: findHeuristic(std::vector<NQueen> board) {
	int heuristics = 0;
	for (int i = 0; i < board.size(); i++) 
        for (int j = i + 1; j < board.size(); j++ ) 
            if (board.at(i).ifConflict(board.at(j))) heuristics++;
            
    return heuristics;
}

void outputToFile(std::ofstream& fout, std::vector<NQueen> board) {

	int N = board.size();
	bool temp[N][N];

	memset(temp, false, sizeof(temp));
	
	for(int i = 0; i < N; i++) 
		temp[board[i].getRow()][board[i].getCol()] = true;

	fout << "\n\n";
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(temp[i][j]) fout << "Q ";
			else fout << ". ";
		}
		fout << "\n";
	}
	fout << "\n\n";

}

std::vector<NQueen> HillClimbingRandomRestart :: nextBoard(std::vector<NQueen> currentBoard) {

	std::vector<NQueen> bestBoard(N), temp(N);
	int currentHeuristic = findHeuristic(currentBoard);
	int bestHeuristic = currentHeuristic;

	bestBoard = currentBoard;
	temp = bestBoard;

	std::ofstream fout;
	fout.open("output.txt", std::ios::app);

    for (int i = 0; i < N; i++) {
        if (i > 0) {
        	NQueen q(currentBoard.at(i - 1).getRow(), currentBoard.at(i - 1).getCol());
        	temp.at(i - 1) = q; 
        }
        NQueen q(0, temp.at(i).getCol());
        temp.at(i) = q;
        
        //outputToFile(fout, temp);

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
    
    fout.close();
    return bestBoard;
    
}

int main() {

	int size;
	std::cout << "\n Enter the size of the board: ";
	std::cin >> size;
	
	if(size <= 3) {
		std::cout <<"\n No Solution \n";
		exit(0);
	}

	HillClimbingRandomRestart algo(size);

	std::vector<NQueen> board = algo.generateBoard();
	
	std::cout << "Initial Configuration: \n";
	algo.printState(board);

	int presentHeuristic = algo.findHeuristic(board);

    while (presentHeuristic != 0) {
        board = algo.nextBoard(board);
        presentHeuristic  = algo.getHeuristic();
    }

    std::cout << "Solution: \n";
    algo.printState(board);
    
    std::cout << "Steps: " << algo.getSteps() << "\n"; 
    std::cout << "Restarts: " << algo.getRestarts() << "\n";

	return 0;
}