/*
 * rational.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */

#ifndef HEADERS_RATIONAL_H_
#define HEADERS_RATIONAL_H_

using namespace std;

namespace swo3 {
class Rational {

	/* A function which is a friend of this class and has access to he class data */
	friend ostream& operator<<(ostream & os, const Rational & s);

public:
	/* Default constructor/destructor are automatically created if not explicitly defined */
	Rational(int numerator, int denominator);

	/* 'explicit' keyword for only int otherwise casting is implicitly casted */
	Rational(int numerator); // Type cast constructor

	Rational(const Rational &r);

	~Rational();

	double asDouble() const;

	int getNumerator() const;
	int getDenominator() const;

	void setNumerator(int newNum);
	void setDenominator(int newDenom);

	void print() const;

	void simplify();

	void add(const Rational &r);
	void mult(const Rational &r);
	void div(const Rational &r);
	void sub(const Rational &r);
	Rational& operator+(const Rational & r);
	Rational& operator-(const Rational & r);
	Rational& operator*(const Rational & r);
	Rational& operator/(const Rational & r);

private:
	int numerator;
	int denominator;
};

}
#endif /* HEADERS_RATIONAL_H_ */
