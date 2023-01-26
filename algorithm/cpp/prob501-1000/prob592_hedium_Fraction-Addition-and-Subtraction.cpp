// prob592: Fraction Addition and Subtraction

/*
 * https://leetcode-cn.com/problems/fraction-addition-and-subtraction/
 */

#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

class Solution {
public:
    string fractionAddition(string expression) {
        if(expression.empty()) return "";
        vector<int> A, B;
        if(expression[0] != '-')
            expression = '+' + expression;
        int n = expression.size();
        int i = 0;
        while(i < n)
        {
            int j = i;
            while(j < n && expression[j] != '/')
                ++j;
            stringstream ss;
            int a;
            ss << expression.substr(i , j - i);
            ss >> a;
            A.push_back(a);
            i = j + 1;
            j = i;
            while(j < n && expression[j] >= '0' && expression[j] <= '9')
                ++j;
            ss.clear();
            ss << expression.substr(i, j - i);
            int b;
            ss >> b;
            B.push_back(b);
            i = j;
        }
        int m = B.size();
        int b = 1;
        int a = 0;
        for(int i = 0; i < m; ++i)
            b = lcm<int>(b, B[i]);
        for(int i = 0; i < m; ++i)
            a += A[i] * b / B[i];
        int t = gcd<int>(a, b);
        a /= t;
        b /= t;
        string result;
        result += to_string(a) + '/' + to_string(b);
        return result;
    }
};
