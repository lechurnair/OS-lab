#include "../include/scalar_head.h"
#include "../include/matrix_head.h"
#include<bits/stdc++.h>
using namespace std;

void log(string s){
	ofstream fp;
	fp.open("logger.txt",  ofstream::app);
	time_t Time;
	tm * TM;
	char tr[100];
	time(&Time);
	TM = localtime(&Time);
	strftime(tr, 50, "%F.%T", TM);
	fp << tr << "    " << s << endl;
	fp.close();
}
