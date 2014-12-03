/*
 * person.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>

namespace swo3 {

class Person {

public:
	Person(); // Default constructor with no arguments

	Person(const char* name); // Second constructor with name as argument

	~Person(); // Destructor responsible for destroying the object and all used members

	Person(const Person& p); // Copy constructor

	void setName(const char* name); // Setter for name

	const char* getName();	// Getter for name

	void print() const; // const functions are not allowed to change object attribute values

private:
	char* name;
};

}
#endif /* PERSON_H_ */
