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
private:
	std::string value;

	/* Public members */
public:
	Data(std::string val);
	~Data();
	operator std::string();

	bool operator==(const Data& d) const;

	inline bool operator!=(const Data& d) const {
		return !operator==(d);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Data& data);
};

#endif /* DATA_H_ */
