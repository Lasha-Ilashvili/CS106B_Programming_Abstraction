/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities, Vector<Set<string>>& locations,
							   int numHospitals, Vector<Set<string>>& result);

/* Recursive helper function for canOfferUniversalCoverage.
 * If a valid solution is found, it is stored in the result parameter.
 * Returns true; false otherwise.
 */
bool coverCitiesHelper(Set<string>& cities, Vector<Set<string>>& locations, 
					   int numHospitals, Vector<Set<string>> coveredCities, Vector<Set<string>>& result);

/* Main for testing */
int main() {

    // A set with some sample cities.
    Set<string> cities;
	cities += "A", "E", "B";

	// A vector of sets representing the locations that can cover each city
	Vector<Set<string>> locations;
	Set<string> s;
	s += "A", "B", "C";
	locations += s;
	s.clear();
	s += "A", "C", "D"; 
	locations += s;
	s.clear();
	s += "B", "F"; 
	locations += s;
	s.clear();
	s += "C", "E", "F";
	locations += s;
	s.clear();

	// A vector to store the result
	Vector<Set<string>> result;

	// Results
	cout << "Can offer universal coverage: " << canOfferUniversalCoverage(cities, locations, 2, result) << endl;
	cout << "Result: " << result << endl;

    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector<Set<string>>& locations, 
							   int numHospitals, Vector<Set<string>>& result){

	Vector<Set<string>> coveredCities;

	return coverCitiesHelper(cities, locations, numHospitals, coveredCities, result);

}

bool coverCitiesHelper(Set<string>& cities, Vector<Set<string>>& locations, 
					   int numHospitals, Vector<Set<string>> coveredCities, Vector<Set<string>>& result){

	/* If we've used more hospitals than allowed, returns false */
	if(coveredCities.size() > numHospitals){
		return false;
	}

	/* If there are no more cities left to cover, we've found a solution */
	if(cities.isEmpty()){
		result=coveredCities;
		return true;
	} else if(locations.isEmpty()){ // If there are no more hospitals and cities is not empty, returns false.
		return false;
	}

	/* The last hospital location in the vector */
	Set<string> last = locations[locations.size()-1];
	locations.remove(locations.size()-1);

	/* Covers the remaining cities without using the current location */
	bool option1 = coverCitiesHelper(cities-last, locations, numHospitals, coveredCities+=last, result);

	coveredCities.remove(coveredCities.size()-1);

	/* Covers the remaining cities using the current location */
	bool option2 = coverCitiesHelper(cities, locations, numHospitals, coveredCities, result);

	/* Restores the list of hospital locations */
	locations.add(last);

	/* Returns correct path, if there was any */
	return option1 || option2;
}