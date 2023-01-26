// interview16.01: Swap Numbers LCCI

/*
 * Write a function to swap a number in place (that is, without temporary vari­ ables).
 */

/*
 * Example:
 * Input: numbers = [1,2]
 * Output: [2,1]
 */

/*
 * Note:
 * numbers.length == 2
 */

#include <vector>

using namespace std;

// 无溢出风险
class Solution {
public:
    vector<int> swapNumbers(vector<int>& numbers) {
        numbers[0] = numbers[0] ^ numbers[1];
        numbers[1] = numbers[0] ^ numbers[1];
        numbers[0] = numbers[0] ^ numbers[1];
        return numbers;
    }
};

// 有溢出风险高
class Solution_2 {
public:
    vector<int> swapNumbers(vector<int>& numbers) {
        numbers[0] = numbers[0] + numbers[1];
        numbers[1] = numbers[0] - numbers[1];
        numbers[0] = numbers[0] - numbers[1];
        return numbers;
    }
};
