// Prob970 Powerful Integers

/*
 * Given two non-negative integers x and y, an integer is powerful if it is equal to x^i + y^j for some integers i >= 0 and j >= 0.
 * Return a list of all powerful integers that have value less than or equal to bound.
 * You may return the answer in any order. In your answer, each value should occur at most once.
 */

/*
 * Example 1:
 * Input: x = 2, y = 3, bound = 10
 * Output: [2,3,4,5,7,9,10]
 * Explanation:
 * 2 = 2^0 + 3^0
 * 3 = 2^1 + 3^0
 * 4 = 2^0 + 3^1
 * 5 = 2^1 + 3^1
 * 7 = 2^2 + 3^1
 * 9 = 2^3 + 3^0
 * 10 = 2^0 + 3^2
 *
 * Example 2:
 * Input: x = 3, y = 5, bound = 15
 * Output: [2,4,6,8,10,14]
 */

/*
 * Note:
 * 1 <= x <= 100
 * 1 <= y <= 100
 * 0 <= bound <= 10^6
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        vector<int> x_list = get_power_list(x, bound);
        vector<int> y_list = get_power_list(y, bound);
        vector<int> result;
        int nx = x_list.size();
        int ny = y_list.size();
        unordered_set<int> s;
        for(int i = 0; i < nx; ++i)
        {
            for(int j = 0; j < ny; ++j)
            {
                int sum = x_list[i] + y_list[j];
                if(sum > bound)
                    break;
                else
                {
                    if(s.find(sum) == s.end())
                    {
                        s.insert(sum);
                        result.push_back(sum);
                    }
                }
            }
        }
        return result;
    }

private:
    vector<int> get_power_list(int x, int bound)
    {
        // return the list of x^i which is less than round
        if(x == 1)
            return vector<int>(1, 1);
        vector<int> result;
        int i = 0;
        int power = pow(x, i);
        while(power < bound)
        {
            result.push_back(power);
            ++i;
            power = pow(x, i);
        }
        return result;
    }
};


int main()
{
    int x;
    int y;
    int bound;
    cout << "input x: " << endl;
    cin >> x;
    cout << "input y: " << endl;
    cin >> y;
    cout << "input bound: " << endl;
    cin >> bound;
    Solution solution;
    vector<int> result;
    result = solution.powerfulIntegers(x, y, bound);
    for(vector<int>::iterator iter = result.begin(); iter != result.end(); ++iter)
    {
        cout << *iter << ", ";
    }
    cout << endl;
}

