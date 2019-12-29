//
//  Monomial.cpp
//
//  Created by Tomer Zaidler on 11/12/2019.
//


#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <string>
#include <math.h>
#include "Monomial.h"

using namespace std;


int Monomial::numberOfMonomials = 0;

Monomial::Monomial(double coe, int deg) {//constructor
	c = coe;
	d = deg;
	next = NULL;
	numberOfMonomials++;
}

Monomial::Monomial(string s) {//constructor for string
	bool checkforX = false;
	double finalC;
	string num;
	int i;
	if (s[0] != '-') { // this is a positive number
		for (i = 0; i < (int)(s.length()); i++) {
			if (s[i] == 'x')
				break;
			num += s[i];
		}
		if (s[0] == 'x' || (s[0] == '1' && s[1] == 'x')) {
			this->c = 1;
		}
		else {
			finalC = stod(num);
			this->c = finalC;
		}
		num = "";
		for (int j = 0; j < (int)(s.length()); j++) {
			if (s[j] == 'x')
				checkforX = true;
		}
		if (checkforX == false)
		{
			this->d = 0;
		}
		else if (i == (int)(s.length()) - 1) {
			this->d = 1;
		}
		else {
			for (i = i + 2; i < (int)(s.length()); i++) {
				num += s[i];
			}
			this->d = stoi(num);
		}
	}
	else { // this is a negative number
		int i;
		for (i = 1; i < (int)(s.length()); i++) {
			if (s[i] == 'x')
				break;
			num += s[i];
		}
		if (s[1] == 'x' || (s[1] == '1' && s[2] == 'x')) {
			this->c = -1;
		}
		else {
			finalC = stod(num) * (-1);
			this->c = finalC;
		}
		num = "";
		for (int j = 0; j < (int)(s.length()); j++) {
			if (s[j] == 'x')
				checkforX = true;
		}
		if (checkforX == false)
		{
			this->d = 0;
		}
		else if (i == (int)(s.length()) - 1) {
			this->d = 1;
		}
		else {
			for (i = i + 2; i < (int)(s.length()); i++) {
				num += s[i];
			}
			this->d = stoi(num);
		}
	}
	this->next = NULL;
	numberOfMonomials++;
}


Monomial::Monomial(const Monomial& other)//copy constructor
	: d(other.d) {
	c = other.c;
	this->next = NULL;
	numberOfMonomials++;
}

Monomial::~Monomial() {//destructor
	numberOfMonomials--;
}

const Monomial& Monomial::operator=(const Monomial& other) { // = operator
	c = other.c;
	d = other.d;
	return *this;
};


Monomial Monomial::operator+(const Monomial& other) const { // + operator
	if (d == other.d) 
		return Monomial(c + other.c, d);
	else 
		return Monomial(c, d);
}

Monomial Monomial::operator-() const { // - unary operator
	return Monomial(-c, d);
}

istream& operator>>(istream& in, Monomial& m) { // >> operator for input
	string s;
	getline(in, s); // append the string into s
	m = s; // set values of m from the input string
	return in;
}

ostream& operator<<(ostream& out, const Monomial& m) { // << operator to print
	m.print();
	return out;
}

Monomial Monomial::operator-(const Monomial& other) const // - operator with the use of + operator and - unary operator
{ // - operator
	return Monomial(c, d) + (-other);
}


Monomial Monomial::operator*(const Monomial& other) const { // * operator
	return Monomial(c * other.c, d + other.d);
}

void Monomial::operator*=(int num) { // *= operator
	c *= num;
}

const Monomial& Monomial::operator+=(const Monomial& other) { // += operator
	*this = *this + other;
	return *this;
}

const Monomial& Monomial::operator-=(const Monomial& other) { // -= operator
	*this = *this - other;
	return *this;
}

const bool Monomial::operator==(const Monomial& other) const { // == logical operator for monomials
	if (c == other.c && d == other.d) return true;
	else return false;
}

const bool Monomial::operator!=(const Monomial& other) const { // != logical operator for monomials
	return !(*this == other);
}

const double Monomial::operator()(const int num) const { // get Monomial value operator using ()
	return c * pow(num, d);
}

void Monomial::print() const { //print the monomial
	if (c == 0)
		cout << 0;
	else if (d == 0) {
		cout << c;
	}
	else if (c == 1 && d == 1) {
		cout << "x";
	}
	else if (c == -1 && d == 1) {
		cout << "-x";
	}
	else if (c == 1 && d > 1) {
		cout << "x^" << d;
	}
	else if (d == 1) { // c != 1
		cout << c << "*x";
	}
	else { // c!=1 && d != 1
		cout << c << "*x^" << d;
	}
}

const bool Monomial::add(const Monomial& other) { //return true if succeed to add
	if (d != other.d)
		return false;
	else {
		c += other.c;
		return true;
	}
};