#include <vector>
#include <string>

using namespace std;

// G()(al)

class Solution {
public:
    string interpret(string command) {
        int n = command.size();
        string result;
        int i = 0;
        while(i < n)
        {
            if(command[i] == 'G')
            {
                result += "G";
                i += 1;
            }
            else
            {
                ++i;
                if(command[i] == 'a')
                {
                    result += "al";
                    i += 3;
                }
                else
                {
                    result += "o";
                    i += 1;
                }
            }
        }
        return result;
    }
};
