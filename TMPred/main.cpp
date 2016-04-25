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

int main(int argc, const char * argv[])
{
    
    // insert code here...
    cout << "Hello, World!\n";
    //display_transition(init_transition_matrix());
    //convert_annotation("ADSASDADAUDS", "iiiMMMoooMMM");
    SequenceType s = SequenceType();
    s.convert_annotation("ADSASDADAUDS", "iiiMMMoooMMM");
    return 0;
}
