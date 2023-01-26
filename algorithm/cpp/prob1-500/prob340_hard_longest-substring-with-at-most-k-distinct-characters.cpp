// prob340: longest-substring-with-at-most-k-distinct-characters

/*
 * Given a string, find the length of the longest substring T that contains at most k distinct characters.
 */

/*
 * Example 1:
 * Input: s = "eceba", k = 2
 * Output: 3
 * Explanation: T is "ece" which its length is 3.
 * Example 2:
 * Input: s = "aa", k = 1
 * Output: 2
 * Explanation: T is "aa" which its length is 2.
 */

#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache() {}

    int size() {
        return linkedlist.size();
    }

    int get(char key) {
        auto it = mapping.find(key);
        if(it == mapping.end())
            return -1;
        else
            return (it -> second).first;
    }

    void put(char key, int index) {
        auto it = mapping.find(key);
        if(it != mapping.end())
            remove(key);
        linkedlist.push_front(key);
        mapping.insert(pair<char, pair<int, list<char>::iterator>>(key, pair<int, list<char>::iterator>(index, linkedlist.begin())));
    }

    void remove(char key) {
        auto it = mapping.find(key);
        if(it != mapping.end())
        {
            auto iter = (it -> second).second;
            linkedlist.erase(iter);
            mapping.erase(it);
        }
    }

    int remove_bottom()
    {
        char key = linkedlist.back();
        int index = mapping[key].first;
        mapping.erase(mapping.find(key));
        linkedlist.pop_back();
        return index;
    }

private:
    unordered_map<char, pair<int, list<char>::iterator>> mapping;
    list<char> linkedlist;
};

// 滑动窗口 + 有序字典
// 使用有序字典代替标准哈希表解决方法：
//   如果字符串为空或者 k 是零的话返回 0。
//   设置指针为字符串开头 left = 0 和 right = 0，初始化最大子串长度 max_len = 1。
//   当 right 指针小于 N 时：
//     如果当前字符 s[right] 已经在有序字典中 hashmap 中，删除它，以保证 hashmap 的第一个元素是滑动窗口的最左侧元素。
//     将 s[right] 加入有序字典，并右移 right 指针。
//     如果有序字典 hashmap 包含 k + 1 个不同字符，在哈希表中移去最左出现的字符，移动 left 指针使得滑动窗口只包含 k 个不同字符。
//     更新 max_len。
// 最坏 O(N) 但实际跑的结果是 60ms
class Solution_2 {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(s.empty() || k == 0) return 0;
        int n = s.size();

        int left = 0, right = 0;
        LRUCache mapping;
        int result = 1;
        while(right < n)
        {
            mapping.put(s[right], right);
            ++right;
            if(mapping.size() == k + 1)
                left = mapping.remove_bottom() + 1;
            result = max(result, right - left);
        }
        return result;
    }
};

// 滑动窗口 + 哈希表 最坏O(Nk)
// 30ms
class Solution_3 {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(s.empty() || k == 0) return 0;
        int n = s.size();
        unordered_map<char, int> mapping;
        int left = 0, right = 0;
        int ans = 0;
        while(right < n)
        {
            while(right < n)
            {
                if(mapping.count(s[right]) == 0 && (int)mapping.size() == k)
                    break;
                if(mapping.count(s[right]) == 0)
                    mapping[s[right]] = 1;
                else
                    ++mapping[s[right]];
                ++right;
            }
            ans = max(ans, right - left);
            while((int)mapping.size() == k)
            {
                --mapping[s[left]];
                if(mapping[s[left]] == 0)
                    mapping.erase(s[left]);
                ++left;
            }
        }
        return ans;
    }
};
