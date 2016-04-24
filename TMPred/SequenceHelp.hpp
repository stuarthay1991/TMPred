//
//  SequenceHelp.hpp
//  TMPred
//
//  Created by Thanmai on 24/04/16.
//  Copyright © 2016 None. All rights reserved.
//

#ifndef SequenceHelp_hpp
#define SequenceHelp_hpp

#include <stdio.h>
#include <iostream>
#include "MainHeader.h"

using namespace std;

/*
 *  Input: Nothing
 *  Output: Map[String,int] ==> { iM: 0, MM: 0 .... }
 *  Initialize Transition Matrix
 */
Map init_transition_matrix();


/*
 *  Input: Transition Matrix of the Map form
 *  Output: Nothing
 *  Display Transition Matrix
 */
void display_transition(Map result);


/*
 *  Input: String amino acid, annotation. Ex: ( ASDARAASDSDF, iiiMMMoooMMM )
 *  Output: List annotation based amino acids. Ex: { i: [ 'ASD' ], M: [ 'ARA', 'SDF' ], o: [ 'ASD' ] }
 *  Converts the given record to a sequence type usable.
 */
MapList convert_annotation(string amino_acid, string annotation);



#endif /* SequenceHelp_hpp */
