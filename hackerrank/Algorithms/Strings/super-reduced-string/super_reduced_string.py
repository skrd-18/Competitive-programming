def super_reduced_string(s: str) -> str:
    m = list(s)
    c = 0
    while c < len(m)-1:
        if m[c] == m[c+1]:
            del m[c]
            del m[c]
            if c != 0:
                c = c-1
        else:
            c = c+1
    if len(m) == 0:
        return 'Empty String'
    else:
        return ''.join(map(str, m))


print(super_reduced_string("baab"))
