#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        unordered_map<string, int> mapping;
        mapping["c"] = 0;
        mapping["cr"] = 0;
        mapping["cro"] = 0;
        mapping["croa"] = 0;
        int n = croakOfFrogs.size();
        int cnt = 0;
        int max_cnt = 0;
        for(char ch: croakOfFrogs)
        {
            if(ch == 'c')
            {
                mapping["c"] += 1;
                max_cnt = max(max_cnt, mapping["c"]);
            }
            else if(ch == 'r')
            {
                mapping["cr"] += 1;
                if(mapping["cr"] > mapping["c"])
                    return -1;
            }
            else if(ch == 'o')
            {
                mapping["cro"] += 1;
                if(mapping["cro"] > mapping["cr"])
                    return -1;
            }
            else if(ch == 'a')
            {
                mapping["croa"] += 1;
                if(mapping["croa"] > mapping["cro"])
                    return -1;
            }
            else
            {
                if(mapping["croa"] == 0)
                    return -1;
                cnt++;
                mapping["croa"]--;
                mapping["cro"]--;
                mapping["cr"]--;
                mapping["c"]--;
            }
        }
        if(cnt * 5 < n)
            return -1;
        return max_cnt;
    }
};
