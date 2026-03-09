class Solution():
    def mergeAlternately(self, word1: str, word2: str) -> str:
        total_string = ""
        i = 0
        while len(word1) != (i) and len(word2) != (i):
            # Splice the string
            total_string += word1[i]
            total_string += word2[i]
            i +=1 
        # print(i)
        if len(word1) == (i):
            total_string += word2[i:]
        else:
            total_string += word1[i:]
        # print(total_string)
        return total_string

word1 = "abcd"
word2 = "pq"
sol = Solution()
sol.mergeAlternately(word1, word2)