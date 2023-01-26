// prob1166: Design File System

/*
 * You are asked to design a file system which provides two functions:
 * createPath(path, value): Creates a new path and associates a value to it if possible and returns True. Returns False if the path already exists or its parent path doesn't exist.
 * get(path): Returns the value associated with a path or returns -1 if the path doesn't exist.
 * The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
 * Implement the two functions.
 * Please refer to the examples for clarifications.
 */

/*
 * Example 1:
 * Input:
 * ["FileSystem","createPath","get"]
 * [[],["/a",1],["/a"]]
 * Output:
 * [null,true,1]
 * Explanation:
 * FileSystem fileSystem = new FileSystem();
 * fileSystem.createPath("/a", 1); // return true
 * fileSystem.get("/a"); // return 1
 * Example 2:
 * Input:
 * ["FileSystem","createPath","createPath","get","createPath","get"]
 * [[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
 * Output:
 * [null,true,true,2,false,-1]
 * Explanation:
 * FileSystem fileSystem = new FileSystem();
 * fileSystem.createPath("/leet", 1); // return true
 * fileSystem.createPath("/leet/code", 2); // return true
 * fileSystem.get("/leet/code"); // return 2
 * fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
 * fileSystem.get("/c"); // return -1 because this path doesn't exist.
 */

/*
 * Constraints:
 * The number of calls to the two functions is less than or equal to 10^4 in total.
 * 2 <= path.length <= 100
 * 1 <= value <= 10^9
 */

#include <string>
#include <unordered_map>

using namespace std;

class FileSystem {
public:
    FileSystem() {
        mapping = unordered_map<string, int>();
    }

    bool createPath(string path, int value) {
        if(path.empty()) return false;
        if(path.back() == '/') return false;
        if(mapping.find(path) != mapping.end())
            return false;
        int n = path.size();
        int right_fold_idx = n - 1;
        while(right_fold_idx >= 0 && path[right_fold_idx] != '/')
            --right_fold_idx;
        string father;
        if(right_fold_idx == -1)
            father = "";
        else
            father = path.substr(0, right_fold_idx);
        if(father != "" && mapping.find(father) == mapping.end())
            return false;
        mapping[path] = value;
        return true;
    }

    int get(string path) {
        if(mapping.find(path) == mapping.end())
            return -1;
        return mapping[path];
    }

private:
    unordered_map<string, int> mapping;
};

