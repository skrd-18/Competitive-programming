import sys
from pprint import pprint

## Wishful thinking

##input = sys.stdin.read()
##line = input.strip("\n")

line1 = [""]
line2 = [""]
line3 = [""]
line4 = [""]
line5 = [""]

## Debugging
line = "ABCD"

def solve(line: str) -> None:
    for i in range(len(line)):
        if (i+1) % 3 != 0:
            # pyrefly: ignore  # missing-attribute
            line1.append("..#.")
            # pyrefly: ignore  # missing-attribute
            line2.append(".#.#")
            if (i) % 3 == 0 and  i != 0:
                # pyrefly: ignore  # missing-attribute
                line3.append("*." + str(line[i]) + ".")
            else:
                # pyrefly: ignore  # missing-attribute
                line3.append("#." + str(line[i]) + ".")
            # pyrefly: ignore  # missing-attribute
            line4.append(".#.#")
            # pyrefly: ignore  # missing-attribute
            line5.append("..#.")
        elif (i+1) % 3 == 0 and i != 0:
            # pyrefly: ignore  # missing-attribute
            line1.append("..*.")
            # pyrefly: ignore  # missing-attribute
            line2.append(".*.*")
            # pyrefly: ignore  # missing-attribute
            line3.append("*." + str(line[i]) + ".")
            # pyrefly: ignore  # missing-attribute
            line4.append(".*.*")
            # pyrefly: ignore  # missing-attribute
            line5.append("..*.")

    # pyrefly: ignore  # missing-attribute
    line1.append(".")
    # pyrefly: ignore  # missing-attribute
    line2.append(".")
    # pyrefly: ignore  # missing-attribute
    line4.append(".")
    # pyrefly: ignore  # missing-attribute
    line5.append(".")
    
    if len(line) % 3 == 0:
        # pyrefly: ignore  # missing-attribute
        line3.append("*")
    else:
        # pyrefly: ignore  # missing-attribute
        line3.append("#")

solve(line)

line1 = "".join(line1)
line2 = "".join(line2)
line3 = "".join(line3)
line4 = "".join(line4)
line5 = "".join(line5)

print(line1)
print(line2)
print(line3)
print(line4)
print(line5)




                
            
            









