/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "gtypes.h" 
#include "simpio.h"
using namespace std;

/* Draws a Sierpinski Triangle recursively */
void sierpinskiTriangle(GWindow& window, GPoint& last, double length, int order);

/* Draws an equilateral triangle given a length and using theta */
void equilateralTriangle(GWindow& window, GPoint& last, double length, int theta);

int main()
{
	//GWindow window(600,400);

   	/* Length of the triangle from the user */
	double length = getReal("Enter length of triangle: ");

	/* Fractal order from the user */
	int order = getInteger("Enter a fractal order: ");

	GWindow window(length*1.5, length*1.5); // Window size is based on user's preference

	/* Starting point for the first triangle */
	GPoint last((window.getWidth()-length) / 2, (window.getHeight()+length) / 2);
	sierpinskiTriangle(window, last, length, order);
	return 0;
}

void sierpinskiTriangle(GWindow& window, GPoint& last, double length, int order){
	/* Draws equilateral triangles given the length */
	equilateralTriangle(window, last, length, 0);
	
	if(order!=0){

		length/=2;

		/* Recursive calls with adjusted starting points and length */
		sierpinskiTriangle(window, last, length, order-1);

	   /* The new starting points are calculated using the drawPolarLine function,
	    * which takes in a last point and returns a new middle point between a start and an end
	    */
		sierpinskiTriangle(window, window.drawPolarLine(last, length,  0), length, order-1);
		sierpinskiTriangle(window, window.drawPolarLine(last, length, 60), length, order-1);
	}
}

void equilateralTriangle(GWindow& window, GPoint& last, double length, int theta){
	last = window.drawPolarLine(last, length, theta);
	last = window.drawPolarLine(last, length, theta + 120);
	last = window.drawPolarLine(last, length, theta - 120);
}
