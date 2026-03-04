class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        res = 0
        for user in accounts:
            tmp = sum(user)
            if res < tmp:
                res = tmp
        return res


sol = Solution()
accounts = [[2, 8, 7], [7, 1, 3], [1, 9, 5]]
print(sol.maximumWealth(accounts=accounts))
