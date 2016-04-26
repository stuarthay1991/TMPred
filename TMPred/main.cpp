#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "header.h"

#define amino_alphabet "ARNDCQEGHILKMFPSTWYV"

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

vector<vector<string> > CleanSeq::print()
{
    return output;
}

AAandStateFreq::AAandStateFreq(vector<vector<string> > invector)
{
    content = invector;
}

void AAandStateFreq::findInitialStateFreqs()
{
    int iCount = 0;
    int oCount = 0;
    int MCount = 0;
    for(int i = 0; i < content.size(); i++)
    {
        if(content[i][1][0] == 'i')
        {
            iCount = iCount + 1;
        }
        if(content[i][1][0] == 'o')
        {
            oCount = oCount + 1;
        }
        if(content[i][1][0] == 'M')
        {
            MCount = MCount + 1;
        }
    }
    double sum = iCount + oCount + MCount;
    iInitialFreq = iCount / sum;
    oInitialFreq = oCount / sum;
    MInitialFreq = MCount / sum;
}

void AAandStateFreq::findAAFreqByState()
{
    AACountList aaiCounts;
    AACountList aaMCounts;
    AACountList aaoCounts;
    for(char i: amino_alphabet)
    {
        if(i != NULL)
        {
        aaiCounts[i] = 0;
        aaMCounts[i] = 0;
        aaoCounts[i] = 0;
        }
    }
    for(char i: amino_alphabet)
    {
        if(i != NULL)
        {
            for(int k = 0; k<content.size(); k++)
            {
                for(int j = 0; j<content[k][0].length(); j++)
                {
                    if(content[k][1][j] == 'i' and content[k][0][j] == i)
                        aaiCounts[i] = aaiCounts[i] + 1;
                    if(content[k][1][j] == 'M' and content[k][0][j] == i)
                        aaMCounts[i] = aaMCounts[i] + 1;
                    if(content[k][1][j] == 'o' and content[k][0][j] == i)
                        aaoCounts[i] = aaoCounts[i] + 1;
                }
            }
        }
    }
    double isum = 0;
    double Msum = 0;
    double osum = 0;
    for(char i: amino_alphabet)
    {
        if(i != NULL)
        {
            isum = isum + aaiCounts[i];
            Msum = Msum + aaMCounts[i];
            osum = osum + aaoCounts[i];
        }
    }

    for(char i: amino_alphabet)
    {
        if(i != NULL)
        {
            AAifrequencies[i] = aaiCounts[i] / isum;
            AAMfrequencies[i] = aaMCounts[i] / Msum;
            AAofrequencies[i] = aaoCounts[i] / osum;
        }
    }

}

int main(int argc, const char * argv[])
{
    string bob1 = "PPPLLLPPP";
    string bob2 = "MMM...MMM";
    string line;
    string myfile ="test.ffa";
    CleanSeq bob;
    bob.read(myfile);
    bob.fill();
    vector<vector<string> > outlist = bob.print();
    SequenceType s = SequenceType();

    cout << "CHECKING LENGTHS..." << endl;
    for(int i = 0; i < outlist.size(); i++)
    {
        std::cout << outlist[i][0].length() << " " << outlist[i][1].length() << "\n";
        //s.convert_annotation("ADSASDADAUDS", "iiiMMMoooMMM");
        s.convert_annotation(outlist[i][0], outlist[i][1]);
    }

    cout << "DURATION LISTS BY CHARACTER" << endl;
    s.display_blah();

    AAandStateFreq outlistfreqs(outlist);

    outlistfreqs.findInitialStateFreqs();
    outlistfreqs.findAAFreqByState();
    cout << "INITIAL FREQ" << '\n';
    cout << outlistfreqs.iInitialFreq << '\n';
    cout << outlistfreqs.oInitialFreq << '\n';
    cout << outlistfreqs.MInitialFreq << '\n';
    
    cout << "FREQUENCY BY LETTER" << '\n';
    for(char i: "ARNDCQEGHILKMFPSTWYV")
    {
        if(i != NULL)
        {
            cout << "LETTER: " << i << '\n';
            cout << "STATE i: " << outlistfreqs.AAifrequencies[i] << '\n';
            cout << "STATE M: " << outlistfreqs.AAMfrequencies[i] << '\n';
            cout << "STATE o: " << outlistfreqs.AAofrequencies[i] << '\n'; 
        }
    }

    return 0;
}
