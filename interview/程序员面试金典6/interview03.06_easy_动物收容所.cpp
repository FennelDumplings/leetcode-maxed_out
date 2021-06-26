// interview03.06: 动物收容所

/*
 * https://leetcode-cn.com/problems/animal-shelter-lcci/
 */

#include <queue>

using namespace std;

class AnimalShelf {
public:
    AnimalShelf() {
        q_cat = queue<int>();
        q_dog = queue<int>();
    }

    void enqueue(vector<int> animal) {
        if(animal[1] == 0)
            q_cat.push(animal[0]);
        else
            q_dog.push(animal[0]);
    }

    vector<int> dequeueAny() {
        if(q_cat.empty() && q_dog.empty())
            return {-1, -1};
        vector<int> result;
        if(q_cat.empty())
        {
            result = {q_dog.front(), 1};
            q_dog.pop();
            return result;
        }
        if(q_dog.empty())
        {
            result = {q_cat.front(), 0};
            q_cat.pop();
            return result;
        }
        if(q_dog.front() < q_cat.front())
        {
            result = {q_dog.front(), 1};
            q_dog.pop();
            return result;
        }
        else
        {
            result = {q_cat.front(), 0};
            q_cat.pop();
            return result;
        }
    }

    vector<int> dequeueDog() {
        if(q_dog.empty())
            return {-1, -1};
        vector<int> result;
        result = {q_dog.front(), 1};
        q_dog.pop();
        return result;
    }

    vector<int> dequeueCat() {
        if(q_cat.empty())
            return {-1, -1};
        vector<int> result;
        result = {q_cat.front(), 0};
        q_cat.pop();
        return result;
    }

private:
    queue<int> q_cat, q_dog;
};
