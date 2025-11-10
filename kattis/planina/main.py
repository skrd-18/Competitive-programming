def list_mutability() -> None:
    data = [1,2,3,4]

    datum = data * 2

    print(f'data = {data}')
    print(f'datum = {datum}')
    print(id(datum[0]))
    print(id(data))

    data[3] = 1000
    print()

    print(f'data = {data}')
    print(f'datum = {datum}')
    print(id(datum[0]))
    print(id(data))

n = int(input())
e = 2**n + 1
print(e**2)
