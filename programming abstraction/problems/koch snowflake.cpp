#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "gtypes.h"
#include "simpio.h"
#include "random.h"
using namespace std;

void drawSnowflake(GWindow& window, GPoint& pt, double length, int order);
void addLines(GWindow& window, GPoint& pt, double length, int theta, int order);

int main()
{
	double length = getReal("Enter length of triangle: ");

	int order = getInteger("Enter a fractal order: ");

	GWindow window(length*1.5, length*1.5);
	window.setColor("blue");
	GPoint pt((window.getWidth()-length)/2, (window.getHeight()+length)/2.5);
	drawSnowflake(window, pt, length, order);
	return 0;
}

void drawSnowflake(GWindow& window, GPoint& pt, double length, int order){
	int theta=0;
	for(int i=0; i<3; i++){
		addLines(window, pt, length, theta,7); 
		theta+=120;
	}
}

void addLines(GWindow& window, GPoint& pt, double length, int theta, int order){
	if(order==0){
		pt = window.drawPolarLine(pt.getX(), pt.getY(), length, theta);
	} else {
		addLines(window, pt, length/3, theta, order-1); 
		addLines(window, pt, length/3, theta+60, order-1); 
		addLines(window, pt, length/3, theta-60, order-1); 
		addLines(window, pt, length/3, theta, order-1);
	}
}