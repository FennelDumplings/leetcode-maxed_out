// Prob984: string-without-aaa-or-bbb

/*
 * Given two integers A and B, return any string S such that:
 *
 * S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
 * The substring 'aaa' does not occur in S;
 * The substring 'bbb' does not occur in S.
*/

/*
 * Note:
 * 0 <= A <= 100
 * 0 <= B <= 100
 * It is guaranteed such an S exists for the given A and B.
*/

#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    string strWithout3a3b(int A, int B)
    {
        string result = "";
        int delta = A - B;
        if(delta == 0)
        {
            // A == B
            for(int i = 0; i < (A + B) / 2; ++i)
                result += "ab";
        }
        else if(delta > 0)
        {
            // A > B
            int num_aa = delta - 1;
            if(num_aa > B)
            {
                for(int i = 0; i < B; ++i)
                    result += "aab";
                result += "aa";
            }
            else
            {
                for(int i = 0; i < num_aa; ++i)
                    result += "aab";
                for(int i = 0; i < B - num_aa; ++i)
                    result += "ab";
                result += "a";
            }
        }
        else
        {
            // A < B
            int num_bb = - delta - 1;
            if(num_bb > A)
            {
                for(int i = 0; i < A; ++i)
                    result += "bba";
                result += "bb";
            }
            else
            {
                for(int i = 0; i < num_bb; ++i)
                    result += "bba";
                for(int i = 0; i < A - num_bb; ++i)
                    result += "ba";
                result += "b";
            }
        }
        return result;
    }
};


int main()
{
    Solution solution;
    int A;
    cout << "input A" << endl;
    cin >> A;
    int B;
    cout << "input B" << endl;
    cin >> B;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    string result = solution.strWithout3a3b(A, B);
    cout << result << endl;
}
