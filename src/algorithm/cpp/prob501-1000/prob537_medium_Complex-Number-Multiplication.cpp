// prob537: Complex Number Multiplication

/*
 * https://leetcode-cn.com/problems/complex-number-multiplication/
 */

#include <string>
#include <sstream>
#include <complex>

using namespace std;

class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        int ra, ia;
        get(a, ra, ia);
        int rb, ib;
        get(b, rb, ib);
        complex<int> c1(ra, ia);
        complex<int> c2(rb, ib);
        complex<int> ans = c1 * c2;
        string result = to_string(ans.real()) + '+' + to_string(ans.imag()) + 'i';
        return result;
    }

private:
    void get(const string& a, int& ra, int& ia)
    {
        int n = a.size();
        int i = 0;
        while(i < n && a[i] != '+')
            ++i;
        stringstream ss;
        ss << a.substr(0, i);
        ss >> ra;
        ++i;
        ss.clear();
        ss << a.substr(i);
        ss >> ia;
    }
};
