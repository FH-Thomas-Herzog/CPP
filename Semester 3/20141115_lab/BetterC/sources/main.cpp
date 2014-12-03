//============================================================================
// Name        : 20141115_lab.cpp
// Author      : Thomas Herzog
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
/**
 * They are the same.
 * C standard lib inclusion
 #include <cstdlib>
 #include <stdlib.h>
 */

/* Same as packages in java. For design means
 * If not defined 'std::out' must be used. (:: = scope operator)
 * */
using namespace std;

struct Person {
	char* name;
};

/* Prints person values of referenced person */
void print(Person& p) {
	cout << p.name;
}

/* C like call by references */
void increase(int* i) {
	(*i)++;
}

/* C++ like call by reference */
void increase(int& i) {
	i++;
}

int main() {
	int i = 0;            // This is a single line comment, finally
	char s[10];

	cout << "Enter a number!\n";
	cin >> i;
	cout << "Your entered number was " << i << "\n" << endl;

	cerr << "A error occurred\n";

	increase(i);
	increase(&i);
	cout << "Increased value of i=" << i << endl;

	// Deactivate some warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

	// Own context for these tests
	{
		int const iVal = 0;
		for (int j = 0; j < 10; ++j) {
			cout << "j=" << j << endl;
		}

		char* const c1 = ""; // Only character array is not allowed to be changed

		char const *c2 = ""; // Only pointer is not allowed to be changed

		char const * const c3 = "";   // pointer and character cannot be altered
	}

#pragma GCC diagnostic pop

	string s1 = "Franz"; // Compiler generates s1("Franz") = copy constructor
	string s2 = "Gruber"; // Compiler generates s1("Gruber") = copy constructor

	s1 = "Gruber-Leitner"; // assign operator

	cout << s1 << " " << s2 << endl;

	s1.clear();

	s1.push_back('C');
	s1.push_back('+');
	s1.push_back('+');

	cout << s1 << endl;

	s1.insert(s1.end(), 'X');

	cout << s1 << endl;

	return 0;
}
