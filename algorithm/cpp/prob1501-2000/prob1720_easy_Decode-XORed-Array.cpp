
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int n = encoded.size();
        vector<int> decoded(n + 1);
        decoded[0] = first;
        // encoded[i] = decoded[i] ^ decoded[i + 1]
        // decoded[i + 1] = encoded[i] ^ decoded[i]
        for(int i = 0; i < n; ++i)
            decoded[i + 1] = encoded[i] ^ decoded[i];
        return decoded;
    }
};
