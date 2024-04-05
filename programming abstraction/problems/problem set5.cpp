#include <iostream>
#include "console.h"
#include "grid.h"
#include "random.h"
using namespace std;

void fieldProbability(Grid<bool>& result, double probability);
void fieldCount(Grid<bool>& result, int numMines);
void mineSweeperGrid(Grid<bool>& result);
int checkBombs(Grid<bool>& result, int x, int y);
void leftRect(Grid<bool>& result);
void rectBombs(Grid<bool>& result, int x1, int y1, int x2, int y2);

int main5()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
void fieldProbability(Grid<bool>& result, double probability){
	for(int row=0; row<result.numRows(); row++){
		for(int col=0; col<result.numCols(); col++){
			result[row][col]=randomChance(probability);
		}
	}
}

void fieldCount(Grid<bool>& result, int numMines) {
	while(numMines>0){
		int x=randomInteger(0,result.numCols()-1);
		int y=randomInteger(0,result.numRows()-1);
		if(!result[x][y]){
			result[x][y]=true;
			numMines--;
		}	
	}
}
// problem 2
void mineSweeperGrid(Grid<bool>& result){
	Grid<int> mine(result.numRows(),result.numCols());
	for(int row=0; row<mine.numRows(); row++){
		for(int col=0; col<mine.numCols(); col++){
			mine[row][col]=checkBombs(result, row, col);
		}
	} 
}

int checkBombs(Grid<bool>& result, int x, int y){
	if(result[x][y]) return -1;
	int bombs=0;
	for(int row=-1; row<=1; row++){
		for(int col=-1; col<=1; col++){
			if(result.inBounds(x+row,y+col))
				bombs+=result[x+row][y+col];
		}
	}
	return bombs;
}

// problem 3
void leftRect(Grid<bool>& result){
	Grid<int> rects(result.numRows(),result.numCols());
	for(int i=0; i<result.numRows(); i++){
		for(int j=0; j<result.numCols(); j++){
			if(i==0 && j==0) rects[i][j]= result[i][j];
			else if(i==0)	 rects[i][j]= rects[i][j-1]+result[i][j];
			else if(j==0)	 rects[i][j]= rects[i-1][j]+result[i][j];
			else			 rects[i][j]= rects[i-1][j]+rects[i][j-1]+result[i][j]-rects[i-1][j-1];
		}
	}
}

void rectBombs(Grid<bool>& result, int x1, int y1, int x2, int y2){
    int sum=0;
	for(int i=y1; i<=y2; i++){
		for(int j=x1; j<=x2; j++){
			sum+=result[i][j];		
		}
	}
	cout<<sum<<endl;
}