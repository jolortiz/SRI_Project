#include "Thread.h"

mutex mtx;
void Thread::init_thread(int key, vector<string> v_parse_str) {
	for(int i = 2; i < v_parse_str.size(); i++) {
		 string temp = v_parse_str[i];
		 sv.push_back(temp);
	}
	for(int i = 0; i < sv.size(); i++) {
		futures.push_back(async(launch::async, Myfunction,sv[i], i));
	}
	retrieve_values();
 }

string Thread::Myfunction(string temp, int i) {
	mtx.lock();
	cout<<"Thread Index: "<<i<<": "<<this_thread::get_id()<<endl;
	return temp;
}

void Thread::retrieve_values() {
 for(int i = 0; i < futures.size(); i++) {
		auto x = futures.at(i).get();
		cout<<x<<endl;
		mtx.unlock();
	}
}

