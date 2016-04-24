#include <vector>
#include <string>
using namespace std;
class CleanSeq{
public:
    void pruneAndAdd(string amino, string annotation);
    void read(string infile);
    void fill();
    vector<vector<string>> print();
private:
    vector<string> content;
    vector<vector<string>> output;
};


