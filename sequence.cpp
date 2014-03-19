#include "stdafx.h"
#include "sequence.h"


sequence::sequence(string a, string b)
{
	this->_h = a;
	this->_b = b;
}

sequence::~sequence() 
{
	this->_h.clear();
	this->_b.clear();
}

string sequence::body()
{
	return this->_b;
}

string sequence::header()
{
	return this->_h;
}