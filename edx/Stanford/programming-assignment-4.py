# Stack: LIFO (Last in First Out) data structure implementation

"""
The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex). So for example, the 11th row looks liks : "2 47646". This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646

Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.

Enter the sizes of the 5 largest SCCs in the given graph using the fields below, in decreasing order of sizes. So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, enter 500 in the first field, 400 in the second, 300 in the third, and so on. If your algorithm finds less than 5 SCCs, then enter 0 for the remaining fields. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then you enter 400, 300, and 100 in the first, second, and third fields, respectively, and 0 in the remaining 2 fields.

WARNING: This is the most challenging programming assignment of the course. Because of the size of the graph you may have to manage memory carefully. The best way to do this depends on your programming language and environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.
"""

from typing import List, Tuple


def read_graph_two_pass(path: str) -> Tuple[List[List[int]], List[List[int]], int]:
    """
    Returns (G, GR, n) with 1-based indexing.
    G[u]  = out-neighbors of u in the original graph.
    GR[u] = out-neighbors of u in the reversed graph (incoming to u in G).
    n     = max vertex label seen in the file.
    """
    # pass 1: find max label
    n = 0
    with open(path, "r") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            a, b = s.split()  # split using whitespace
            u, v = int(a), int(b)  # typecast into integer type
            n = u if u > v else v

    G = [[] for _ in range(n + 1)]
    GR = [[] for _ in range(n + 1)]

    # pass 2: fill G and GR
    with open(path, "r") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            a, b = s.split()
            u, v = int(a), int(b)
            G[u].append(v)
            GR[v].append(u)  # reverse edge: v -> u

    return G, GR, n


def finishing_order(GR, n):
    explored = bytearray(n + 1)  # all zeroes
    finished = [0] * (n + 1)  # (postorder timestamps; optional but nice to print)
    order = []  # We will append v on finish
    t = 0  # global postorder clock
    # Keep index 0 unused since labels are 1..n.
    # Simulate recursion with a stack of frames (u, i), where i is the next neighbor index you’ll try for u.

    for start in range(n, 0, -1):  # Index 0 is unused
        if explored[start] == 0:
            stack = [
                (start, 0)
            ]  # 0 stands for the 0th element, the first edge from the currentnode
            explored[start] = 1  # start is explored

            while stack:  # While the stack is not empty
                u, i = stack[-1]  # Peek at the last element; Last In First Out
                if i < len(GR[u]):  # Check that the node has at least one edge
                    v = GR[u][i]
                    stack[-1] = u, i + 1  # We have consumed that neighbour slot
                    if not explored[v]:
                        explored[v] = 1
                        stack.append((v, 0))
                else:  # no more neighbours
                    # Finish u.
                    t += 1
                    finished[u] = t
                    order.append(u)  # Append the u to order, then you pop()
                    stack.pop()  # Pop the frame; This “finish on pop” is the single most important invariant. If you accidentally append on discovery, Pass 2 won’t work.
        else:
            continue
    return list(reversed(order)), finished


def run_scc(order, G, n):
    explored = bytearray(n + 1)
    leader = [0] * (n + 1)  # who discovered each vertex in pass 2
    scc_sizes = []  # collect sizes here

    for v in order:
        if explored[v]:
            continue
        s = v  # assume v is the leader s, new leader (source of this DFS tree)
        size = 1  # reset the size incremental variable here
        leader[s] = s
        stack = [(v, 0)]
        explored[v] = 1  # v is explored.
        while stack:
            v, i = stack[-1]
            if i < len(G[v]):
                u = G[v][i]  # find the edge, neighbour vertex
                stack[-1] = v, i + 1  # we have consumed the neighbour slot
                if not explored[u]:
                    explored[u] = 1
                    leader[u] = s
                    stack.append((u, 0))
                    size += 1  # Increments size for every newly discovered vertex
            else:  # no more neighbours, a scc has been found
                stack.pop()

        scc_sizes.append(size)
    return scc_sizes, leader


if __name__ == "__main__":
    G, GR, n = read_graph_two_pass(
        "/Users/shiva/Documents/Competitive-programming/edx/Stanford/data/Programming-Assignment-4.txt"
    )
    # print("n =", n)  # expect 7
    # print("Empty list exists? G[1] =", G[1])  # should print a list (possibly non-empty), never KeyError
    # print(f"G = {G}")
    # print(
    # f"GR = {GR}"
    # )  # these arrays are 1-'indexed', that's why the first element is 0.

    # print("\n")
    order, finished = finishing_order(GR, n)
    # print(finished)

    # print("\n")
    scc_sizes, leader = run_scc(order, G, n)
    print(f"scc_sizes = {sorted(scc_sizes, reverse=True)[:6]}")
    # print(f"leader = {leader}")
