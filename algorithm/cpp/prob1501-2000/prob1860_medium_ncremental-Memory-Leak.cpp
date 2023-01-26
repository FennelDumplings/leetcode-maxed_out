
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> memLeak(int memory1, int memory2) {
        int i = 1;
        while(true)
        {
            if(i > memory1 && i > memory2)
                return vector<int>{i, memory1, memory2};
            if(i > memory1)
                memory2 -= i;
            else if(i > memory2)
                memory1 -= i;
            else
            {
                if(memory1 >= memory2)
                    memory1 -= i;
                else
                    memory2 -= i;
            }
            ++i;
        }
    }
};
