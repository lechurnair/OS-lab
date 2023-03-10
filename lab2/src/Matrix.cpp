#include "../include/matrix_head.h"
#include "../include/scalar_head.h"
#include "../include/inp.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv){
	vector<int> scalar;
	vector<vector<vector<int>>> m;
	taking_input(m, scalar);
	int i = 1;
	string st;
	while((i < argc) && (m.size() != 0)){
		st = argv[i];
		i++;
		if(st == "-a"){
			if(scalar.empty()) break;
			m[0] = s_add (scalar[0], m[0]);
			scalar.erase(scalar.begin());
		}
		else if(st == "-s"){
			if(scalar.empty()) break;
			m[0] = s_sub (scalar[0], m[0]);
			scalar.erase(scalar.begin());
		}
		else if(st == "-m"){
			if(scalar.empty()) break;
			m[0] = s_mul (scalar[0], m[0]);
			scalar.erase(scalar.begin());
		}
		else if(st == "-d"){
			if(scalar.empty()) break;
			m[0] = s_div (scalar[0], m[0]);
			scalar.erase(scalar.begin());
			if(m[0].size() == 0) m.erase(m.begin());
		}
		else if(st == "-A"){
			if(m.size() < 2) break;
			m[1] = m_add (m[0], m[1]);
			m.erase(m.begin());
			if(m[0].size() == 0) m.erase(m.begin());
		}
		else if(st == "-S"){
			if(m.size() < 2) break;
			m[1] = m_sub (m[0], m[1]);
			m.erase(m.begin());
			if(m[0].size() == 0) m.erase(m.begin());
		}
		else if(st == "-M"){
			if(m.size() < 2) break;
			m[1] = m_mul (m[0], m[1]);
			m.erase(m.begin());
			if(m[0].size() == 0) m.erase(m.begin());
		}
		else if(st == "-T"){
			m[0] = m_trans (m[0]);
		}
		else if(st == "-X"){
			int ans = m_deter (m[0], m[0].size());
			m.erase(m.begin());
			if(ans != INT_MIN) scalar.insert(scalar.begin(), ans);
			if((i == argc) && (ans != INT_MIN)){
				cout << ans << endl;
				exit(0);
			}
		}
		else{
			log("Invalid Operation");
			exit(0);
		}
	}
	if(m.size()){
		cout << m[0].size() << " " << m[0][0].size() << endl;
		for (int i = 0; i < m[0].size(); i++)
		{
			for (int j = 0; j < m[0][i].size(); j++)
			{
				cout << m[0][i][j] << ",";
			}
			cout << endl;
		}
	}
}
