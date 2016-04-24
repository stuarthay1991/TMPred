//
//  SequenceHelp.cpp
//  TMPred
//
//  Created by Thanmai on 24/04/16.
//  Copyright © 2016 None. All rights reserved.
//

#include "SequenceHelp.hpp"

Map init_transition_matrix(){
    Map result;
    for(char i: "iMo")
        for(char j: "iMo"){
            if( i != '\0' && j != '\0'){
                string x;
                x+= i;
                x+= j;
                result[x] = 0;
            }
        }
    return result;
}


void display_transition(Map result){
    for (Map::iterator it=result.begin(); it!=result.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}


MapList convert_annotation(string amino_acid, string annotation){
    if(amino_acid.length() != annotation.length()){
        cerr << "AMINO ACID and ANNOTATION are not of same length" << endl;
        exit(0);
    }
    
    MapList result;
    vector<int> change_indices;
    
    for(int i = 0; i < annotation.length(); i++){
        if(i == 0){
            change_indices.push_back(i);
            result[annotation[i]] = vector<string>();
        }else if(annotation[i] != annotation[i-1]){
            change_indices.push_back(i);
        }
    }
    
    for(int i=0; i< change_indices.size(); i++){
        cout << change_indices[i];
    }
    return result;
}




