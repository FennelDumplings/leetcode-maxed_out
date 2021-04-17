// prob843: Guess the Word

/*
 * This problem is an interactive problem new to the LeetCode platform.
 * We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.
 * You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the
 * original list with 6 lowercase letters.
 * This function returns an integer type, representing the number of exact matches (value and position) of your
 * guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.
 * For each test case, you have 10 guesses to guess the word. At the end of any number of calls,
 * if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.
 * Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list. 
 * The letters of each word in those testcases were chosen independently at random from 'a' to 'z',
 * such that every word in the given word lists is unique.
 */

/*
 * Example 1:
 * Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]
 * Explanation:
 * master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
 * master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
 * master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
 * master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
 * master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
 * We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
 */

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Master {
  public:
    int guess(string word);
};

class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int n = wordlist.size();
        vector<bool> visited(n, false);
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            int res = master.guess(wordlist[i]);
            if(res == 6) return;
            visited[i] = true;
            _check(wordlist, wordlist[i], res, visited);
        }
    }

private:
    void _check(const vector<string>& wordList, const string& cur, int res, vector<bool>& visited)
    {
        int n = wordList.size();
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            int same_char = _same_char(cur, wordList[i]);
            if(same_char != res)
                visited[i] = true;
        }
    }

    int _same_char(const string& s1, const string& s2)
    {
        int result = 0;
        for(int i = 0; i < 6; ++i)
        {
            if(s1[i] == s2[i])
                ++result;
        }
        return result;
    }
};

// 与 Solution 过程基本相同
//
class Solution_2 {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int N = wordlist.size();
        vector<vector<int> > sim(N, vector<int>(N, 0)); // sim[i][j] 是两个词之间匹配的字母数
        for (int i = 0; i < N; ++i) {
            sim[i][i] = 6;
            for (int j = i + 1; j < N; ++j) {
                sim[i][j] = sim[j][i] = _calSim(wordlist[i], wordlist[j]);
            }
        }
        vector<bool> candidates(N, true);
        while (true) {
            int i = findNext(sim, candidates);
            int s = master.guess(wordlist[i]);
            if (s == 6) return;
            for (int j = 0; j < N; ++j) {
                if (candidates[j] && sim[j][i] != s) {
                    candidates[j] = false;
                }
            }
        }
    }

private:
    int _calSim(const string& s1, const string& s2) {
        int res = 0;
        for (int i = 0; i < 6; ++i) {
            res += s1[i] == s2[i];
        }
        return res;
    }

    int findNext(const vector<vector<int> >& sim, const vector<bool>& candidates) {
        int N = candidates.size();
        int mn = INT_MAX;
        int mn_ind = -1;
        for (int i = 0; i < N; ++i) {
            if (!candidates[i]) continue;
            vector<int> counts(6, 0);
            for (int j = 0; j < N; ++j) {
                if (j == i || !candidates[j]) continue;
                ++counts[sim[i][j]];
            }
            int mx = *max_element(counts.begin(), counts.end());
            if (mx < mn) {
                mn = mx;
                mn_ind = i;
            }
        }
        return mn_ind;
    }
};
