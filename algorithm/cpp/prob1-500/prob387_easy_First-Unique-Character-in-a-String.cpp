// prob387: First Unique Character in a String

/*
 * Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.
 */

/*
 * Note: You may assume the string contain only lowercase letters.
 */

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        if(s.empty()) return -1;
        int n = s.size();
        if(n == 1) return 0;
        vector<int> mapping(26, -2); // char -> idx
        for(int i = 0; i < n; ++i)
        {
            int cur = s[i] - 'a';
            if(mapping[cur] >= 0)
                mapping[cur] = -1;
            else if(mapping[cur] == -2)
                mapping[cur] = i;
        }
        int result = n;

        for(int i = 0; i < 26; ++i)
        {
            if(mapping[i] >= 0)
                result = min(result, mapping[i]);
        }
        if(result == n) return -1;
        return result;
    }
};

// 120ms
class Solution_2 {
public:
    int firstUniqChar(string s) {
        if(s.empty()) return -1;
        int n = s.size();
        if(n == 1) return 0;
        unordered_map<int, int> mapping; // char -> idx
        for(int i = 0; i < n; ++i)
        {
            if(mapping.find(s[i]) != mapping.end())
                mapping[s[i]] = -1;
            else
                mapping[s[i]] = i;
        }
        int result = n;

        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            if(it -> second != -1)
                result = min(result, it -> second);
        }
        if(result == n) return -1;
        return result;
    }
};
