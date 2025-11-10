


test = []
for _ in range(4):
    test.append(list(input()))

## Wishful thinking
def manhattan_distance(i: int, j: int, m: int, n: int):
    return abs(i - m) + abs(j - n)


solution = [['A', 'B', 'C', 'D'], ['E', 'F', 'G', 'H'], ['I', 'J', 'K', 'L'], ['M', 'N', 'O', '.']]

##test = [['.', 'B', 'C', 'D'], ['E', 'A', 'G', 'H'], ['I', 'J', 'F', 'L'], ['M', 'N', 'O', 'K']]

scatter_score = 0

for i in range(len(solution)):
    for j in range(len(solution[0])):
        if solution[i][j] == ".":
            continue
        
##        print(solution[i][j])
        
        for m in range(len(test)):
            for n in range(len(test[0])):
                if test[m][n] == solution[i][j]:
                    scatter_score += manhattan_distance(i, j, m, n)
                    break ## we have found the letter matching to the first solution
        
        

print(scatter_score)
