#include <iostream>
#include <string>
#include "console.h"
#include "gwindow.h"
#include "random.h"
using namespace std;

void drawCubes(GWindow& window, double x, double y, double size, int count);
string randomColor();

int main()
{
	GWindow window(600,500);
	double size= 150.0;
	drawCubes(window, (window.getWidth()-size)/2, (window.getHeight()-size)/2, size, 8);
	return 0;
}

void drawCubes(GWindow& window, double x, double y, double size, int count){
	if(count!=0){
		window.setColor("orange");
		window.fillRect(x,y,size,size);
		drawCubes(window, x-size/2, y-size/2, size/2, count-1);
		drawCubes(window, x+size, y-size/2, size/2, count-1);
		drawCubes(window, x-size/2, y+size, size/2, count-1);
		drawCubes(window, x+size, y+size, size/2, count-1);
	}
}

string randomColor(){
	int rand=randomInteger(1,10);
	switch(rand){
		case 1: return "blue";
		case 2: return "cyan";		
		case 3: return "gray";		
		case 4: return "green";		
		case 5: return "magenta";		
		case 6: return "orange";		
		case 7: return "pink";		
		case 8: return "red";		
		case 9: return "yellow";		
	}
	return "black";
}
