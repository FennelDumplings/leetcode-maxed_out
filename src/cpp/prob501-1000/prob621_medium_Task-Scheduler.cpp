// prob621: Task Scheduler

/*
 * https://leetcode-cn.com/problems/task-scheduler/
 */

#include <vector>
#include <queue>
#include <string>

using namespace std;

class Solution_2 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> char_cnts(26);
        for(const char &ch: tasks)
            ++char_cnts[ch - 'A'];
        using PIC = pair<int, char>;
        priority_queue<PIC> pq;
        for(char ch = 'A'; ch <= 'Z'; ++ch)
            if(char_cnts[ch - 'A'] > 0)
                pq.push(PIC(char_cnts[ch - 'A'], ch));

        // 更新答案
        vector<PIC> buffer;
        int ans = 0;
        while(!pq.empty())
        {
            // 不断从堆顶取元素，直至堆空或者已经取满 n + 1 个
            buffer.clear();
            for(int j = 0; j < n + 1 && !pq.empty(); ++j)
            {
                PIC cur = pq.top();
                pq.pop();
                buffer.push_back(cur);
            }
            int num_char = buffer.size();
            for(PIC &item: buffer)
            {
                --item.first;
                if(item.first > 0)
                    pq.push(item);
            }
            if(pq.empty())
                ans += num_char;
            else
                ans += n + 1;
        }
        return ans;
    }
};

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> char_cnts(26);
        for(const char &ch: tasks)
            ++char_cnts[ch - 'A'];

        using PIC = pair<int, char>;
        priority_queue<PIC> pq;
        for(char ch = 'A'; ch <= 'Z'; ++ch)
            if(char_cnts[ch - 'A'] > 0)
                pq.push(PIC(char_cnts[ch - 'A'], ch));

        int max_val = pq.top().first - 1;
        int idle = max_val * (n + 1);

        while(!pq.empty())
        {
            PIC cur = pq.top();
            pq.pop();
            idle -= min(cur.first, max_val);
        }
        int ans = tasks.size();
        if(idle > 0)
            ans += idle;
        return ans;
    }
};
