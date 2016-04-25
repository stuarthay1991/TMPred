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

SequenceType::SequenceType(){
    this->transition_matrix = init_transition_matrix();
}


void SequenceType::display_transition(){
    for (Map::iterator it=this->transition_matrix.begin(); it!=this->transition_matrix.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}


void SequenceType::update_transition_matrix(char i, char j, string annotation){
    string key_temp;
    key_temp += annotation[i];
    if(annotation[j] != '\0'){
        key_temp += annotation[j];
        this->transition_matrix[key_temp] += 1;
    }
}

void SequenceType::calculateProbability(){
    for(char state: "iMo"){
        int total_trans = 0;
        //Working on probability calculation.
        for(Map::iterator it = this->transition_matrix.begin(); it != this->transition_matrix.end(); ++it){
            if(it->first[0] == state)
                total_trans += it->second;
        }
        
        for(Map::iterator it = this->transition_matrix.begin(); it != this->transition_matrix.end(); ++it){
            if(it->first[0] == state)
                it->second = it->second / (float)total_trans;
        }
    }
}


void SequenceType::convert_annotation(string amino_acid, string annotation){
    if(amino_acid.length() != annotation.length()){
        cerr << "AMINO ACID and ANNOTATION are not of same length" << endl;
        exit(0);
    }
    
    string temp;
    
    for (int i = 0; i < annotation.length(); i++) {
        if(annotation[i] != annotation[i+1] || i+1 == annotation.length()){
            // Found a change in the sequence, do following:
            temp += amino_acid[i];
            // Update list for that annotation.
            if(this->sequence_lists.find(annotation[i]) == this->sequence_lists.end())
                this->sequence_lists[annotation[i]] = vector<string>();
            this->sequence_lists[annotation[i]].push_back(temp);
            temp = "";
            // Update transition matrix for that annotation.
            this->update_transition_matrix(i, i+1, annotation);
        }else{
            temp += amino_acid[i];
        }
    }
    
}

void SequenceType::display_sequence(){
    for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it) {
                    cout << it->first << "," << endl;
                    vector<string> resu = it->second;
                    for(int i = 0 ;i < resu.size(); i++)
                        cout << resu[i] << endl;
                }
}

DefaultDict SequenceType::get_durations(){
    DefaultDict result;
    for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it) {
        result[it->first] = vector<int>();
        vector<string> resu = it->second;
        for(int i = 0 ;i < resu.size(); i++)
            result[it->first].push_back(resu[i].length());
    }
    return result;
}
