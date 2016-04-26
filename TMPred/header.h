#include <vector>
#include <string>
#include "SequenceHelp.hpp"

using namespace std;
class CleanSeq{
public:
	void pruneAndAdd(string amino, string annotation);
    	void read(string infile);
    	void fill();
    	vector<vector<string> > print();
private:
    	vector<string> content;
    	vector<vector<string> > output;
};

class AAandStateFreq{
public:
	AAandStateFreq(vector<vector<string> > invector);
	void findInitialStateFreqs();
	void findAAFreqByState();
	double iInitialFreq = 0;
	double oInitialFreq = 0;
	double MInitialFreq = 0;
	AAFreqList AAifrequencies;
	AAFreqList AAMfrequencies;
	AAFreqList AAofrequencies;
private:
	vector<vector<string> > content;
};


