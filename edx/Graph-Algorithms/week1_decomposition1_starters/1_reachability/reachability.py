def reach(adj, x, y):
    visited = [False] * n  # Only initialise once

    def dfs(x):
        visited[x] = True  # Mark the starting vertex as explored
        for neighbour in adj[x]:
            if neighbour == y:
                return 1  # Found it immediately
            if not visited[neighbour]:  # not False = True
                if dfs(neighbour) == 1:
                    return 1  # Found it deeper in the recursion
        return 0  # Dead end

    return dfs(x)


# if __name__ == "__main__":
inp1 = """
4 4
1 2
3 2
4 3
1 4
1 4
"""

input = inp1.strip()
data = list(map(int, input.split()))
n, m = data[
    0:2
]  # The first number is the number of vertices n and the second is the number of edges m
data = data[2:]
edges = list(zip(data[0 : (2 * m) : 2], data[1 : (2 * m) : 2]))
x, y = data[2 * m :]  # Output 1 if there is a path between x and y and 0 otherwise
adj = [[] for _ in range(n)]
x, y = x - 1, y - 1
for a, b in edges:
    adj[a - 1].append(b - 1)
    adj[b - 1].append(a - 1)

print(reach(adj, x, y))
