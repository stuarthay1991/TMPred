//
//  MainHeader.h
//  TMPred
//
//  Created by Thanmai on 24/04/16.
//  Copyright © 2016 None. All rights reserved.
//

#ifndef MainHeader_h
#define MainHeader_h

#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef map<string, float> Map;

// For Sequence Type: { i: ['ASDADS', 'ASDASD' ] }
typedef map<char,vector<string> > MapList;


// For Sequence Distance List { i: [6, 6, 6 ] }
typedef map<char, vector<int> > DefaultDict;

#endif /* MainHeader_h */
