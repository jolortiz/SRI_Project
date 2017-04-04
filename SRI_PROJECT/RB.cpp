/*
 * main.cpp

 *
 *  Created on: Feb 20, 2017
 *      Author: psharma5
 */
#include "RB.h"
using namespace std;

//multimap<int, Node > rulemap;
//Operator overloading to print the multimap
inline ostream & operator << (ostream & os, const vector <string> &v){
  for(const auto & i : v){
    os << i <<" ";
  }
  cout<<endl;
  return os;
}

inline ostream & operator << (ostream & os , const multimap<int,Node > &m){
  for(const auto & i : m){
    //os << i.first << " : " << endl;
    os << "RULE ";
    os << i.second.info<<endl;
  }
  return os;
}

RB::RB() {
}

void RB::passString(string o_values){
  string_map.push_back(o_values);
  parse_string(o_values);
  v_parse_str.erase(v_parse_str.begin(), v_parse_str.end());
}
//Adds a rule to the main multimap shared by all objects
void RB::add_Rule(int o_key, Node &N, string temp_str) {
    if(status == -1) {
      cout<<"Error: Missing Operator in Rule"<<endl;
      cout<<"Unable to put values in map: "<<temp_str<<endl;

    }
    if(status == 1){
       /*for(int j=0; j<N.info.size(); j++){
             cout << N.info[j] << ", ";
       }
       cout <<endl;*/
       rulemap.insert(pair<int, Node >(o_key, N));
    } 
    
       /*cout << o_key << endl;
       for(int j=0; j<N.info.size(); j++){
             cout << N.info[j] << ", ";
        }*/
}

//Parses the string
void RB::parse_string(string values) {
  number_of_spaces = -1;
  saved_value = -1;
  found = false;
  key = 0;
  status = 1;
  string temp_str = values;
  for(int i = 0; i < temp_str.length(); i++) {
    if(temp_str[i] == ':') {found = true;}
    if(found && temp_str[i] == ')'){number_of_spaces++;}
    if(!found && temp_str[i] == '$') {key += 1;}
    if(temp_str[i] == '(' || temp_str[i] == ')' || temp_str[i] == ':'
    || temp_str[i] == '-' || temp_str[i] == ',' || temp_str[i] == ' ') {
       decode_rule(i, temp_str);
    }
  }
  vector<string> hisVec;
  hisVec = pop_elements(key, v_parse_str);
  //Store name Left most Predicate : Name of Rule e.g "Parent"
  Node temp(hisVec,v_parse_str[0]);
  add_Rule(key, temp, temp_str);
}
//Adds each word in the string to a specific index inside a vector
void RB::decode_rule(int i, string temp_str) {
    v_parse_str.push_back(temp_str.substr(saved_value+1, i-(saved_value+1)));
    saved_value = i;
}
//Deletes or pops unneccessary elements from the vector
vector <string> RB::pop_elements(int key, vector<string> v_parse_str) {
   v_parse_str.erase(remove(v_parse_str.begin(), v_parse_str.end(),""), v_parse_str.end());

   if(!(v_parse_str.at(1+key) == "OR" || v_parse_str.at(1+key) == "AND")) {
     status = -1;
   }
   if(v_parse_str.at(1+key) == "OR") {
          for(int s = 0; s < key; s++) {
            temp_vec.push_back(v_parse_str[s+1]);
          }
          for(int i = 0; i < key; i++) {
            v_parse_str.erase(v_parse_str.begin() + 1);
          }
          for(int q = 0; q < key; q++) {
            temp_vec_pred.push_back(v_parse_str[q+3]);
          }
          compare_vec(temp_vec, temp_vec_pred);
          temp_vec_pred.clear();
          for(int j = 0; j < key; j++) {
            v_parse_str.erase(v_parse_str.begin() + 3);
          }
          if(!check_res) {
            v_parse_str.erase(v_parse_str.begin()+2);
	    
          }
          int temp_num_of_spaces = number_of_spaces;
          while(temp_num_of_spaces != 0) {
            int counter_dup = 4;
	    if(!check_res) counter_dup = 3;
            for(int k = 0; k < key; k++) {
             temp_vec_pred.push_back(v_parse_str[counter_dup+k]);
            }
            temp_num_of_spaces--;
            compare_vec(temp_vec, temp_vec_pred);
            temp_vec_pred.clear();
          }
	      
          int pos = 1;
                while(number_of_spaces != 0) {
		  count_in_while++;
                  int counter = 3 + pos;
		  if(!check_res) {
		  counter = 3 + pos - wrong_params;	
		  }
                    for(int k = 0; k < key; k++) {
                      v_parse_str.erase(v_parse_str.begin() + counter);
                    }
                    pos++;
                    number_of_spaces--;
                 }
		for(int i = 0; i <v_parse_str.size(); i++) {
                  cout<<i<<": "<<v_parse_str[i]<<endl;
              }
    }
 
   else if(v_parse_str.at(1+key) == "AND"){
     for(int i = 0; i < key; i++){
        v_parse_str.erase(v_parse_str.begin() +1);
     }
    
   }

  //if(v_parse_str.at(key+1)

   //Print to Check values inside vector
   /*
   for(int k =0; k < v_parse_str.size(); k++) {
     cout<<k<<" "<<v_parse_str[k]<<endl;
   }
   */
   init_thread(key,v_parse_str);
   return v_parse_str;
}
//Prints the rulemap




void RB:: search_stringmap(string tmp2){
    for(int i = 0; i < string_map.size(); i++){
       string temp = string_map.at(i);
       for(int j = 0; j <temp.length(); j++){
          if(temp[j] == '('){
              string tmp = temp.substr(0,j);
             if(tmp == tmp2){
               string_map.erase(string_map.begin()+i);
               i = -1;
             }
             //cout<< temp.substr(0,j);
             //return tmp;
          }
      }
    }
}

void RB::compare_vec(vector<string> temp_vec, vector<string> temp_vec_pred) {
    for(int i = 0; i < temp_vec.size(); i++) {
      if(temp_vec[i] != temp_vec_pred[i]) {
          check_res = false;
          wrong_params++;
          result = i;
      }
   }
}


void RB:: print_values(ofstream &outputFile) {
    for(unsigned i =0; i < string_map.size();i++){
       outputFile<< "RULE "<< string_map.at(i) << endl;
    } 
    //outputFile << "Rule" + <<::rulemap;
    string_map.clear();
}
/*void RB:: print(RB &rb) {
    
    cout <<::rb.rulemap;
}*/

/*int main(){
 RB testobj;
    testobj.passString("Parent($X,$Y) :- OR Father($X,$Y) Mother($X,$Y)");
    testobj.print_values();
    //delete testobj;
return 0;
}*/
