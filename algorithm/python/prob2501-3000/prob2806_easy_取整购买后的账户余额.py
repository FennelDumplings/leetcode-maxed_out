class Solution:
    def accountBalanceAfterPurchase(self, purchaseAmount: int) -> int:
        m = purchaseAmount % 10
        if m < 5:
            x = purchaseAmount - m
        else:
            x = purchaseAmount + (10 - m)
        return 100 - x

