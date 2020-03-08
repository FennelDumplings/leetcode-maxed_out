// prob636: Exclusive Time of Functions

/*
 * On a single threaded CPU, we execute some functions.  Each function has a unique id between 0 and N-1.
 * We store logs in timestamp order that describe when a function is entered or exited.
 * Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".
 * For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.
 * "1:end:2" means the function with id 1 ended at the end of timestamp 2.
 * A function's exclusive time is the number of units of time spent in this function.
 * Note that this does not include any recursive calls to child functions.
 * The CPU is single threaded which means that only one function is being executed at a given time unit.
 * Return the exclusive time of each function, sorted by their function id.
 */

/*
 * Input:
 * n = 2
 * logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
 * Output: [3, 4]
 * Explanation:
 * Function 0 starts at the beginning of time 0, then it executes 2 units of time and reaches the end of time 1.
 * Now function 1 starts at the beginning of time 2, executes 4 units of time and ends at time 5.
 * Function 0 is running again at the beginning of time 6, and also ends at the end of time 6, thus executing for 1 unit of time.
 * So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
 */

#include <stack>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        if(logs.empty()) return result;
        stack<pair<int, int> > st;
        for(string record: logs)
        {
            int timestamp, func_id;
            bool is_start;
            _parse_record(record, func_id, timestamp, is_start);
            if(is_start)
                st.push(pair<int, int>(timestamp, 0));
            else
            {
                pair<int, int> top_cur = st.top();
                st.pop();
                int timedelta = timestamp - top_cur.first + 1;
                if(!st.empty())
                {
                    pair<int, int> top_prev = st.top();
                    st.pop();
                    top_prev.second += timedelta;
                    st.push(top_prev);
                }
                timedelta -= top_cur.second;
                result[func_id] += timedelta;
            }
        }
        return result;
    }

private:
    void _parse_record(const string& record, int& func_id, int& timestamp, bool& is_start)
    {
        string func_id_str, timestamp_str;
        int n = record.size();
        int i = 0;
        while(i < n && record[i] != ':')
            ++i;
        func_id_str = record.substr(0, i);
        ++i;
        if(record[i] == 's')
            is_start = true;
        else
            is_start = false;
        while(i < n && record[i] != ':')
            ++i;
        timestamp_str = record.substr(i + 1, n - 1 - i);
        stringstream ss;
        ss << func_id_str;
        ss >> func_id;
        ss.clear();
        ss << timestamp_str;
        ss >> timestamp;
    }
};
