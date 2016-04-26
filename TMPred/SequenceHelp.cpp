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


void display_transition(Map result){
    for (Map::iterator it=result.begin(); it!=result.end(); ++it)
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
        // Working on probability calculation.
//        for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it){
//            string key = it->first;
//            if(key[0] == state)
//                total_trans += this->transition_matrix[key];
//        }
//        
//        for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it){
//            string key = it->first;
//            if(key[0] == state)
//                this->transition_matrix[key] = this->transition_matrix[key] / (float) total_trans;
//        }
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
    
    this->calculateProbability();
    
    // To Display result in the format of annotation: corresponding amino acids.
    //        for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it) {
    //            cout << it->first << "," << endl;
    //            vector<string> resu = it->second;
    //            for(int i = 0 ;i < resu.size(); i++)
    //                cout << resu[i] << endl;
    //        }
}

void SequenceType::display_blah(){
    for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it) {
                    cout << it->first << "," << endl;
                    vector<string> resu = it->second;
                    for(int i = 0 ;i < resu.size(); i++)
                        cout << resu[i] << endl;
                }
}




