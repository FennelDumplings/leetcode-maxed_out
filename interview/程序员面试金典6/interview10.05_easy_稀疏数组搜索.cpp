// interview10.05: 稀疏数组搜索

/*
 * https://leetcode-cn.com/problems/sparse-array-search-lcci/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int findString(vector<string>& words, string s) {
        if(words.empty()) return -1;
        int n = words.size();
        int left = 0, right = n - 1;
        return find(words, s, left, right);
    }

private:
    int find(const vector<string>& words, const string& s, int left, int right)
    {
        while(left <= right)
        {
            if(words[left] == s)
                return left;
            int mid = (left + right) / 2;
            if(!words[mid].empty())
            {
                if(words[mid] < s)
                    left = mid + 1;
                else if(words[mid] > s)
                    right = mid - 1;
                else
                    right = mid;
            }
            else
            {
                int l = find(words, s, left, mid - 1);
                if(l != -1)
                    return l;
                int r = find(words, s, mid + 1, right);
                return r;
            }
        }
        return -1;
    }
};


class Solution_2 {
public:
    int findString(vector<string>& words, string s) {
        if(words.empty()) return -1;
        int n = words.size();
        int left = 0, right = n - 1;
        return find(words, s, left, right);
    }

private:
    int find(const vector<string>& words, const string& s, int left, int right)
    {
        if(left > right)
            return -1;
        if(words[left] == s)
            return left;
        int mid = (left + right) / 2;
        if(!words[mid].empty())
        {
            if(words[mid] < s)
                return find(words, s, mid + 1, right);
            else if(words[mid] > s)
                return find(words, s, left, mid - 1);
            else
                return find(words, s, left, mid);
        }
        int l = find(words, s, left, mid - 1);
        if(l != -1)
            return l;
        int r = find(words, s, mid + 1, right);
        return r;
    }
};

