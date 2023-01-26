
//
//  main.cpp
//  homework3
//
//  Created by Gülşah Önen on 3.05.2021.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <map> // will be used count the word
#include <iomanip>
#include "HashTable.h"
using namespace std;

struct vec
{
  string name;
  double sup_value;
//  double con_value;
};


// rule of the hash table
int hashed(const vec & key, const int tableSize )
{
    int hashVal = 0;
    for( char ch : key.name )
        hashVal += ch;
    return (hashVal % tableSize);
}
// if have at least one same element
// eliminate like {a,b}-> {a}
bool isHave(string name1, string name2){
    vector<string> name;
    string names = name1 + "," +name2;
    
    stringstream ss(names);
    while( ss.good()){
        string substr;
        getline( ss, substr, ',' );
        name.push_back( substr );
    }
    // Put all array elements in a map
    unordered_set<string> s;
    for (int i = 0; i < name.size(); i++) {
        s.insert(name[i]);
    }
      
    // If all elements are distinct, size of
    // set should be same array.
    return !(s.size() == name.size());
}
// line contains temp or not
// line = a b c d temp = a b c --> true
bool isContains(string name1, string name2){
    vector<string> name;
    vector<string> name2_vec;

    string names = name1 + "," +name2;
    
    stringstream ss(names);
    while( ss.good()){
        string substr;
        getline( ss, substr, ',' );
        name.push_back( substr );
    }
    stringstream sss(name2);
    while( sss.good()){
        string substr;
        getline( sss, substr, ',' );
        name2_vec.push_back( substr );
    }
    unordered_set<string> s;
    for (int i = 0; i < name.size(); i++) {
        s.insert(name[i]);
    }
      
   return !(s.size() == (name.size() - name2_vec.size()));
}
// string 1 = a b c string 2 = b c a --> true
bool isMixedContains(string name1, string name2){
    vector<string> name;
    string names = name1 + "," +name2;
    
    stringstream ss(names);
    while( ss.good()){
        string substr;
        getline( ss, substr, ',' );
        name.push_back( substr );
    }
    // Put all array elements in a map
    unordered_set<string> s;
    for (int i = 0; i < name.size(); i++) {
        s.insert(name[i]);
    }
      
    // If all elements are distinct, size of
    // set should be same array.
    if(s.size()*2 == name.size())
        return true;
    else
        return  false;
}
template <class KTy, class Ty>

//insert hash one name and their support
// insert ve
void PrintMap(map<KTy,Ty> map, string filename, double sup_thres, vector<vec> &vector, HashTable<vec>&table, double &lineCount)
{
    ifstream input;
    string line;
    input.open(filename.c_str());
    if(input.fail()){
        cout << "file cannot opened!" << endl;
    }
    else{
        while(getline(input,line)){     // linecount
            lineCount++;
    }
    }
    typedef typename std ::map<KTy,Ty>::iterator iterator;
    for (iterator p = map.begin(); p != map.end(); p++){
        // take bigger or equal support threshold
        if(p->second/lineCount >= sup_thres){
           vec subject;
           subject.name = p->first;
           subject.sup_value =  p->second/lineCount;
           vector.push_back(subject);
           table.insert(subject);
        }
        }
    input.close();
    input.clear();
    input.seekg(0);
    }

// find how many each word occurance in a file

void SupportOneShow(string filename, double sup_thres, vector <vec> & vector,HashTable<vec> &table, double &lineCount){
    map<string, double> showsCount;

    ifstream input;
    string show;

    input.open(filename.c_str());
    if(input.fail()){
        cout << "file cannot opened!" << endl;
    }
    else{
        
        while(input >> show){
         
            if (showsCount.find(show) == showsCount.end()){
                showsCount[show] = 1;
            }
            else{
                showsCount[show]++;
            }
        }
    }

    input.close();
    input.clear();
    input.seekg(0);
    // send name and occurance number
    PrintMap(showsCount,filename,sup_thres,vector,table, lineCount);
    // names and support value which bigger or equal support threshold
}
// find two pair
void FindPair( vector<vec> &vector, ::vector<vec> &pair_vector, double &lineCount,string filename, double sup_thres,HashTable<vec> &table){
    ifstream input;
    string line;
    vec pair_subject;
    for(int i=0; i< vector.size(); i++){
        for(int j=i+1; j< vector.size(); j++){
            string pair_one = vector[i].name;
            string pair_second = vector[j].name;
            string pair_name= pair_one + "," + pair_second;
    
            pair_subject.name = pair_name;
            pair_vector.push_back(pair_subject);
    }}
    
    ::vector <string> vecline;    // for each line create  vecline
    input.open(filename.c_str());
    while(getline(input,line)){
        string name;
        istringstream iss(line);
    
        while(iss >> name){
            vecline.push_back(name);
        }
            for(int i=0; i < pair_vector.size(); i++){
                for(int j=0; j < vecline.size(); j ++){
                    unsigned long int pos = pair_vector[i].name.find(",");
                    
                    if(pair_vector[i].name.substr(0,pos) == vecline[j]){
                        for(int z=j+1 ; z< vecline.size(); z++){
                           if( pair_vector[i].name.substr(pos+1) == vecline[z]){
                               pair_vector[i].sup_value++;
                            }
                        }
                    }
                    else if(pair_vector[i].name.substr(pos+1) == vecline[j]){
                        for(int z=j+1 ; z< vecline.size(); z++){
                           if( pair_vector[i].name.substr(0,pos) == vecline[z]){
                               pair_vector[i].sup_value++;
                           }
                        }
                    }
                }
            }
        vecline.clear();
    }
   for(int i=0; i < pair_vector.size(); i++){
       if(pair_vector[i].sup_value == 0){
           pair_vector[i].sup_value = 0;
       }
       else{
          pair_vector[i].sup_value =  (pair_vector[i].sup_value/lineCount);
       }
        if(pair_vector[i].sup_value >= sup_thres){
           // cout <<  pair_vector[i].name << "--"<<  pair_vector[i].sup_value <<  endl;
            vec subject_pair;
            subject_pair.name = pair_vector[i].name ;
            subject_pair.sup_value =  pair_vector[i].sup_value;
            vector.push_back(subject_pair);
          //  pair_table.insert(subject_pair);
            table.insert(subject_pair);
        }
    }

    input.close();
   
}
// find pair bigger tahn two
void allPair(vector<vec> &vector, ::vector<vec> &pair_vector, string filename, double lineCount){
    ::vector<vec> temp;
    ifstream input;
    string line;
    string line_name;
    vec subject;
    for(int i=0; i< vector.size(); i++){
        for(int j = i+1; j< vector.size(); j++){
            int posi = vector[i].name.find(",");
            int posj = vector[j].name.find(",");
            if((posi != -1 || posj != -1) && !isHave(vector[i].name, vector[j].name)){
                string name = vector[i].name + "," + vector[j].name;
                
                subject.name = name;
                subject.sup_value = 0;
                temp.push_back(subject);
            }
        }
    }
   
    string str_line;
    ::vector <string> vecline;
    input.open(filename.c_str());
    // count how many lines include pairs
    while(getline(input,line)){
        string name;
        str_line="";
        istringstream iss(line);
        while(iss >> name){
            str_line += name + ",";
        }
        str_line = str_line.substr(0,str_line.length()-1);
        for(int i=0; i <temp.size(); i++){
            if (!isContains(str_line,temp[i].name)){
             temp[i].sup_value ++;
            }
            /*else{
                temp[i].sup_value = 0;  // that was a huge bug for me :)
            }*/
        }
    }
    for(int i=0; i < temp.size(); i++){
        subject.name= temp[i].name;
        subject.sup_value = (temp[i].sup_value / lineCount);
        pair_vector.push_back(subject);
    }
}

double confidenceCalculator(string name1,string name2, vector<vec> pair_vector){
    ::vector<string> pair_name;
    string names = name1 +"," +name2;
    for(int i=0; i< pair_vector.size(); i++){
        
   /*     if(pair_vector[i].name == names){
          //  cout << pair_vector[i].sup_value << endl;
            return pair_vector[i].sup_value;
            
        }*/
        if(isMixedContains(pair_vector[i].name, names)){
          return pair_vector[i].sup_value;
    }}
    return 0.0;
}
// create confidence pair
void FindConfidence(vector<vec> &vector, ::vector<vec> &pair_vector, double con_thres){
    int count=0;
    ofstream myfile;
    myfile.open ("result.txt");
  
    for(int i=0; i<vector.size(); i++){
        for(int j=i+1 ; j<vector.size(); j++){
            
           if(!isHave(vector[i].name , vector[j].name)){
                double con1 = (confidenceCalculator(vector[i].name,vector[j].name, pair_vector)/vector[i].sup_value);
                double con2 = (confidenceCalculator(vector[i].name,vector[j].name, pair_vector)/vector[j].sup_value);
              
                if(con1 >= con_thres){
                   myfile << vector[i].name << ";" << vector[j].name << ";" << fixed << setprecision(2) << con1 <<  endl;
                   count++;}
                if(con2 >= con_thres){
                   myfile << vector[j].name << ";" << vector[i].name << ";" << fixed << setprecision(2) << con2 << endl;
                   count++;}
            }
        }
    }
   
    if(count > 0){
        cout << count << " rules are written to results.txt" << endl;
    }
    else{
        cout << "There is no rule for the given support and confidence values." << endl;
        }
    myfile.close();
}

// main
int main() {
    string filename;
    ifstream input;
    int size= 11;
    double lineCount=0.0;
    vec i;
    HashTable<vec> table(i,size);
    HashTable<vec> pair_table(i,size);
    vector<vec> pair_vector;
    vector <vec> vector;
    ::vector <vec> other_pair_vector;
    double sup_thres, con_thres ;

   
    cout << "Please enter the transaction file name: " ;
    cin >> filename;
  
    cout << "Please enter support and confidence values between 0 and 1: " ;
    cin >> sup_thres >> con_thres;
  
    SupportOneShow(filename,sup_thres, vector, table,lineCount);
    
    FindPair(vector, pair_vector,lineCount,filename,sup_thres,table);
    
    allPair(vector,pair_vector, filename, lineCount);

    FindConfidence( vector, pair_vector,con_thres);
    
    return 0;


}
