#ifndef ABC_H_INCLUDED
#define ABC_H_INCLUDED

#include <vector>
#include <algorithm>
#include <time.h>
#include "abc_cfg.h"
#include "msa.h"

using namespace std;

class abc
{
	private:
		struct bee
		{
			msa* align;
			double score;
			bee(msa*, int);
		};
		abc_cfg config;
		static bool compare(bee*, bee*);
		bool metropolisAccepted(double, double, double);
	public:
		abc(abc_cfg);
		msa* solve();
};
#endif
