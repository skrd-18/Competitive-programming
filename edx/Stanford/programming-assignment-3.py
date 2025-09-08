import typing
import random


triangle_case = """
1 2 3
2 1 3
3 1 2
"""


def read_edgeslist(path: str) -> typing.List[typing.List[int]]:
    with open(path, "r") as f:
        lines = f.readlines()
    edgeslist = []
    for line in lines:
        edges = list(map(int, line.split()))
        for _ in range(len(edges) - 1):
            edgeslist.append([edges[0], edges[_ + 1]])
    return edgeslist


def kargers_cut(edgeslist: typing.List[typing.List[int]]) -> int:
    min_cut_so_far = 1000000

    for _ in range(200):
        # run different random seeds for each trial
        random.seed()

        # Create a DEEP COPY of the edge list for each trial.
        edges = [edge[:] for edge in edgeslist]

        vertices = set()
        for edge in edges:
            vertices.add(edge[0])
            vertices.add(edge[1])

        while len(vertices) > 2:
            # If the edge list becomes empty while vertices > 2, something is wrong.
            # This can happen if the graph gets disconnected, which means the cut is 0.
            if not edges:
                # This case is unlikely with the provided data but is good practice.
                return 0

            rand_index = random.randrange(len(edges))
            u, v = edges[rand_index]

            if u in vertices and v in vertices and u != v:
                # This is a valid edge, so we proceed with contraction.
                edges.pop(rand_index)

                # 1. Remove the absorbed vertex
                vertices.remove(v)

                # 2. Merge v into u by re-pointing all of v's edges to u
                for edge in edges:
                    if edge[0] == v:
                        edge[0] = u
                    if edge[1] == v:
                        edge[1] = u

                # 3. Remove the self-loops that were just created
                edges = [edge for edge in edges if edge[0] != edge[1]]
            # else:
            #     print("Stale edge encountered.")
            #     # This is a stale edge (one of its vertices was already absorbed).
            #     # Just remove it and continue to the next iteration of the while loop.
            #     edges.pop(rand_index)
            #     continue  # Go to the next iteration of `while len(vertices) > 2:`

        current_cut_size = len(edges)
        if current_cut_size < min_cut_so_far:
            min_cut_so_far = current_cut_size

    return min_cut_so_far // 2


if __name__ == "__main__":
    edgeslist = read_edgeslist(
        "/home/shiva/Projects/Competitive-programming/edx/Stanford/data/Programming-Assignment-3.txt"
    )
    print(edgeslist[:10])
    print(kargers_cut(edgeslist))
    # print(
    #     kargers_cut([[1, 2], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2]])
    # )  # triangle case
