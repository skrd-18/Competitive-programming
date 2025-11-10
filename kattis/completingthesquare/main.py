import sys

## Wishful thinking

## Calculate the distance between them


x, y = map(int, input().split())
p1 = [x, y]

x, y = map(int, input().split())
p2 = [x, y]

x, y = map(int, input().split())
p3 = [x, y]

def calculate_distance(p1: list[int], p2: list[int]):
    return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2

##p1 = [-5, -8]
##p2 = [-8, -1]
##p3 = [2, -5]

dist_1_2 = calculate_distance(p1, p2)
dist_1_3 = calculate_distance(p1, p3)

if dist_1_2 == dist_1_3:
    p1, p3 = p3, p1
elif dist_1_3 > dist_1_2:
    p2, p3 = p3, p2

x = p1[0] + (p2[0] - p3[0])
y = p1[1] + (p2[1] - p3[1])

print(x, y)

