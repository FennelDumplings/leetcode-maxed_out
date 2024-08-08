INF = int(2e9)

class Solution:
    def maxmiumScore(self, cards: List[int], cnt: int) -> int:
        def post_process(parity: int) -> int:
            # 在 cards[0:cnt] 中找奇偶性为 parity 的，记为 x
            # 再在 cards[cnt:n] 中找奇偶性相反的，记为 y
            # 若找到一组，则返回 y - x，否则返回 -INF
            # 由于 cards 有序，肯定有 y - x <= 0，因此返回 1 肯定代表无解
            l = cnt - 1
            while l >= 0 and cards[l] % 2 != parity:
                l -= 1
            if l >= 0:
                # 找到奇偶性为 parity 的 x = cards[l]
                r = cnt
                while r < n and cards[r] % 2 != (parity ^ 1):
                    r += 1
                if r < n:
                    # 找到奇偶性为 parity^1 的 y = cards[r]
                    return cards[r] - cards[l]
            return -INF

        n = len(cards)
        cards.sort(reverse=True)
        ans = sum(cards[0:cnt])
        if ans % 2 == 0:
            return ans

        delta0 = post_process(0)
        delta1 = post_process(1)
        if delta0 == -INF and delta1 == -INF:
            return 0
        return max(delta0, delta1) + ans
