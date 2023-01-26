// prob1286: Iterator for Combination

/*
 * Design an Iterator class, which has:
 * A constructor that takes a string characters of sorted distinct lowercase English letters and a number combinationLength as arguments.
 * A function next() that returns the next combination of length combinationLength in lexicographical order.
 * A function hasNext() that returns True if and only if there exists a next combination.
 */

/*
 * Example:
 *
 * CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.
 *
 * iterator.next(); // returns "ab"
 * iterator.hasNext(); // returns true
 * iterator.next(); // returns "ac"
 * iterator.hasNext(); // returns true
 * iterator.next(); // returns "bc"
 * iterator.hasNext(); // returns false
 */

/*
 * Constraints:
 *
 * 1 <= combinationLength <= characters.length <= 15
 * There will be at most 10^4 function calls per test.
 * It's guaranteed that all calls of the function next are valid.
 */

#include <string>
#include <stack>
#include <vector>

using namespace std;

class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength):characters(characters),combinationLength(combinationLength)
    {
        n = characters.size();
        vec = vector<string>();
        string item = "";
        dfs(0, item, 0, vec);
        N = vec.size();
        iter = 0;
    }

    string next() {
        return vec[iter++];
    }

    bool hasNext() {
        return iter < N;
    }

private:
    string characters;
    vector<string> vec;
    int combinationLength;
    int n;
    int N;
    int iter;

    void dfs(int pos, string& item, int len, vector<string>& vec)
    {
        if(len == combinationLength)
        {
            vec.push_back(item);
            return;
        }

        for(int i = pos; i + (combinationLength - len) <= n; ++i)
        {
            item += characters[i];
            dfs(i + 1, item, len + 1, vec);
            item.pop_back();
        }
    }
};
