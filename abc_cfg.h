#ifndef ABC_CFG_H_INCLUDED

#include "sequence.h"
#include <vector>
#include <set>

using namespace std;

struct abc_cfg
{
	vector <sequence*> sequences;
    int count_of_scout_bees;
    int count_of_best_areas;
    int count_of_perspective_areas;
    int count_of_bees_to_best_area;
    int count_of_bees_to_perspective_area;
	double t_init;
	double alpha;
	int fitness(vector<sequence*>, vector <set<int>>, unsigned int);
	double gap_open;
	double gap_extend;
    int max_iterations;
	vector <vector<double>> matrix;
    abc_cfg();
};

#endif
