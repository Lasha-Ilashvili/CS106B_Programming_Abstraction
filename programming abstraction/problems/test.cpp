#include <iostream>
#include "console.h"
#include <string>
using namespace std;

void testMethod(string **s1, string **s2) { *s2 = *s1; } // different from **s2 = **s1;

int main()
{
	string *s1 = new string("AF");
	string *s2 = new string("");

	cout<<s2<<endl;

	cout<<*s2<<endl;

	testMethod(&s1, &s2);

	cout<<s2<<endl;

	cout<<*s2<<endl;

	return 0;
}