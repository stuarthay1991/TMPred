//
//  main.cpp
//  TMPred
//
//  Created by Stuart Brendan Hay on 4/24/16.
//  Copyright (c) 2016 None. All rights reserved.
//

#include <iostream>
#include "SequenceHelp.hpp"

using namespace std;

void display_duration(DefaultDict result){
    for(DefaultDict::iterator it = result.begin(); it != result.end(); ++it) {
        cout << it->first << "," << endl;
        vector<int> resu = it->second;
        for(int i = 0 ;i < resu.size(); i++)
            cout << resu[i] << endl;
    }
}

int main(){
    //convert_annotation("ADSASDADAUDS", "iiiMMMoooMMM");
    SequenceType s = SequenceType();
    s.convert_annotation("ADSASDADAUDS", "iiiMMMoooMMM");
    s.display_sequence();
    s.calculateProbability();
    s.display_transition();
    DefaultDict x = s.get_durations();
    display_duration(x);
    return 0;
}

