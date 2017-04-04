//-----------------------------------------------------------------------------
//  CLI_Module.cpp
//  A Command Line client for the SRI Engine.
//  author: djespera
//
//-----------------------------------------------------------------------------
#include "common.h"
#include "boost/filesystem.hpp"
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "Transactions.h"
using namespace std;
using namespace boost :: filesystem;
map<string, int> commands;
vector<string> file_input;
ifstream infile;
string line;
string tmp;
string label;
RB rb;
KB kb;
Transactions action;
Inference_parse parser;
size_t pos;
int main(int argc, char* argv[])
{
   commands["quit"] = 1;
   commands["clear"] = 2;
   commands["FACT"] = 3;
   commands["RULE"] = 4;
   commands["INFERENCE"] = 5;
   commands["DROP"] = 6;
   commands["DUMP"] = 7;
   commands["LOAD"] = 8;
   //If the user has a file to load
   //int Session
   if(argc == 2){
     //cout<< "LOAD will be called on File\n";
      //cout << argv[1];
     //If cannot open File
     if(infile.fail()){
       cout << "CLI Error : Cannot open File\n";
       exit(1);
     }
     else{
        string file = argv[1];
        action.LOAD(rb,kb,file);
     }
    }     
   cout<< "\n***SRI Interface***\n";
   cout<<"Enter quit to Terminate Program\n";
   while(1)
   {
     string input;
     cout<<"CLI> ";
     getline(cin, input);
     vector<string> parsed_input;
     vector<string> params;
     string word;
     string name;
     istringstream iss(input);
     while( iss >> word) parsed_input.push_back(word);
       pos = input.find_first_of(" ");
       tmp  = input.substr(pos+1);
     if(input.empty()){//Do Nothing
     }else if(commands.find(parsed_input.at(0)) == commands.end()){
          //not 
           cout<<"CLI: "<<input<<" : Command Not Found"<<endl;
     }else{   
       int i = commands[parsed_input.at(0)];
       parser.passString(tmp);
       int size;
       //cout << parser.v_parse_str[0]<< endl;
       vector<Node> myVec;
       switch(i){
          case 1 :
             //Quit
             cout<<"Exiting Program\n"<<endl;
             exit(1);
          case 2 :
             //CLEAR
             system("clear");
             break;
          case 3 :
             //FACT
             kb.passString(tmp);
             //kb.print();
             break;
          case 4 :
             //RULE
             rb.passString(tmp);
             //rb.print();
             break;
          case 5 :
             //INFERENCE
             params = parser.get_Vector();
             size = params.size();
             if(parser.label == ""){/*cout<<"No Label Exists"<<endl;*/}
             if(parser.label != ""){/*cout << "Label : "<< parser.label << endl;*/}
             for(int k = 0; k <params.size();k++){
                cout << k << " : " << params[k] <<endl;
             }
             name = parser.name;
             cout << size << endl;
             
             myVec = action.INFERENCE(kb,rb,name,size,params);
              for(int i=0; i<myVec.size(); i++){
                for(int j=0; j<myVec[i].info.size(); j++){
                   cout << myVec[i].info[j] << ", ";
                }
              }
             //cout << endl;
             //cout << "Name of Fact : "<< name << endl;
             break;
          case 6 :
             //DROP
             action.DROP(tmp, rb,kb);
             break;
          case 7 :
              //DUMP
              action.DUMP(rb,kb,tmp);
             break;
          case 8 :
             //LOAD
             action.LOAD(rb,kb,tmp);
             break;
       }
     }
   }
} 


