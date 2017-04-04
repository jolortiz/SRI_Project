// Transactions CPP
#include "Transactions.h"
Transactions::Transactions(){
}   

//Loads Facts and Rules  into KB and RB
void Transactions::LOAD(RB &rb , KB &kb, string file_name){
  //lock<mutex> lock(mtx);
  Inference_parse parser2;
  ifstream input_file;
  string line_of_file;
  vector<string> file_input;
  size_t pos;
  string tmp;
  map<string, int> commands;
   commands["quit"] = 1;
   commands["clear"] = 2;
   commands["FACT"] = 3;
   commands["RULE"] = 4;
   commands["INFERENCE"] = 5;
   commands["DROP"] = 6;
   commands["DUMP"] = 7;
   commands["LOAD"] = 8;
  if(exists(file_name)){
    //File Found
    input_file.open(file_name);
    if(input_file.fail()){ cout << "Cannot Open File\n" << endl;}
    else{
      while(getline(input_file,line_of_file)){
        vector <string > params;
        string word;
        string name;
        istringstream iss(line_of_file);
        while(iss >> word) file_input.push_back(word);
        pos = line_of_file.find_first_of(" ");
        tmp = line_of_file.substr(pos+1);
        if(commands.find(file_input.at(0)) == commands.end()){cout << "Command Not Found - Transactions - Load -" << endl;/*Command Not Found*/}
        else{
          unsigned int size;
          vector<Node> myVec;
          vector<Node> myVec2;
          vector<string> :: iterator it;
          int n = commands[file_input.at(0)];
          //cout << n<< endl;
          switch(n){
            case 3 :
                   //cout << "FACT COMMAND\n";
                   kb.passString(tmp);
                   break;
            case 4 :
                   //cout << "Rule COMMAND\n";
                   rb.passString(tmp);
                   break;
            case 5 :
                   parser2.passString(tmp);
                   //cout << "Inference COMMAND\n";
                   params = parser2.get_Vector();
                   if(parser2.label == ""){/*cout<<"\nNo Label Exists"<<endl;*/}
                   if(parser2.label != ""){/*cout << "\nLabel : "<< parser2.label << endl;*/}
                   //for(int k = 0; k <params.size();k++){
                      //cout << k << " : " << params[k] <<endl;
                   //}
                   name = parser2.name;
                   size = params.size();

                   //fut = async(launch::async, &Transactions ::INFERENCE,this,ref(kb),ref(rb),name,  size,params);
                   //cout<< myVec.size();
                   myVec = fut.get();
                   for(int i=0; i<myVec.size(); i++){
                      for(int j=0; j<myVec[i].info.size(); j++){
                        cout << myVec[i].info[j] << ", ";
                      }
                   }cout <<endl;
                   /*for(int x =0; x<myVec2.size();x++){
                      for(int y = 0; y<myVec2[x].info.size(); y++){
                         cout << myVec2[x].info[y] << ", ";
                      }
                   }*/
                   break;
            case 6 :
                   //cout << "DROP Command\n";
                   DROP(tmp,rb,kb);
                   //cout << tmp<<endl;
                   break;
            case 7 :
                   //cout << "DUMP Command\n";
                   DUMP(rb,kb,tmp);
                   break;
            case 8 :
                   cout << "LOAD Command\n";
                   LOAD(rb,kb, tmp);
                   break;
          }
        }
       file_input.clear();
      }
    input_file.close(); 
    }
           
  }         
  else{
    cout << "File : " << file_name << "Does Not Exist\n" << endl;
  }
 
}

void Transactions :: DUMP(RB &rb, KB &kb, string file){
    ofstream file_name;
    file_name.open(file);
    rb.print_values(file_name);
    kb.print_values(file_name);
    file_name.close();
}

vector<Node> Transactions::INFERENCE(KB& kb, RB& rb, string s1, unsigned int params, 
        vector <string>& v){
    //init_thread(params,v);
    //lock_guard<mutex> block_threads_until_finish_this_job(mtx);
    std::vector<Node> temp;
    std::vector<Node> temp2;
    bool found;
    int newparam = 0;
    for (std::multimap<int, Node>::iterator it=rb.rulemap.begin(); 
            it!=rb.rulemap.end();++it){ //loops through map
       if(it->second.info[1] == "AND" && it->first == params && it->second.info[0] == s1){ //if right rule is found
            found = true;
            vector<Node> someVec;
            vector<Node> classyVec;
            vector<Node> toomuchVec;
            std::vector<string> strVec;
            int x=2;
            int counter = 3+params;
            for(int y=x+params+1; y<it->second.info.size(); y+=params+1){ //this will loop through the rule
                for(int j=0; j<v.size(); j++){ //pushes v into temporary strVec
                    strVec.push_back(v[j]);
                }
                if(x==2){ //return all facts if its the first fact/rule
                    someVec = INFERENCE(kb, rb, it->second.info[x], params, strVec);
                }else{
                    for(int p=0; p<toomuchVec.size(); p++){ //this is where its messing up
                        someVec.push_back(toomuchVec[p]);
                    }
                    toomuchVec.clear();
                }
                for(int j=y+1; j<y+1+params; j++){
                for(int i=x+1; i<x+1+params; i++){
                    if(it->second.info[i] == it->second.info[j]){ // j=7, i=5
                        for(int k=0; k<someVec.size(); k++){ //loops through somevec
                            strVec[j-y-1] = someVec[k].info[i-x];
                            classyVec = INFERENCE(kb, rb, it->second.info[y], params, strVec);
                        for(int j=0; j<classyVec.size(); j++){
                            toomuchVec.push_back(classyVec[j]);
                        }
                        classyVec.clear();
                        }
                    }
                }
                }
                someVec.clear();
                strVec.clear();
                x+=params+1;
            }
            return toomuchVec;
        }else{
        //newparam = params;
        if(it->first == params && it->second.info[0] == s1){ //if the right rule is found
            found = true;
            //vector< future < vector<Node> > > futures;
            for(int i = 2; i < it->second.info.size(); i++){
		temp = search_facts3(kb,rb,it->second.info[i], params, v);
                //cout<<"Launching Thread "<<i<<"ID: "<<this_thread::get_id()<<endl;
	    
            /*for(int i=0; i<futures.size(); i++){
                temp = futures.at(i).get();*/
                for(int j=0; j<temp.size(); j++){
                    temp2.push_back(temp[j]);
                }
                temp.clear();
		
            }
            
            /*for(int i=2; i<it->second.info.size(); i++){//loops through info
                temp = search_facts3(kb, rb, it->second.info[i], params, v);
                for(int j=0; j<temp.size(); j++){
                    temp2.push_back(temp[j]);
                }
                temp.clear();
            }*/
        }
        }
    }
    if(found == false){
        temp2 = search_facts3(kb, rb, s1, params, v);
    }
    
    return temp2;
}

/*vector<Node> Transactions :: myfunc(KB& kb, RB& rb, string s1, int params,vector <string> &v){
        vector <Node> temp;
	temp = search_facts3(kb,rb,s1,params,v);
        return temp;
}*/
vector<Node> Transactions::search_facts3(KB& kb, RB& rb, string s1, int params, vector <string>& v){ // father, 2
    std::vector<Node> temp;
    std::vector<Node> temp2;
    int flag = 0;
    for (std::multimap<int, Node>::iterator it=kb.factmap.begin(); 
            it!=kb.factmap.end();++it){ // puts all facts that align with s1 and params in temp vec
        if(it->first == params && it->second.info[0] == s1){ //checks type of fact and number of parameters
            flag++;
            temp.push_back(it->second); //pushes fact into temp vec
        }
    }
    bool myB;
    for(int j=0; j<temp.size(); j++){ //loops through temp vector
        int count = 0;
        for(int i=0; i<v.size(); i++){ //loops through parameter vector
            string str = v[i];
            if(str[0] == '$'){
                count++;
            }else{
                if(temp[j].info[i+1] == str){
                    myB = true;
                }else{
                    myB = false;
                }
            }
        }
        if(count == v.size()){ myB = true; }
        if(myB == true){ temp2.push_back(temp[j]); }
    }
    if(flag == 0){temp2 = INFERENCE(kb, rb, s1, params, v); }//return false;
    //mtx.unlock();*/
    return temp2;
}


void Transactions :: DROP(string s1, RB &rb, KB &kb){
     //Searches the KB and erases from map if finds match
     rb.search_stringmap(s1);
     kb.search_stringmap(s1);
     /*
     for(std::multimap<int, Node>::iterator it= kb.factmap.begin(); it != kb.factmap.end();){
        multimap <int,Node>:: iterator erase_it = it++;
        if(it->second.name == s1){
          cout << "found Fact"<<endl;
          cout << it->second.name << endl;
          kb.factmap.erase(erase_it);
        }
        
     }

     //Searches the RB and erases from map if finds match
     for(std::multimap<int, Node>::iterator it= rb.rulemap.begin(); it !=rb.rulemap.end();){
        multimap<int,Node> :: iterator erase_it = it++;
        if(it->second.name == s1){
          cout << "found Rule"<<endl;
          rb.rulemap.erase(erase_it);
        }
        
     }*/
}

/*int main(){
   KB kb;
   RB rb;
   Transactions test;
   test.LOAD(rb,kb,"input.sri");
   //cout <<"KB\n";
   //kb.print();
   //cout <<"RB\n";
   //rb.print();
   test.DUMP(rb,kb,"dump_test.sri");
   
 return 0;
}*/
