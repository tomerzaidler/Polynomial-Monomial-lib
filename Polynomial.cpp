//
//  Polynomial.cpp
//
//  Created by Tomer Zaidler on 11/12/2019.
//

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iomanip>
#include <iostream>
#include <string>
#include <string.h>
#include "Polynomial.h"
#include "Monomial.h"
using std::string;

using namespace std;
double zero = 0;

Polynomial::Polynomial() //constructor
{
	head = NULL;
}

Polynomial::Polynomial(const Polynomial& other) //copy constructor
{
	head = NULL;
	Monomial* ptr = head, *otherPtr = other.head;
	if (!other.head) return;
	else {
		head = new Monomial(otherPtr->getCoefficient(), otherPtr->getDegree());
		ptr = head;
		otherPtr = otherPtr->getNext();
		while (otherPtr) {
			ptr->setNext(new Monomial(otherPtr->getCoefficient(), otherPtr->getDegree()));
			ptr = ptr->getNext();
			otherPtr = otherPtr->getNext();
		}
	}
}

Polynomial::~Polynomial() //destructor
{
	Monomial* temp = head, *back = head;
	while (temp) {
		temp = temp->getNext();
		delete back;
		back = temp;
	}
}

istream& operator>>(istream& in, Polynomial& p) // >> operator for input
{
	if (p.head) {
		p.deleteAllNodes(); // Clearing the polynom
	}
	p.head = NULL; // reseting the polynomial
	string s;
	getline(in, s); // getting the string from input
	if (s[0] == '\0') {
		cout << "ERROR!! " << endl;
		return in;
	}
	int stringSize = s.length();
	char *dup = strdup(s.c_str()); // duplicating the string to array of chars
	string splitedString = strtok(dup, "+-,");
	char signs[100] = "";
	if (s == "0") {
		return in;
	}
	int numOfSigns = 0;
	// Getting all the signs into an array of signs
	for (int i = 0; i < stringSize; i++) {
		if (s[i] == '+' || s[i] == '-') {
			signs[numOfSigns++] = s[i];
		}
	}
	int k = 0;
	// first monomial's c is negative
	if (s[0] == '-') {
		for (int i = 0; i < numOfSigns; i++) {
			Monomial m;
			// first node case
			if (p.head == NULL) {
				splitedString = signs[k++] + splitedString; // adding '-' to the string
				m = splitedString; // converting string to monom
				p.add(m); // adding the monom to p
			}
			// other nodes caes
			else {
				if (signs[k] == '-') {
					splitedString = signs[k++] + splitedString; // adding '-' to the string
					m = splitedString; // converting to monom
					p.add(m); // adding monom to p
				}
				else {
					m = splitedString; // don't have to add '-' cuz its a positive monom
					p.add(m); // converting to positive monom
					k++; // adding monom to p
				}
			}
			if (k != numOfSigns)
				splitedString = strtok(NULL, "+-"); // continue cut the string by + , -
		}
	}
	// first monomial's c is positive
	else {
		for (int i = 0; i <= numOfSigns; i++) {
			Monomial m;
			// first node case
			if (p.head == NULL) {
				m = splitedString; // don't have to add a sign cuz it's positive already
				p.add(m); // adding to p
			}
			else {
				if (signs[k] == '-') {
					splitedString = signs[k++] + splitedString; // adding '-' to string
					m = splitedString; // converting to monom
					p.add(m); // adding monom to p
				}
				else {
					m = splitedString; // converting monom
					p.add(m); // adding monom to p
					k++;
				}
			}
			if (k < numOfSigns)
				splitedString = strtok(NULL, "+-"); // continue cut by "+" or "-"
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const Polynomial& p) // << operator to print
{
	// prints the monom
	p.print();
	return out;
}

const Polynomial& Polynomial::operator=(const Polynomial& other)  // = operator
{
	if (*this == other) return *this;
	if (head) { // in case they are not equal, clear the polynom
		this->deleteAllNodes();
	}
	if (other.head) { // copying other polynom's nodes to this
		Monomial* otherPtr = other.head;
		while (otherPtr != NULL) {
			this->add(*otherPtr);
			otherPtr = otherPtr->getNext();
		}
	}
	return *this;
}


Polynomial Polynomial::operator+(const Polynomial& other) const // + operator between 2 Poly's
{
	Polynomial newPoly;
	Monomial* polyPtr = head;
	while (polyPtr != NULL) {
		newPoly.add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head;
	while (polyPtr != NULL) {
		newPoly.add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	return newPoly; // Returns object by value
}

Polynomial Polynomial::operator+(const Monomial& mon) const // + operator between Poly and monomial
{
	Polynomial temp = *this;
	temp.add(mon);
	return temp;
}

Polynomial Polynomial::operator-(const Polynomial& other) const  // - operator between 2 Poly's
{
	Monomial* polyPtr = head;
	Polynomial newPoly;
	while (polyPtr != NULL) {
		newPoly.add(Monomial(*polyPtr));
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head;
	while (polyPtr != NULL) {
		newPoly.add(-(Monomial(*polyPtr)));
		polyPtr = polyPtr->getNext();
	}
	return newPoly;
}

Polynomial Polynomial::operator-(const Monomial& mon) const // - operator between Poly and monomial
{
	Polynomial temp = *this;
	temp.add(-mon);
	return temp;
}


Polynomial Polynomial::operator-() const // - unary operator
{
	Polynomial newPoly;
	if (!head) return newPoly; // Returns empty polynomial

	Monomial* monPtr = head;
	Monomial* ptr = head;
	if (head) { /// Set the head of the new polynomial
		newPoly.head = new Monomial(-head->getCoefficient(), head->getDegree());
		monPtr = newPoly.head;
		ptr = head->getNext();
	}
	while (ptr != NULL) {
		monPtr->setNext(new Monomial(-(ptr->getCoefficient()), ptr->getDegree()));
		monPtr = monPtr->getNext();
		ptr = ptr->getNext();
	}
	return newPoly; // Returns object by value
}

const Polynomial& Polynomial::operator+=(const Monomial& mon) // += operator between Poly and monomial
{
	this->add(mon);
	return *this;
}

const Polynomial& Polynomial::operator+=(const Polynomial& other) // += operator between 2 Poly's
{
	Monomial* otherPtr = other.head;
	while (otherPtr) {
		this->add(*otherPtr);
		otherPtr = otherPtr->getNext();
	}
	return *this;
}

const Polynomial& Polynomial::operator-=(const Monomial& mon) // -= operator between Poly and monomial
{
	this->add(-mon);
	return *this;
}

const Polynomial& Polynomial::operator-=(const Polynomial& other) // -= operator between 2 Poly's
{
	Monomial* otherPtr = other.head;
	while (otherPtr) {
		this->add(-(*otherPtr));
		otherPtr = otherPtr->getNext();
	}
	return *this;
}

double& Polynomial::operator[](int num) // get coefficcient by the degree of monom in the polynom
{ 
	Monomial* current = head;

	if (head == NULL) return zero; // list is empty, returning 0
	while (current != NULL) {
		if (current->getDegree() == num) {
			return (current->getCoeByRef()); //  Get the coefficient by ref to read/re-assign
		}
		else current = current->getNext();
	}
	return zero; // If the degree hasn't been found -> returning 0
}

const double Polynomial::operator()(const int num) const // get Monomial value operator using ()
{
	Monomial* current = head;
	double polyValue = 0;
	while (current != NULL) {
		polyValue += (*current)(num);
		current = current->getNext();
	}
	return polyValue;
}

const bool Polynomial::operator==(const Polynomial& other) const // == operator between 2 Poly's
{
	if (!head || !other.head) return false;
	Monomial* monPtr = head;
	Monomial* otherPtr = other.head;
	while (monPtr && otherPtr) {
		if (monPtr->getCoefficient() == otherPtr->getCoefficient() &&
			monPtr->getDegree() == otherPtr->getDegree())
		{
			monPtr = monPtr->getNext();
			otherPtr = otherPtr->getNext();
		}
		else return false;
	}
	if (otherPtr || monPtr) return false; // didn't reach the end of one of the polynomials
	else return true; // They are equal
};

const bool Polynomial::operator==(const Monomial& mon) const // == logical operator between Poly and monomial
{
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return true;
	else return false;
};

const bool Polynomial::operator!=(const Polynomial& other) const // != operator between 2 Poly's
{
	if (!head || !other.head) return true;
	Monomial* monPtr = head;
	Monomial* otherPtr = other.head;
	while (monPtr && otherPtr) {
		if (monPtr->getCoefficient() == otherPtr->getCoefficient() &&
			monPtr->getDegree() == otherPtr->getDegree())
		{
			monPtr = monPtr->getNext();
			otherPtr = otherPtr->getNext();
		}
		else return true;
	}
	if (otherPtr || monPtr) 
		return true; // didn't reach the end of one of the polynomials
	else 
		return false; // the 2 Poly's are equal
};

const bool Polynomial::operator!=(const Monomial& mon) const // != logical operator between Poly and monomial
{
	if (head == NULL && mon.getCoefficient() == 0) return false;
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return false;
	else return true;
};

void Polynomial::deleteAllNodes() // delete all nodes(monomials) from polynomial
{
	Monomial* ptr = head, *toDelete = head;
	while (ptr != NULL) {
		ptr = ptr->getNext();
		delete toDelete;
		toDelete = ptr;
	}
	head = NULL;
}

void Polynomial::print() const // print Polynomial
{
	// list is empty or filled only by zero
	if (head == NULL || (head->getCoefficient() == 0 && head->getNext() == NULL)) {
		cout << 0;
		return;
	}
	else {
		Monomial *monomsPtr = head;
		while (monomsPtr != NULL) {
			if (monomsPtr->getCoefficient() != 0) monomsPtr->print();
			if (
				monomsPtr->getNext() != NULL &&
				monomsPtr->getNext()->getCoefficient() > 0
				)
				cout << "+";
			monomsPtr = monomsPtr->getNext();
		}
	}
}

void Polynomial::add(const Monomial& monToAdd) // add monomial to the polynomial
{
	if (head == NULL) {
		head = new Monomial(monToAdd);
		return;
	}
	else if (monToAdd.getCoefficient() == 0)
	{
		return;
	}
	Monomial *monomsPtr = head, *prev = NULL;

	while (monomsPtr) {
		if (monomsPtr->add(monToAdd)) { // Found monomial with same degree
			if (monomsPtr->getCoefficient() == 0) { // if monomial coe is 0 need to vanish
				if (prev) {
					prev->setNext(monomsPtr->getNext());
				}
				else {
					head = monomsPtr->getNext();
				}
				delete monomsPtr;
			}
			return;
		}
		else if (monToAdd.getDegree() > monomsPtr->getDegree()) { // Need to insert before monomsptr
			Monomial* newMonToAdd = new Monomial(monToAdd);
			newMonToAdd->setNext(monomsPtr);
			if (prev) {
				prev->setNext(newMonToAdd);
			}
			else {
				head = newMonToAdd;
			}
			return;
		}
		prev = monomsPtr;
		monomsPtr = monomsPtr->getNext();
	}

	// If reached so far need to add to the end of the list
	Monomial* newMonToAdd = new Monomial(monToAdd);
	prev->setNext(newMonToAdd);
}