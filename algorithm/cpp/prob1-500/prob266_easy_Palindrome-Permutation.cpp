// prob266: Palindrome Permutation

/*
 * Given a string, determine if a permutation of the string could form a palindrome.
 */

/*
 * Example 1:
 * Input: "code"
 * Output: false
 * Example 2:
 * Input: "aab"
 * Output: true
 * Example 3:
 * Input: "carerac"
 * Output: true
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// vector
class Solution {
public:
    bool canPermutePalindrome(string s) {
        if(s.empty()) return false;
        int n = s.size();
        if(n == 1) return true;

        vector<int> mapping(1000, 0);
        int m = mapping.size();
        for(char c: s)
        {
            if((int)c >= m)
            {
                vector<int> tmp(c - m + 1, 0);
                mapping.insert(mapping.end(), tmp.begin(), tmp.end());
            }
            ++mapping[(int)c];
        }
        int num_odd = 0;
        for(int i = 0; i < m; ++i)
        {
            if(mapping[i] & 1)
                ++num_odd;
            if(num_odd > 1)
                return false;
        }
        return true;
    }
};

// unordered_map
class Solution_2 {
public:
    bool canPermutePalindrome(string s) {
        if(s.empty()) return false;
        int n = s.size();
        if(n == 1) return true;

        unordered_map<char, int> mapping;
        for(char c: s)
        {
            if(mapping.find(c) != mapping.end())
                ++mapping[c];
            else
                mapping[c] = 1;
        }

        int num_odd = 0;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            if(it -> second & 1)
                ++num_odd;
            if(num_odd > 1)
                return false;
        }
        return true;
    }
};
