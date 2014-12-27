/*
 * rational.c
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include "rational.h"

using namespace std;

namespace swo3 {

	Rational::Rational(int numerator, int denominator) :
			numerator(numerator), denominator(denominator) {
		cout << "Konstructor with 2 inst called " << endl;
	}

	Rational::Rational(int numerator) :
			numerator(numerator), denominator(1) {
	}

	Rational::Rational(const Rational& r) :
			numerator(r.numerator), denominator(r.denominator) {
		cout << "copy Konstructor with 2 inst called " << endl;
	}

	Rational::~Rational() {
		cout << "Destructer called" << endl;
	}

	double Rational::asDouble() const {
		return (double) numerator / denominator;
	}

	int Rational::getNumerator() const {
		return numerator;
	}

	int Rational::getDenominator() const {
		return numerator;
	}

	void Rational::setNumerator(int newNum) {
		numerator = newNum;
	}
	void Rational::setDenominator(int newDenom) {
		denominator = newDenom;
	}

	void Rational::print() const {
		cout << numerator << "/" << denominator << endl;
	}

	int gcd(int a, int b) {
		while (b > 0) {
			int h = a % b;
			a = b;
			b = h;
		}

		return a;
	}

	void Rational::simplify() {
		int g = gcd(numerator, denominator);
		numerator /= g;
		denominator /= g;
	}

	void Rational::add(const Rational &r) {
		int g = gcd(numerator, denominator);
		numerator = numerator * r.denominator / g
				+ r.numerator * denominator / g;
		denominator = denominator * r.denominator / g;
	}

	void Rational::sub(const Rational &r) {
		int g = gcd(numerator, denominator);
		numerator = numerator * r.denominator / g
				- r.numerator * denominator / g;
		denominator = denominator * r.denominator / g;
	}

	void Rational::mult(const Rational &r) {

		numerator = numerator * r.denominator;
		denominator = denominator * r.denominator;
		simplify();
	}

	void Rational::div(const Rational &r) {
		numerator = numerator * r.denominator;
		denominator = denominator * r.numerator;
		simplify();
	}

	Rational& Rational::operator+(const Rational & r) {
		Rational result = Rational(*this);
		result.add(r);
		return result;
	}
	Rational& Rational::operator-(const Rational & r) {
		Rational result = Rational(*this);
		result.sub(r);
		return result;

	}
	Rational& Rational::operator*(const Rational & r) {
		Rational result = Rational(*this);
		result.mult(r);
		return result;
	}
	Rational& Rational::operator/(const Rational & r) {
		Rational result = Rational(*this);
		result.div(r);
		return result;
	}
	ostream& operator<<(ostream & os, const Rational & r) {
		// Should not be done like this, because if the output stream differs then
		// this won't work anymore.
		// Therefore don't do it like this.
//	r.print();

		// this is the better solution
		os << r.getNumerator() << "/" << r.getDenominator() << endl;

		return os;
	}

}
