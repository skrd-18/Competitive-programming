# Stack: LIFO (Last in First Out) data structure implementation
from typing import Optional

# Directed graph representation using adjacency list
G: dict[int, list[int]] = {0: [1, 2], 1: [2], 2: [3], 3: []}


def dfs_reach(
    G: dict[int, list[int]], s: int
) -> tuple[set[int], dict[int, int | None], dict[int, int], dict[int, int], list[int]]:
    visited: set[int] = set()
    parent: dict[int, Optional[int]] = {s: None}
    tin: dict[int, int] = {}
    tout: dict[int, int] = {}
    time = 0
    finish_stack: list[int] = []  # decreasing finishing time

    def dfs(u: int) -> None:
        nonlocal time
        # 1) mark u as visited
        visited.add(u)
        tin[u] = time
        time += 1
        # 2) for each v in G(u) , if v not visited: dfs(v)
        for v in G[u]:
            if v not in visited:
                parent[v] = u  # record tree edges u -> v
                dfs(v)
        finish_stack.append(u)  # record u when it FINISHES
        tout[u] = time
        time += 1

    for u in G:
        if u not in visited:
            dfs(u)
    return visited, parent, tin, tout, finish_stack[::-1]


# quick checks
# print(dfs_reach(G, 0))  # expect {0,1,2,3}
# print(dfs_reach(G, 1))  # expect {1,2,3}
# print(dfs_reach(G, 3))  # expect {3}


def reconstruct_path(parent: dict[int, Optional[int]], t: int) -> list[int]:
    if t not in parent:  # unreachable from source
        return []
    path = []
    cur = t
    while cur is not None:
        path.append(cur)
        cur = parent[cur]
    path.reverse()
    return path


# Try from source 0
visited, parent, tin, tout, finish_stack = dfs_reach(G, 0)
print("visited:", visited)  # expect {0,1,2,3}
print("parent:", parent)  # e.g., {0:None, 1:0, 2:0 or 1, 3:2}
print("tin = {}".format(tin))
print("tout= {}".format(tout))
print("finish_stack = {}".format(finish_stack))
print("\n")
