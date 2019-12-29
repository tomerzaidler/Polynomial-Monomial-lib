//
//  Monomial.h
//
//  Created by Tomer Zaidler on 11/12/2019.
//

#ifndef Monomial_h

#define Monomial_h
#include <iomanip>
#include <iostream>
using namespace std;

class Monomial {
private:
	double c; // monomial coefficient
	int d;	// monomial degree
	static int numberOfMonomials; // static integer to count how many monomials we created
	Monomial* next; // pointer next for the next node on linked list

public:
	Monomial(double coe = 1, const int deg = 0); //constructor
	Monomial(const Monomial& other); //copy constructor
	Monomial(string); // string constructor
	~Monomial(); //destructor
	const Monomial& operator=(const Monomial& other); // = operator
	Monomial operator+(const Monomial& other) const; // + operator
	Monomial operator-() const; // - unary operator
	Monomial operator-(const Monomial& other) const; // - operator with the use of + operator and - unary operator
	Monomial operator*(const Monomial& other) const; // * operator
	void operator*=(int num); // *= operator
	const Monomial& operator+=(const Monomial& other); // += operator
	const Monomial& operator-=(const Monomial& other); // -= operator
	const bool operator==(const Monomial& other) const; // == logical operator for monomials
	const bool operator!=(const Monomial& other) const; // != logical operator for monomials
	const double operator()(const int num) const; // get Monomial value operator using ()
	friend ostream& operator <<(ostream&, const Monomial&); // << operator to print
	friend istream& operator >>(istream&, Monomial&); // >> operator for input
	const bool add(const Monomial& other); //return true if succeed to add
	static int getNumberOfMonomials() { return numberOfMonomials; }; // get the number of monomials
	void print() const; //print the monomial
	const int getDegree() const { return d; }; // return the value of this monomial degree
	double getCoefficient() const { return c; }; //return the value of this monomial coefficcient
	double& getCoeByRef() { return c; }; //return the c by reference of this monomial
	Monomial* getNext() const { return next; }; // get the next monomial in linked list(polynomial)
	void setCoefficient(const int coe) { c = coe; }; // set new value to this monomial coefficcient
	void setDegree(const int deg) { d = deg; }; // set new value to this monomial degree
	void setNext(Monomial *newNext) { next = newNext; }; //set the monomial *next
};

#endif /* Monomial_h */
