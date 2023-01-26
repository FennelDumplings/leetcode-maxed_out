// prob1324: Print Words Vertically

/*
 * Given a string s. Return all the words vertically in the same order in which they appear in s.
 * Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
 * Each word would be put on only one column and that in one column there will be only one word.
 */

/*
 * Example 1:
 * Input: s = "HOW ARE YOU"
 * Output: ["HAY","ORO","WEU"]
 * Explanation: Each word is printed vertically.
 *  "HAY"
 *  "ORO"
 *  "WEU"
 * Example 2:
 * Input: s = "TO BE OR NOT TO BE"
 * Output: ["TBONTB","OEROOE","   T"]
 * Explanation: Trailing spaces is not allowed.
 * "TBONTB"
 * "OEROOE"
 * "   T"
 * Example 3:
 * Input: s = "CONTEST IS COMING"
 * Output: ["CIC","OSO","N M","T I","E N","S G","T"]
 */

/*
 * Constraints:
 * 1 <= s.length <= 200
 * s contains only upper case English letters.
 * It's guaranteed that there is only one space between 2 words.
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> printVertically(string s) {
        if(s.empty()) return vector<string>();
        vector<vector<int> > intervals;
        s.push_back(' ');
        int N = s.size();
        int i = 0;
        while(i < N && s[i] == ' ')
            ++i;
        if(i == N) return vector<string>();
        int n = 0;
        while(i < N)
        {
            int j = i;
            while(j < N && s[j] != ' ')
                ++j;
            intervals.push_back(vector<int>({i, j}));
            n = max(n, j - i);
            if(j == N) break;
            i = j + 1;
        }
        int m = intervals.size();
        // 输出 n 行，每行 m 个
        vector<string> result(n);
        i = 0;
        for(int j = 0; j < n; ++j)
        {
            for(int k = 0; k < m; ++k)
            {
                result[j].push_back(s[intervals[k][0]]);
                if(intervals[k][0] != intervals[k][1])
                    ++intervals[k][0];
            }
            while(result[j][m - 1] == ' ')
            {
                result[j].pop_back();
                --m;
            }
        }
        s.pop_back();
        return result;
    }
};

// 借助 stringstream
class Solution_2 {
public:
    vector<string> printVertically(string s) {
        stringstream in(s);
        vector<string> words;
        string _word;
        int maxlen = 0;
        while (in >> _word) {
            words.push_back(_word);
            maxlen = max(maxlen, (int)_word.size());
        }
        vector<string> ans;
        for (int i = 0; i < maxlen; ++i) {
            string concat;
            for (string& word: words) {
                concat += (i < (int)word.size() ? word[i] : ' ');
            }
            while (concat.back() == ' ') {
                concat.pop_back();
            }
            ans.push_back(move(concat));
        }
        return ans;
    }
};
