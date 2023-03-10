#ifndef MATRIX_HEAD_H_ // #include guards
#define MATRIX_HEAD_H_ 
#include <vector>
#include <limits.h>
#include<math.h>
#include <string>
std::vector<std::vector<int>> m_add(std::vector<std::vector<int>> &m1, std::vector<std::vector<int>> &m2);
int m_deter(std::vector<std::vector<int>> &m, int n) ;
std::vector<std::vector<int>> m_trans(std::vector<std::vector<int>> &m);
std::vector<std::vector<int>> m_mul(std::vector<std::vector<int>> &m1, std::vector<std::vector<int>> &m2);
std::vector<std::vector<int>> m_sub(std::vector<std::vector<int>> &m1, std::vector<std::vector<int>> &m2);
void log(std::string s);
#endif // MYCLASS_H_  _
