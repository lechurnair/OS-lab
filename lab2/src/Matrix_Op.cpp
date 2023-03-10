using namespace std;
#include "../include/matrix_head.h"
vector<vector<int>> m_add(vector<vector<int>> &m1, vector<vector<int>> &m2)
{
	if((m1.size() != m2.size()) || (m1[0].size() != m2[0].size())){
		log ("Matrices are not of same dimansion");
		return {};
	}
	vector<vector<int>> ans(m1.size());
	for(int i=0; i < m1.size(); i++)
	{
		for(int j=0; j< m1[0].size(); j++)
		{
			ans[i].push_back(m1[i][j]+m2[i][j]);   
		}
	}
	return ans;
}
vector<vector<int>> m_sub(vector<vector<int>> &m1, vector<vector<int>> &m2)
{
	if((m1.size() != m2.size()) || (m1[0].size() != m2[0].size())){
		log ("Matrices are not of same dimansion");
		return {};
	}
	vector<vector<int>> ans(m1.size());
	for(int i=0; i < m1.size(); i++)
	{
		for( int j=0; j< m1[0].size();j++)
		{
			ans[i].push_back(m1[i][j]-m2[i][j]);   
		}
	}
	return ans;
}

vector<vector<int>> m_mul(vector<vector<int>> &m1, vector<vector<int>> &m2)
{
	if((m1[0].size() !=  m2.size())){
		log ("No. of rows of first matrix is not equal to no. of columns of other matrix");
		return {};
	}
	vector<vector<int>> ans(m1.size());
	int a;
	for(int i = 0; i < m1.size(); i++)
	{	
		for(int j = 0 ; j < m1[0].size(); j++)
		{
			a = 0;
			for(int k = 0; k < m1[0].size(); k++)
			{
				a += m1[i][k] * m2[k][j];
			}
			ans[i].push_back(a);
		}
	}
	return ans;
}

vector<vector<int>> m_trans(vector<vector<int>> &m)
{
	vector<vector<int>> ans(m[0].size());
	for(int i = 0; i < m[0].size(); i++)
	{
		for(int j = 0; j < m.size(); j++)
		{
			ans[i].push_back(m[j][i]);   
		}
	}
	return ans;
}

int m_deter(vector<vector<int>> &m, int n) 
{
	if(m.size() != m[0].size()){
		log ("Matrix is not a square matrix");
		return INT_MIN;
	}
	int det = 0;
	vector<vector<int>> submatrix(m.size(),vector<int>(m[0].size(),0));
	if(n == 1) return m[0][0];
	if (n == 2) return ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
	else 
	{
		for (int k = 0; k < n; k++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == k) continue;
					submatrix[subi][subj] = m[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, k) * m[0][k] * m_deter( submatrix, n - 1 ));
		}
	}
	return det;
}
