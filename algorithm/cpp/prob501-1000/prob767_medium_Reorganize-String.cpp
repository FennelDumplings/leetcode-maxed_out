// prob767: Reorganize String

/*
 * https://leetcode-cn.com/problems/reorganize-string/
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    string reorganizeString(string S) {
        vector<int> char_cnts(26);
        for(const char &ch: S)
            ++char_cnts[ch - 'a'];

        using PIC = pair<int, char>;
        priority_queue<PIC> pq;
        for(char ch = 'a'; ch <= 'z'; ++ch)
            if(char_cnts[ch - 'a'] > 0)
                pq.push(PIC(char_cnts[ch - 'a'], ch));

        string result;
        while(!pq.empty())
        {
            PIC buf1 = pq.top();
            pq.pop();
            result += buf1.second;
            --buf1.first;
            if(pq.empty() && buf1.first > 0)
                return "";
            if(!pq.empty())
            {
                PIC buf2 = pq.top();
                pq.pop();
                result += buf2.second;
                --buf2.first;
                if(buf2.first > 0)
                    pq.push(buf2);
            }
            if(buf1.first > 0)
                pq.push(buf1);
        }
        return result;
    }
};
