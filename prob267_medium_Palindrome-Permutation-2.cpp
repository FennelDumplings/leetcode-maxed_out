// prob 267: Palindrome Permutation II

/*
 * Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.
 */

/*
 * Example 1:
 * Input: "aabb"
 * Output: ["abba", "baab"]
 * Example 2:
 * Input: "abc"
 * Output: []
 */

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

// 在DFS中传递哈希表，调通的版本
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        if(s.empty()) return vector<string>();
        int n = s.size();
        if(n == 1) return vector<string>({s});

        unordered_map<char, int> mapping;
        for(char c: s)
        {
            if(mapping.find(c) != mapping.end())
                ++mapping[c];
            else
                mapping[c] = 1;
        }

        int num_odd = 0;
        char odd_char = ' ';
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            if(it -> second & 1)
            {
                ++num_odd;
                if(num_odd > 1)
                    return vector<string>();
                odd_char = it -> first;
                it -> second /= 2;
            }
            else
                it -> second /= 2;
        }

        if(mapping[odd_char] == 0)
                mapping.erase(mapping.find(odd_char));

        vector<string> results;
        string result_item;
        unordered_map<char, int> visited = mapping;
        dfs(mapping, result_item, results, odd_char, num_odd == 1, visited);
        return results;
    }

private:
    void dfs(unordered_map<char, int>& mapping, string& result_item, vector<string>& results,
            char odd_char, bool odd, unordered_map<char, int>& visited)
    {
        // 用 empty 做退出判断不推荐
        if(visited.empty())
        {
            string result_item_reverse = result_item;
            reverse(result_item_reverse.begin(), result_item_reverse.end());
            // 下面四行可以合为一行表达式
            if(odd)
                results.push_back(result_item + odd_char + result_item_reverse);
            else
                results.push_back(result_item + result_item_reverse);
            return;
        }

        for(auto it = mapping.begin(); it != mapping.end(); ++it) // 自带了去重
        {
            // 当前选 it
            char cur_char = it -> first;
            if(visited.find(cur_char) == visited.end()) continue;
            if(visited[cur_char] > 1)
                --visited[cur_char];
            else
                visited.erase(visited.find(cur_char));
            result_item.push_back(cur_char);
            dfs(mapping, result_item, results, odd_char, odd, visited);
            result_item.pop_back();
            if(visited.find(cur_char) != visited.end())
                ++visited[cur_char];
            else
                visited[cur_char] = 1;
        }
    }
};

// 哈希表作为dfs的原始数据
// 以遍历过的元素个数为退出条件
class Solution_2 {
public:
    void dfs(map<char, int> counts, int i, int K, string odds, string& s, vector<string>& res) {
        if (i == K) {
            string t = s;
            reverse(t.begin(), t.end());
            t += odds + s;
            res.push_back(t);
            return;
        }
        for (auto& p : counts) {
            if (p.second == 0) continue;
            --p.second;
            s += p.first;
            dfs(counts, i + 1, K, odds, s, res);
            s.pop_back();
            ++p.second;
        }
    }
    vector<string> generatePalindromes(string s) {
        if (s.size() < 2) return {s};
        int N = s.size();
        map<char, int> counts;
        for (auto c : s) ++counts[c];
        string odds;
        for (auto& p : counts) {
            if (p.second & 1) {
                odds += p.first;
            }
        }
        if ((odds.size() > 1 && (N & 1)) || (odds.size() > 0 && !(N & 1))) {
            return {};
        }
        int K = 0;
        for (auto& p : counts) {
            p.second >>= 1;
            K += p.second;
        }
        string t;
        vector<string> res;
        dfs(counts, 0, K, odds, t, res);
        return res;
    }
};
