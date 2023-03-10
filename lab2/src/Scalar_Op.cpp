#include<vector>
#include "../include/scalar_head.h"
using namespace std;
vector<vector<int>> s_add(int a, vector<vector<int>> &m)
{
	vector<vector<int>> ans(m.size());
	for(int i=0; i < m.size(); i++)
	{
		for(int j=0; j< m[0].size();j++)
		{
			ans[i].push_back(m[i][j]+a);   
		}
	}
	return ans;
}

vector<vector<int>> s_sub(int a, vector<vector<int>> &m)
{
	vector<vector<int>> ans(m.size());
	for(int i=0; i < m.size(); i++)
	{
		for(int j=0; j< m[0].size();j++)
		{
			ans[i].push_back(m[i][j]-a);   
		}
	}
	return ans;
}

vector<vector<int>> s_mul(int a, vector<vector<int>> &m)
{
	vector<vector<int>> ans(m.size());
	for(int i=0; i < m.size(); i++)
	{
		for(int j=0; j< m[0].size();j++)
		{
			ans[i].push_back(m[i][j]*a);   
		}
	}
	return ans;
}

vector<vector<int>> s_div(int a, vector<vector<int>> &m)
{
	if(a == 0){
		log ("Can't be divisible by 0");
		return {};
	}
	vector<vector<int>> ans(m.size());
	for(int i=0; i < m.size(); i++)
	{
		for(int j=0; j< m[0].size(); j++)
		{
			ans[i].push_back(m[i][j]/a);   
		}
	}
	return ans;
}
