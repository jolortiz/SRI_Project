// Transaction Header
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "common.h"
#include "RB.h"
#include "KB.h"
#include "Thread.h"
#include "Inference_parse.h"
#include "boost/filesystem.hpp"
#include <boost/filesystem.hpp>


using namespace std;
using namespace boost :: filesystem;

class Transactions:public RB, public KB{
protected :
	future < vector < Node > > fut;
public:
    Transactions();
    void LOAD(RB &rb , KB &kb, string file_name);
    vector<Node> INFERENCE(KB& kb, RB& rb, string s1, unsigned int params, vector<string>& v);
    vector<Node> search_facts3(KB& kb, RB& rb, string s1, int params, vector <string>& v);
    //changed to static
//static vector<Node> myfunc(KB& kb, RB& rb, string s1, int params,vector <string> &v);
    void DUMP(RB &rb, KB &kb, string file_name);
    void DROP(string s1, RB &rb, KB &kb);
    //void INFERENCE2(KB& kb, string s1, int params);
};

#endif /* TRANSACTIONS_H */

