class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        result = [-1 for _ in range(n)]
        st = []
        D = []
        for i in range(n):
            while D and nums[D[-1]] < nums[i]:
                j = D.pop()
                result[j] = i
            k = len(st) - 1
            while k >= 0 and nums[st[k]] < nums[i]:
                k -= 1
            # [k+1..len(st)-1] 这部分要弹出，先将其按原顺序压入 D
            D += st[k + 1:]
            # 然后整体弹出 [k+1..len(st)-1]
            del st[k + 1:]
            st.append(i)
        return result
