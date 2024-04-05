#include <iostream>
#include "random.h"
#include "gwindow.h"
#include "gtypes.h"
using namespace std;

void drawTree(GWindow& window, double x, double y, double length, double theta, int order);
string randomColor();

int main() {
	GWindow window(800,400);
	drawTree(window, window.getWidth() / 2.0, window.getHeight(),window.getHeight()/2, 90, 6);
	return 0;
}

void drawTree(GWindow& window, double x, double y, double length, double theta, int count) {
	if (count != 0){
		window.setColor(randomColor());
		GPoint last = window.drawPolarLine(x, y, length, theta);

		int branches = randomInteger(4,7); 

		for (int i = 0; i < branches; i++) {
			pause(2);
			drawTree(window, last.getX(), last.getY(), length / 2, theta + randomReal(-50,50), count-1);
		}
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
