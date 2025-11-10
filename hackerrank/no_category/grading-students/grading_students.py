#!/usr/bin/python3

def gradingStudents(grades: list[int]):
    multiples_5 = [i for i in range(101) if i % 5 == 0]


    for grade in grades:
        possible_grade = list(filter(lambda e : e > grade, multiples_5))[0]
        if grade < 38:
            continue
        elif grade >= 38:
            if (possible_grade - grade) < 3:
                grades[grades.index(grade)] = possible_grade
    return grades

print(gradingStudents([73, 67, 38, 33]))
