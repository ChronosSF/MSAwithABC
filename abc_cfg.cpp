#include "stdafx.h"
#include "abc_cfg.h"

abc_cfg::abc_cfg()
{
    count_of_scout_bees = 20;
    count_of_best_areas = 2;
    count_of_perspective_areas = 5;
    count_of_bees_to_best_area = 10;
    count_of_bees_to_perspective_area = 2;
    max_iterations = 600;
	t_init = 10000;
	alpha = 0.95;
}

int abc_cfg::fitness(vector<sequence*> sequences, vector <set<int>> matrix, unsigned int len)
{
	unsigned int i, j, k, s = sequences.size(), score = 0;
	set<int>::iterator * iters = new set<int>::iterator [s];
	int * skip = new int [s];
	for (i = 0; i < s; i++) {
		iters[i] = matrix[i].begin();
		skip[i] = 0;
	}
	// for each position of the alignment calculate score
	for (i = 0; i < len; i++)
	{
		int sl = 0;
		string row;
		for (j = 0; j < s; j++)
			if (matrix[j].size() > 0 && iters[j] != matrix[j].end() && i == *iters[j]) { row.append("_"); skip[j]++; iters[j]++;} 
			else if (sequences[j]->body().length() > i - skip[j]) { row.push_back(sequences[j]->body()[i - skip[j]]); }
			else { row.append("_"); }
		// for each combination of letters in the sequences
		for (j = 0; j < s - 1; j++)
			for (k = j + 1; k < s; k++)
				if (row[j] == row[k] && row[j] != '_' && row[k] != '_')
					sl++;

		score += sl;
	}
	return score;
}

