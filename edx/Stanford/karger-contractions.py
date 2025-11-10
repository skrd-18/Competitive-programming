import copy
import random


def random_edge(G: dict[int, list[int]]):
    # build the multiset of undirected edges once per contraction
    edges = []
    for u, nbrs in G.items():
        for v in nbrs:
            if u < v:  # include each undirected edge once
                edges.append((u, v))
    return random.choice(edges)


def contract(G: dict[int, list[int]], u, v) -> None:
    # 1) move v's adjacency to u (keep multiplicity)
    G[u].extend(G[v])

    # 2) redirect all edges that pointed to v so they point to u
    for x in G[v]:
        G[x] = [u if w == v else w for w in G[x]]

    # 3) remove self-loops on u
    G[u] = [w for w in G[u] if w != u]

    # 4) delete v
    del G[v]


def karger_min_cut(graph: dict[int, list[int]]) -> float | int:
    n = len(graph)
    trials = n * n  # simple choice; you can use n(n-1) log n for higher success
    best = float("inf")

    for _ in range(trials):
        G = copy.deepcopy(graph)
        while len(G) > 2:
            u, v = random_edge(G)
            contract(G, u, v)
        # two supernodes remain; cut size = # edges between them
        remaining = list(G.keys())
        cut_size = len(G[remaining[0]])
        best = min(best, cut_size)
    return best


# example: K4 (min cut = 3)
graph = {0: [1, 2, 3], 1: [0, 2, 3], 2: [0, 1, 3], 3: [0, 1, 2]}
print(karger_min_cut(graph))
