#include <iostream>
#include <cmath>
#include "console.h"
#include "grid.h"
using namespace std;

const int size=3;

enum position{nought=-1, neither, cross};

struct boardT{
	Grid<position> grid;
	position player;
};

bool gameEnded(boardT& board, position& result);
bool playerWin(boardT& board, position player);
bool isDraw(boardT& board);

int main9()
{
	cout<<"done..."<<endl;
	return 0;
}

// problem 1
bool gameEnded(boardT& board, position& result){
	if(playerWin(board, cross)){
		result=cross;
		return true;
	} else if(playerWin(board, nought)){
		result=nought;
		return true;
	} else if(isDraw(board)){
		result=neither;
		return true;
	}
	return false;
}

bool playerWin(boardT& board, position player){
	int diagLeft=0, diagRight=0;
	for(int row=0; row<size; row++){
		int rows=0, cols=0;
		for(int col=0; col<size; col++){
			if(row == col){
				diagLeft+= board.grid[row][col]==player;
				diagRight+= board.grid[row][size-1-col]==player;
			}
			rows+= board.grid[row][col]==player;
			cols+= board.grid[col][row]==player;
		}
		if(rows == size || cols == size){
			return true;
		}
	}

	if(diagLeft == size || diagRight == size){
		return true;
	}

	return false;
}

bool isDraw(boardT& board){
	for(int row=0; row<size; row++){
		for(int col=0; col<size; col++){
			if(board.grid[row][col]==neither){
				return false;
			}
		}
	}
	return true;
}
// problem 2
position getFinalResult(boardT& board){
	position final = board.player==cross? nought:cross;
	if(gameEnded(board, final)){
		return final;
	}

	for(int row=0; row<size; row++){
		for(int col=0; col<size; col++){
			if(board.grid[row][col]==neither){
				boardT copy = board;
				copy.grid[row][col] = copy.player;
				copy.player= copy.player==cross? nought:cross;
				position currentPos=getFinalResult(copy);
				if(board.player == cross){
					final = max(currentPos, board.player);
				} else if(board.player == nought){
					final = min(currentPos, board.player);
				}
			}
		}
	}
	return final;
}