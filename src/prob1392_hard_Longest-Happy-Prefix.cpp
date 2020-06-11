// prob1392: Longest Happy Prefix

/*
 *
 */


class Solution {
public:
    void getNext(string s, vector<int>& next) {
        int n = s.size();
        next[0] = 0;
        for (int q = 1, k = 0; q < n; ++q) {
            while (k > 0 && s[q] != s[k])
                k = next[k-1];
            if (s[q] == s[k]) k++;
            next[q] = k;
        }
    }

    string longestPrefix(string s) {
        int n = s.size();
        vector<int> next(n);
        getNext(s, next);
        return s.substr(0, next[n-1]);
    }
};
