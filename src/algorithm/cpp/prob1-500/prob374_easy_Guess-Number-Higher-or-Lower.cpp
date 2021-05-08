// prob374: Guess Number Higher or Lower

/*
 * We are playing the Guess Game. The game is as follows:
 * I pick a number from 1 to n. You have to guess which number I picked.
 * Every time you guess wrong, I'll tell you whether the number is higher or lower.
 * You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):
 * -1 : My number is lower
 * 1 : My number is higher
 * 0 : Congrats! You got it!
 */

/*
 * Example :
 * Input: n = 10, pick = 6
 * Output: 6
 */

/*
 * Forward declaration of guess API.
 * @param num, your guess
 * @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
 * int guess(int num);
 */
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        if(n == 1) return 1;
        return _guessNumber(1, n);
    }

private:
    int _guessNumber(int l, int r)
    {
        int mid = l + (r - l) / 2;
        int res = guess(mid);
        if(res == 0)
            return mid;
        else if(res == -1)
            return _guessNumber(l, mid - 1);
        else
            return _guessNumber(mid + 1, r);
    }
};
