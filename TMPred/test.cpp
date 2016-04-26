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
    Normalization norm = Normalization(x);
    array_2d dist_norm = norm.get_normalised_distance();
    
    for(int i=0; i < dist_norm.size(); i++){
        vector<double> row = dist_norm[i];
        for(int j = 0; j < row.size(); j++){
            cout << dist_norm[i][j] << " " << endl;
        }
        
    }
    
    return 0;
}

