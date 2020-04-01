// prob1002: Find Common Characters

/*
 * Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings
 * within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times,
 * you need to include that character three times in the final answer.
 * You may return the answer in any order.
 */

/*
 * Example 1:
 * Input: ["bella","label","roller"]
 * Output: ["e","l","l"]
 * Example 2:
 * Input: ["cool","lock","cook"]
 * Output: ["c","o"]
 */

/*
 * Note:
 * 1 <= A.length <= 100
 * 1 <= A[i].length <= 100
 * A[i][j] is a lowercase letter
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        if(A.empty()) return vector<string>();
        int n = A.size();
        vector<vector<int> > char_cnts(26, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            for(char c: A[i])
                ++char_cnts[c - 'a'][i];
        }
        vector<string> result;
        for(int i = 0; i < 26; ++i)
        {
            int cnt = *min_element(char_cnts[i].begin(), char_cnts[i].end());
            vector<string> item(cnt, string(1, 'a' + i));
            result.insert(result.end(), item.begin(), item.end());
        }
        return result;
    }
};
