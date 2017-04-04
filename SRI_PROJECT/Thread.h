#ifndef THREAD_H
#define THREAD_H

#include "includes.h"

class Thread
{

protected:
	    vector<string> sv;
			vector<future<string>> futures;
public:
			 Thread() {}
			~Thread() {};
		  void init_thread(int key, vector<string> v_parse_str);
			static string Myfunction(string temp_str, int i);
			void retrieve_values();

};

#endif // THREAD_H

