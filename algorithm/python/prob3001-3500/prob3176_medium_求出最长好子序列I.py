class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.append(int(1e9+1))

        @lru_cache(int(1e8))
        def solve(i: int, k: int) -> int:
            if k == -1:
                return 0

            mx = 0
            for j in range(i):
                if nums[i] == nums[j]:
                    mx = max(mx, solve(j, k))
                else:
                    mx = max(mx, solve(j, k - 1))

            return 1 + mx

        return solve(n, k + 1)
