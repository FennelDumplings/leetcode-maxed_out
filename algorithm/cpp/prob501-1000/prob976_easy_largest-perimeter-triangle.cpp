// Prob976 Largest Perimeter Triangle

/*
 * Given an array A of positive lengths, return the largest perimeter of a triangle
 * with non-zero area, formed from 3 of these lengths.

 * If it is impossible to form any triangle of non-zero area, return 0.
 */

/*
 * Example 1:
 * Input: [2,1,2]
 * Output: 5
 *
 * Example 2:
 * Input: [1,2,1]
 * Output: 0
 *
 * Example 3:
 * Input: [3,2,3,4]
 * Output: 10
 *
 * Example 4:
 * Input: [3,6,2,3]
 * Output: 8
 */

/*
 * 3 <= A.length <= 10000
 * 1 <= A[i] <= 10^6
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        sort(A.begin(), A.end(), greater<int>());
        int n = A.size();
        for(int i = 0; i < n - 2; ++i)
        {
            if(A[i + 1] + A[i + 2] > A[i])
                return A[i + 1] + A[i + 2] + A[i];
        }
        return 0;
    }
};


int main()
{
    int n;
    cout << "input n: ";
    cin >> n;
    cout<< "input n numbers: " << endl;
    vector<int> vec(n, 0);
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
    }
    for(int i = 0; i < n; ++i)
    {
        cout << vec[i] << ", ";
    }
    cout << endl;
    Solution solution;
    int result = solution.largestPerimeter(vec);
    cout << result << endl;
}
