#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "header.h"

void CleanSeq::pruneAndAdd(string amino, string annotation)
{
    string outstring_amino = "";
    string outstring_anno = "";
    vector<string> outstring;
    int stringlength = amino.length();
    for(int i = 0; i<stringlength; i++)
    {
        if(annotation[i] == '.')
        {
            continue;
        }
        else
        {
            outstring_amino = outstring_amino + amino[i];
            outstring_anno = outstring_anno + annotation[i];
        }
    }
    outstring.push_back(outstring_amino);
    outstring.push_back(outstring_anno);
    output.push_back(outstring);
}

void CleanSeq::read(string infile)
{
    string line;
    ifstream readfile(infile);
    if(readfile.is_open())
    {
        while(getline(readfile, line))
        {
            content.push_back(line);
        }
        readfile.close();
    }
}

void CleanSeq::fill()
{
    int T_FLAG = 0;
    for(int i = 0; i < content.size(); i++)
    {
        T_FLAG = 0;
        string am;
        string an;
        for(int k = 0; k < content[i].size(); k++)
        {
            if(content[i][k] == '\t')
            {
                T_FLAG = 1;
                continue;
            }
            if(T_FLAG == 0)
            {
                am = am + content[i][k];
            }
            if(T_FLAG == 1)
            {
                an = an + content[i][k];
            }
        }
        pruneAndAdd(am, an);
    }
}

vector<vector<string>> CleanSeq::print()
{
    return output;
}

int main(int argc, const char * argv[])
{
    string bob1 = "PPPLLLPPP";
    string bob2 = "MMM...MMM";
    string line;
    string myfile ="/Users/haysb/Desktop/TMPred/TMPred/test.ffa";
    CleanSeq bob;
    bob.read(myfile);
    bob.fill();
    vector<vector<string>> outlist = bob.print();
    for(int i = 0; i < outlist.size(); i++)
    {
        std::cout << outlist[i][0].length() << " " << outlist[i][1].length() << "\n";
    }

    return 0;
}
