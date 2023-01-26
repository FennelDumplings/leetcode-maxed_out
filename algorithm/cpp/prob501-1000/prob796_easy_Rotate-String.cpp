// prob796: Rotate String

/*
 * https://leetcode-cn.com/problems/rotate-string/
 */

#include <string>

using namespace std;

class Solution {
public:
    bool rotateString(string A, string B) {
        return A.size() == B.size() && match(A + A, B);
    }

private:
    bool match(string s, string p)
    {
        return s.find(p) != string::npos;
    }
};
