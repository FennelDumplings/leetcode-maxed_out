#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeMessage(string key, string message) {
        vector<char> mapping(26, '#');
        char i = 'a';
        for(const char &ch: key)
        {
            if(ch == ' ')
                continue;
            if(mapping[ch - 'a'] != '#')
                continue;
            mapping[ch - 'a'] = i++;
        }
        string result = message;
        int n = result.size();
        for(int i = 0; i < n; ++i)
        {
            if(message[i] == ' ')
                continue;
            result[i] = mapping[message[i] - 'a'];
        }
        return result;
    }
};

