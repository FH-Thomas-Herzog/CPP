/*
 * PData.h
 *
 *  Created on: Dec 6, 2014
 *      Author: cchet
 */

#ifndef PDATA_H_
#define PDATA_H_

#include "Data.h"

/*
 * public class is allowed to be derived from again
 * private would cause that the class can never be derived from
 * */
class PData: public Data {
private:
	const int priority; // not allowed to be changed

public:
	PData(std::string value, int priority);
	virtual ~PData();

	int getPriority() const;
	virtual void print(std::ostream &os) const;

};

#endif /* PDATA_H_ */
