#include "../include/inp.h"
#include <bits/stdc++.h>
using namespace std;
void taking_input(vector<vector<vector<int>>> &m, vector<int> &scalar){
	int in = 0, in_matrix = 0, num;
	string s = "";
	
	while(!cin.eof()){
		getline(cin, s);
		if((s[0] == '#') || (s.size() == 0));
		else{
			in++;
			vector <int> tokens;
			stringstream check1(s);
			string inte;
			while(getline(check1, inte, ' '))
			{
				stringstream geek(inte);
				geek >> num;
				tokens.push_back(num);
			}
			if(tokens.size() == 1){
				scalar.push_back(tokens[0]);
			}
			else if(tokens.size() == 2){
				vector<vector<int>> m1;
				for(int i = 0; i < tokens[0]; i++){
					in_matrix = 1;
					getline(cin, s);
					vector <int> token;
					stringstream check1(s);
					while(getline(check1, inte, ','))
					{
						stringstream geek(inte);
						geek >> num;
						token.push_back(num);
					}
					
					m1.push_back(token);
				}
				m.push_back(m1);
			}
		}
	}
}
