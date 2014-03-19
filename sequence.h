#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED

#include <string>

using namespace std;

class sequence
{
	private:
		string _h;
		string _b;
	public:
		sequence(string a, string b);
		~sequence();
		string header();
		string body();
};

#endif