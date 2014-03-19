#include "stdafx.h"
#include "abc.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

abc::abc(abc_cfg config)
{
    abc::config = config;
}

msa* abc::solve()
{
    int count_of_bees = config.count_of_scout_bees +
                    config.count_of_bees_to_best_area * config.count_of_best_areas +
                    config.count_of_bees_to_perspective_area * config.count_of_perspective_areas;

    vector <bee *> bees;
	double t_cur = config.t_init;

    for (int i = 0; i < count_of_bees; ++i)
    {
		msa* a = new msa(config.sequences);
		a->randomAlignment();
		bees.push_back(new bee(a, config.fitness(a->sequences(), a->matrix(), a->msaLen())));
    }

    sort(bees.begin(), bees.end(), compare);

    for (int i = 0; i < config.max_iterations; ++i)
    {
        int j = 0, size, l = config.count_of_best_areas + config.count_of_perspective_areas;

        for (size = config.count_of_best_areas; j < size; ++j)
        {
            for (int k = 0; k < config.count_of_bees_to_best_area - 1; ++k)
            {
				bees[l]->align->randomNeightborAlignment();
				bees[l]->score = config.fitness(bees[l]->align->sequences(), bees[l]->align->matrix(), bees[l]->align->msaLen());
                l++;
            }
        }

        for (size += config.count_of_perspective_areas; j < size; ++j)
        {
            for (int k = 0; k < config.count_of_bees_to_perspective_area - 1; ++k)
            {
				bees[l]->align->randomNeightborAlignment();
				bees[l]->score = config.fitness(bees[l]->align->sequences(), bees[l]->align->matrix(), bees[l]->align->msaLen());
                l++;
            }
        }

        for (;l < count_of_bees;)
        {
			msa *n = new msa(config.sequences);
			n->randomAlignment();
			double ns = config.fitness(n->sequences(), n->matrix(), n->msaLen());
			if (ns > bees[l]->score || this->metropolisAccepted(ns, bees[l]->score, t_cur))
			{
				bees[l]->align = n;
				bees[l]->score = ns;
			}
			//Simple
			//bees[l]->align->randomAlignment();
			//bees[l]->score = config.fitness(bees[l]->align->sequences(), bees[l]->align->matrix(), bees[l]->align->msaLen());
            l++;
        }

        sort(bees.begin(), bees.end(), compare);
		t_cur = config.alpha * t_cur;
		if (t_cur < 0.0001) 
			break;
    }

	return bees[0]->align;
}

abc::bee::bee(msa * align, int score)
{
	bee::align = align;
	bee::score = score;
}

bool abc::compare(bee * a, bee * b)
{
    return a->score > b->score;
}

bool abc::metropolisAccepted(double fa, double fb, double t)
{
	//return exp((fa - fb) / t) > ((double) rand() / (RAND_MAX + 1));
	double e = exp((fa - fb) / t);
	return  e > ((double) rand() / (RAND_MAX + 1));
}

