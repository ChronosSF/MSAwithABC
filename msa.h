#include <vector>
#include <set>
#include "sequence.h"

using namespace std;

class msa
{
	private:
		vector <sequence*> s;
		vector <set<int>> m;
		unsigned int lmax;
		unsigned int lmin;
		unsigned int len;
	public:
		msa(vector <sequence*>);
		msa(vector <sequence*>, int, int);
		void randomAlignment();
		void randomNeightborAlignment();
		int msaLen();
		static bool is_rand_inited;
		static int get_random_int(int, int);
		vector <sequence*> sequences();
		vector <set <int>> matrix();
		vector <string> getMsa();
};