// prob251: Flatten 2D Vector

/*
 * Design and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.
 */

/*
 * Example:
 * Vector2D iterator = new Vector2D([[1,2],[3],[4]]);
 * iterator.next(); // return 1
 * iterator.next(); // return 2
 * iterator.next(); // return 3
 * iterator.hasNext(); // return true
 * iterator.hasNext(); // return true
 * iterator.next(); // return 4
 * iterator.hasNext(); // return false
 */

/*
 * Notes:
 * Please remember to RESET your class variables declared in Vector2D, as static/class variables are persisted across multiple test cases. Please see here for more details.
 * You may assume that next() call will always be valid, that is, there will be at least a next element in the 2d vector when next() is called.
 */

#include <vector>

using namespace std;

class Vector2D {
public:
    Vector2D(vector<vector<int>>& v):vec(v)
    {
        it_outer = vec.begin();
        while(it_outer != vec.end() && it_outer -> empty())
            ++it_outer;
        if(it_outer != vec.end())
            it_inner = it_outer -> begin();
    }

    int next() {
        int result = *it_inner;
        ++it_inner;
        if(it_inner == it_outer -> end())
        {
            ++it_outer;
            while(it_outer != vec.end() && it_outer -> empty())
                ++it_outer;
            if(it_outer != vec.end())
                it_inner = it_outer -> begin();
        }
        return result;
    }

    bool hasNext() {
        return !(it_outer == vec.end());
    }

private:
    vector<vector<int>> vec;
    vector<vector<int>>::iterator it_outer;
    vector<int>::iterator it_inner;
};
