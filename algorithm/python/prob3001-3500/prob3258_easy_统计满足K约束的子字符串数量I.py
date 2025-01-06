class Solution:
    def countKConstraintSubstrings(self, s: str, k: int) -> int:
        n = len(s)
        N = n * (n + 1) // 2
        c0 = 0
        c1 = 0
        j = 0
        while j < n:
            if s[j] == "0":
                c0 += 1
            else:
                c1 += 1
            if c0 > k and c1 > k:
                break
            j += 1
        if c0 <= k or c1 <= k:
            return N

        i0 = 0
        i1 = 0
        while i0 <= j:
            if s[i0] == "0":
                if c0 == k + 1:
                    break
                c0 -= 1
            i0 += 1
        while i1 <= j:
            if s[i1] == "1":
                if c1 == k + 1:
                    break
                c1 -= 1
            i1 += 1
        # A[i0..j] 中有 k+1 个 0，A[i0+1..j] 中有 k 个 0
        # A[i1..j] 中有 k+1 个 1，A[i1+1..j] 中有 k 个 1

        ans = min(i0, i1) + 1

        j += 1
        while j < n:
            if s[j] == "0":
                i0 += 1
                while s[i0] != "0":
                    i0 += 1
            else:
                i1 += 1
                while s[i1] != "1":
                    i1 += 1
            ans += min(i0, i1) + 1
            j += 1
        return N - ans
