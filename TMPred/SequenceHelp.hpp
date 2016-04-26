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



class SequenceType{
    
public:
    
    /*
     *  Input: String amino acid, annotation. Ex: ( ASDARAASDSDF, iiiMMMoooMMM )
     *  Output: List annotation based amino acids. Ex: { i: [ 'ASD' ], M: [ 'ARA', 'SDF' ], o: [ 'ASD' ] }
     *  Converts the given record to a sequence type usable.
     */
    void convert_annotation(string amino_acid, string annotation);
    
    void calculateProbability();
    
    void update_transition_matrix(char i, char j, string annotation);

    void display_blah();
    
    /*
     *  Input: Transition Matrix of the Map form
     *  Output: Nothing
     *  Display Transition Matrix
     */
    void display_transition();

    void display_sequence();
    
    /*
     *  Input: Nothing.
     *  Output: Returns a Default Dict of type { i : [6, 7, 10, 2] } based on the length.
     */
    DefaultDict get_durations();
    
    /*
     *  Contructor that initalizes the Transition Matrix
     */
    SequenceType();
    
    Map transition_matrix;
    MapList sequence_lists;
};


class Normalization{
public:
    
    Normalization(DefaultDict distance);
    array_2d get_normalised_distance();
    void verification_norm();
    DefaultDict distances;
    array_2d normalized_distances;
};



#endif /* SequenceHelp_hpp */
