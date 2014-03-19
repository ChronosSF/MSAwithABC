#include "stdafx.h"
#include "abc.h"
#include "sequence.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector <sequence*> readInput(char* fileName)
{
	ifstream infile(fileName);
	vector <sequence*> sequences;
	infile.seekg(0, ios_base::end);
	streamoff size = infile.tellg();
	infile.seekg(0, std::ios_base::beg);
	if (size <= 0)
	{
		return sequences;
	}
	unsigned int len = static_cast<unsigned int>(size);
	while (!infile.eof()) {
		char *a = new char[len];
		char *b = new char[len];
		infile.getline(a, len);
		infile.getline(b, len);
		sequence *seq = new sequence(a, b);
		sequences.push_back(seq);
	}
	infile.close();
	return sequences;
 }

void writeOutput(msa* best, double score)
{
	ofstream outfile("MSA.txt", ios::out | ios::trunc);
	vector <string> best_align = best->getMsa();
	for (unsigned int i = 0; i < best_align.size(); i++)
	{
		outfile << best_align[i] << endl;
	}
	outfile << score << endl;
	outfile.flush();
	outfile.close();
}

int main(int argc, char** argv)
{
	// ensure one argument is passed
	if (argc != 2)
	{
		cout << "The application requires one multiple sequence file to be passed as arguments!" << endl;
		return 1;
	}
	vector <sequence*> sequences = readInput(argv[1]); 
	abc_cfg config;
	config.sequences = sequences;

    abc *algorithm = new abc(config);
	msa *best = algorithm->solve();
	double bestScore = config.fitness(best->sequences(), best->matrix(), best->msaLen());
	writeOutput(best, bestScore);

    return 0;
}
