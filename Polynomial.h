//
//  Polynomial.h
//
//  Created by Tomer Zaidler on 11/12/2019.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include "Monomial.h"

using namespace std;

class Polynomial {
private:
	Monomial* head;

public:
	Polynomial(); //constructor
	Polynomial(const Polynomial& other); //copy constructor
	~Polynomial(); //destructor
	friend istream& operator>>(istream&, Polynomial&); // >> operator for input
	friend ostream& operator<<(ostream&, const Polynomial&); // << operator to print
	const Polynomial& operator=(const Polynomial& other); // = operator
	Polynomial operator+(const Polynomial& other) const; // + operator between 2 Poly's
	Polynomial operator+(const Monomial& mon) const; // + operator between Poly and monomial
	Polynomial operator-(const Polynomial& other) const; // - operator between 2 Poly's
	Polynomial operator-(const Monomial& mon) const; // - operator between Poly and monomial
	Polynomial operator-() const; // - unary operator
	const Polynomial& operator+=(const Monomial& mon); // += operator between Poly and monomial
	const Polynomial& operator+=(const Polynomial& other); // += operator between 2 Poly's
	const Polynomial& operator-=(const Monomial& mon); // -= operator between Poly and monomial
	const Polynomial& operator-=(const Polynomial& other); // -= operator between 2 Poly's
	double& operator[](int num); // get coefficcient by the degree of monom in the polynom
	const double operator()(int num) const;  // get Monomial value operator using ()
	const bool operator==(const Polynomial& other) const; // == operator between 2 Poly's
	const bool operator==(const Monomial& mon) const; // == logical operator between Poly and monomial
	const bool operator!=(const Polynomial& other) const; // != operator between 2 Poly's
	const bool operator!=(const Monomial& mon) const; // != logical operator between Poly and monomial
	void print() const; // print Polynomial
	void add(const Monomial& monToAdd); // add monomial to the polynomial
	void deleteAllNodes(); // delete all nodes(monomials) from polynomial
};