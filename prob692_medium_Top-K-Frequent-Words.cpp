// prob692: Top K Frequent Words

/*
 * Given a non-empty list of words, return the k most frequent elements.
 * Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency,
 * then the word with the lower alphabetical order comes first.
 */

/*
 * Example 1:
 * Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
 * Output: ["i", "love"]
 * Explanation: "i" and "love" are the two most frequent words.
 *     Note that "i" comes before "love" due to a lower alphabetical order.
 * Example 2:
 * Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
 * Output: ["the", "is", "sunny", "day"]
 * Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
 *     with the number of occurrence being 4, 3, 2 and 1 respectively.
 */

/*
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 * Input words contain only lowercase letters.
 */

/*
 * Follow up:
 * Try to solve it in O(n log k) time and O(n) extra space.
 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

// 哈希表 + 堆
using PIS = pair<int, string>; // 频数，词
bool operator<(const PIS& pis1, const PIS& pis2)
{
    if(pis1.first == pis2.first)
        return pis1.second > pis2.second;
    return pis1.first < pis2.first;
}

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        if(words.empty()) return vector<string>();
        int n = words.size();
        unordered_map<string, int> word_cnt;
        for(int i = 0; i < n; ++i)
            ++word_cnt[words[i]];
        int N = word_cnt.size(); // 单词个数
        priority_queue<PIS, vector<PIS>, Greater> pq; // 小根
        auto it = word_cnt.begin();
        for(int i = 0; i < k; ++it, ++i)
            pq.push(PIS(it -> second, it -> first));
        for(int i = k; i < N; ++it, ++i)
        {
            PIS cur(it -> second, it -> first);
            if(pq.top() < cur)
            {
                pq.pop();
                pq.push(cur);
            }
        }
        vector<string> result(k, "");
        for(int i = k - 1; i >= 0; --i)
        {
            result[i] = pq.top().second;
            pq.pop();
        }
        return result;
    }

private:
    struct Greater {
        bool operator() (const PIS& pis1, const PIS& pis2)
        {
            if(pis1.first == pis2.first)
                return pis1.second < pis2.second;
            return pis1.first > pis2.first;
        }
    };
};

// 哈希表 + 桶排序
class Solution_2 {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        if(words.empty()) return vector<string>();
        int n = words.size();
        unordered_map<string, int> word_cnt;
        for(int i = 0; i < n; ++i)
            ++word_cnt[words[i]];
        int N = word_cnt.size(); // 单词个数
        vector<vector<string> > buckets(N + 1, vector<string>());
        for(auto& item : word_cnt)
            buckets[item.second].push_back(item.first);
        vector<string> result;
        for(int i = N; i >= 0; --i)
        {
            if(!buckets[i].empty())
            {
                sort(buckets[i].begin(), buckets[i].end());
                for(int j = 0; j < (int)buckets[i].size(); ++j)
                {
                    result.push_back(buckets[i][j]);
                    --k;
                    if(k == 0)
                        return result;
                }
            }
        }
        return result;
    }
};
