// week199-1

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        if(s.empty()) return "";
        int n = s.size();
        string result(n, ' ');
        for(int i = 0; i < n; ++i)
        {
            result[indices[i]] = s[i];
        }
        return result;
    }
};
