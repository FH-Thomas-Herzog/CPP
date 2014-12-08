/*
 * Data.h
 *
 *  Created on: Nov 29, 2014
 *      Author: cchet
 */

#ifndef DATA_H_
#define DATA_H_

#include <string>
#include <iostream>

class Data {

	/* Private members*/
protected:
	std::string value;

	/* Public members */
public:
	/* Constructor shall never be virtual because meant for this class and not derived classes */
	Data(std::string val);
	virtual ~Data();

	operator std::string() const;
	bool operator==(const Data& d) const;
	inline bool operator!=(const Data& d) const {
		return !operator==(d);
	}
	/* this method can be bind dynamically and is used to be able to overwrite operator function */
	virtual void print(std::ostream& os) const;

	/* This a global function marked as a friend. this function can not be bind dynamically */
	friend std::ostream& operator<<(std::ostream& stream, Data& data);
};

#endif /* DATA_H_ */
