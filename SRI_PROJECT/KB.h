#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include<algorithm>
#include "Node.h"

using namespace std;

class KB : public virtual Node {
    private:
        int key = 0;
        string values;
    public:
        KB();
        ~KB() {}
        void add_Fact(int o_key, Node &N);
        void parse_string(string values);
        void decode_Fact(int i, string temp_str);
        void print_values(ofstream &outputFile);
        //void print(KB &kb);
        void passString(string o_values);
	 void search_stringmap(string tmp2);
        vector<string> v_parse_str;
        int saved_value = -1;
        multimap< int, Node > factmap;
	vector <string> stringmap;

};

