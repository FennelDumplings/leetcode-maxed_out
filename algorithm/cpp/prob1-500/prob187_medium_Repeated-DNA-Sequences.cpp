// prob187: Repeated DNA Sequences

/*
 * All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG".
 * When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
 * Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
 */

/*
 * Example:
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 */

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if(s.empty()) return vector<string>();
        int n = s.size();
        if(n <= 10) return vector<string>();
        unordered_map<string, int> mapping;
        vector<string> result;
        for(int i = 0; i < n - 9; ++i)
        {
            string cur = s.substr(i, 10);
            ++mapping[cur];
            if(mapping[cur] == 2)
                result.push_back(cur);
        }
        return result;
    }
};
