#include "stdafx.h"
#include "msa.h"
#include <time.h>
#include <algorithm>
#include <cmath>

using namespace std;

msa::msa(vector <sequence*> sequences)
{
	unsigned int max = 0, i;
	for (i = 0; i < sequences.size(); i++)
		if (sequences[i]->body().length() > max)
			max = sequences[i]->body().length();

	this->s = sequences;
	this->lmin = max;
	this->lmax = (int)(max * 1.2 + 0.5);
}

msa::msa(vector <sequence*> sequences, int lmin, int lmax)
{
	this->s = sequences;
	this->lmin = lmin;
	this->lmax = lmax;
}

void msa::randomAlignment()
{
	this->len = this->get_random_int(this->lmin, this->lmax);
	this->m.clear();
	for (unsigned int i = 0; i < this->s.size(); i++)
	{
		set <int> row;
		for (unsigned int j = this->s[i]->body().length(); j < this->len; j++)
		{
			int c = this->get_random_int(0, j - 1);
			if (row.find(c) == row.end()) 
				row.insert(c);
			else 
				row.insert(j);
		}
		this->m.push_back(row);
	}
}

void msa::randomNeightborAlignment()
{
    vector <set<int>> gapped_seqs;
    for (unsigned int x = 0; x < this->s.size(); x++)
    {
        if (this->m[x].size() > 0) {
            gapped_seqs.push_back(this->m[x]);
        }
    }
    int rseq = this->get_random_int(0, gapped_seqs.size() - 1), 
        al = this->s[0]->body().length() + this->m[0].size(),
        gbc = this->get_random_int(1, gapped_seqs[rseq].size()),
        i = gbc, j = 0, skip;

    set<int> mm = gapped_seqs[rseq];
    set<int>::iterator mmit = mm.end();
    mmit--;
    set<int> mmcpy;
    while (i-- > 0)
    {
		if (mm.size() == 1)
		{
			mm.clear();
			break;
		}
        skip = this->get_random_int(1, mm.size() - 1);
        while (skip-- > 0)
        {
            mmcpy.insert(*mmit - 1);
            mmit--;
        }
        while (mmit-- != mm.begin())
            mmcpy.insert(*mmit);
        mm = mmcpy;
        mmit = mm.end();
        mmit--;
		mmcpy.clear();
    }
}

bool msa::is_rand_inited = false;

int msa::get_random_int(int min, int max)
{
	if (!is_rand_inited)
	{
		srand((unsigned)time(NULL));
        is_rand_inited = true;
	}

	return rand() % (max - min + 1) + min;
}

vector <set<int>> msa::matrix()
{
	return this->m;
}

vector <sequence*> msa::sequences()
{
	return this->s;
}

int msa::msaLen()
{
	return this->len;
}

vector <string> msa::getMsa()
{
	vector <string> aligns;
	unsigned int i, j, skip;
	for (i = 0; i < this->s.size(); i++)
	{
		string seq (this->s[i]->header());
		seq += string (10 - seq.length(), ' ');
		skip = 0;
		set<int>::iterator it = this->m[i].begin();
		for (j = 0; j < this->s[i]->body().length() + this->m[i].size(); j++)
		{
			if (this->m[i].size() > 0 && it != this->m[i].end() && *it == j)
			{
				skip++;
				it++;
				seq.append("_");
			} else {
				seq += this->s[i]->body()[j - skip];
			}
		}
		for (j = this->s[i]->body().length() + this->m[i].size(); j < this->len; j++)
		{
			seq.append("_");
		}
		aligns.push_back(seq);
	}
	return aligns;
}
