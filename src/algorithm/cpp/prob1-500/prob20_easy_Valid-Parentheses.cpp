// Prob20: Valid Parentheses

/*Description
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * An input string is valid if:
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 *
 * Note that an empty string is also considered valid.
*/

/*Example:
 * Example 1:
 * Input: "()"
 * Output: true
 *
 * Example 2:
 * Input: "()[]{}"
 * Output: true
 *
 * Example 3:
 * Input: "(]"
 * Output: false
 *
 * Example 4:
 * Input: "([)]"
 * Output: false
 *
 * Example 5:
 * Input: "{[]}"
 * Output: true
 */

#include <stack>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if(s.empty()) return true;
        stack<char> st;
        for(char ch : s)
        {
            if(left_set.find(ch) != left_set.npos)
                st.push(ch);
            else
            {
                if(st.empty()) return false;
                char st_top = st.top();
                if(paren_match(st_top, ch))
                    st.pop();
                else
                    return false;
            }
        }
        if(st.empty())
            return true;
        else
            return false;
    }

private:
    string left_set = "([{";
    string right_set = ")]}";

    bool paren_match(char st_top, char ch)
    {
        if(st_top == '(' && ch == ')') return true;
        if(st_top == '[' && ch == ']') return true;
        if(st_top == '{' && ch == '}') return true;
        return false;
    }
};
