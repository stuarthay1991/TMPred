//
//  SequenceHelp.cpp
//  TMPred
//
//  Created by Thanmai on 24/04/16.
//  Copyright © 2016 None. All rights reserved.
//

#include "SequenceHelp.hpp"
#include <numeric>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

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


Normalization::Normalization(DefaultDict distance){
    this->distances = distance;
}

double calculate_mean(vector<int> v){
    double sum = accumulate(v.begin(), v.end(), 0.0);
    return (float)sum/v.size();
}

double calculate_std(vector<int> v, double mean){
    double sq_sum = inner_product(v.begin(), v.end(), v.begin(), 0.0);
    return sqrt(sq_sum/ v.size() - mean * mean);
}

vector<double> math_norm(int max,double mean,double std){
    vector<double> result= vector<double>();
    for (int i=0; i < max; i++) {
        double y = (i-mean)/std;
        double x = pow(y, 2)/2.0;
        double numer = exp(-x);
        double denom = sqrt(M_PI * 2.0);
        result.push_back(numer/denom);
    }
    return result;
}

void Normalization::verification_norm(){
    for(int i=0; i < this->normalized_distances.size(); i++){
        vector<double> row = this->normalized_distances[i];
        double sum = accumulate(row.begin(), row.end(), 0.0);
        
        for(int j = 0; j < row.size(); j++){
            if( sum != 0){
                this->normalized_distances[i][j] /= (double)sum;
            }
        }
    }
}

array_2d Normalization::get_normalised_distance(){
    int max = 0;
    for(DefaultDict::iterator it = this->distances.begin(); it != this->distances.end(); ++it){
        int temp = * max_element(it->second.begin(), it->second.end());
        if (temp > max){
            max = temp;
        }
    }
    array_2d norm_array(3);
    for(int i=0; i < 3; i++)
        norm_array[i].resize(max,0);
    this->normalized_distances = norm_array;
    int j = 0;
    for(char i: "iMo"){
        if(i == '\0')
            continue;
        double mean = calculate_mean(this->distances[i]);
        double std = calculate_std(this->distances[i],mean);
        this->normalized_distances[j] = math_norm(max, mean, std);
        j++;
    }
    
    this->verification_norm();
    return this->normalized_distances;
}

void SequenceType::display_blah(){
    for(MapList::iterator it = this->sequence_lists.begin(); it != this->sequence_lists.end(); ++it) {
                    cout << it->first << "," << endl;
                    vector<string> resu = it->second;
                    for(int i = 0 ;i < resu.size(); i++)
                        cout << resu[i] << endl;
                }
}






