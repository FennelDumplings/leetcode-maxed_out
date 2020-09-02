// prob604: Design Compressed String Iterator

/*
 * https://leetcode-cn.com/problems/design-compressed-string-iterator/
 */

#include <string>
#include <sstream>

using namespace std;

// 全部缓存不行
class StringIterator_2 {
public:
    StringIterator_2(string compressedString) {
        int n = compressedString.size();
        int i = 0;
        while(i < n)
        {
            char ch = compressedString[i];
            ++i;
            int j = i;
            while(j < n && (compressedString[j] >= '0' && compressedString[j] <= '9'))
                ++j;
            stringstream ss;
            int k;
            ss << compressedString.substr(i, j - i);
            ss >> k;
            for(int l = 1; l <= k; ++l)
                data += ch;
            i = j;
        }
        iter = data.begin();
    }

    char next() {
        return *iter++;
    }

    bool hasNext() {
        return iter != data.end();
    }

private:
    string::iterator iter;
    string data;
};


//
class StringIterator {
public:
    StringIterator(string compressedString) {
        str.swap(compressedString);
        n = str.size();
        cnt = 0;
        k = 0;
        left = 0, right = 1;
        while(right < n && (str[right] >= '0' && str[right] <= '9'))
            ++right;
        stringstream ss;
        ss << str.substr(left + 1, right - left - 1);
        ss >> k;
    }

    char next() {
        if(!hasNext())
            return ' ';
        char res = str[left];
        ++cnt;
        if(cnt == k)
        {
            left = right;
            cnt = 0;
            if(hasNext())
            {
                ++right;
                while(right < n && (str[right] >= '0' && str[right] <= '9'))
                    ++right;
                stringstream ss;
                ss << str.substr(left + 1, right - left - 1);
                ss >> k;
            }
        }
        return res;
    }

    bool hasNext() {
        return left < n;
    }

private:
    string str;
    int left, right;
    int cnt;
    int k;
    int n;
};
