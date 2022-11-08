#include <string>

using namespace std;

class Solution {
public:
    string interpret(string command) {
        int n = command.size();
        int i = 0;
        string ans;
        while(i < n)
        {
            if(command[i] == 'G')
            {
                ans += 'G';
                ++i;
            }
            else if(command[i] == '(')
            {
                ++i;
                if(command[i] == ')')
                {
                    ans += 'o';
                    ++i;
                }
                else
                {
                    ans += "al";
                    i += 3;
                }
            }
        }
        return ans;
    }
};
