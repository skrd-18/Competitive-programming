import unittest
import itertools

"""
Time started: 08:12 pm
Time alloted : 1 hour
Functional Programming paradigm
"""


def combinations(target: int, size: int, exclude):
    numbers = list(filter(lambda x: x not in exclude, range(1, 10)))

    # Invariant 1: Check if the numbers vaariable is correct
    assert all(num not in exclude for num in numbers), "Numbers contain exclude values"
    assert sorted(numbers) == numbers, "Numbers are not sorted"

    result = list(itertools.combinations(numbers, size))

    assert all(
        len(comb) == size for comb in result
    ), "Some combinations have incorrect size"

    filtered_result = list(filter(lambda x: sum(x) == target, result))
    filtered_result = list(map(list, filtered_result))

    return filtered_result


class KillerSudokuHelperTest(unittest.TestCase):
    def test_1(self) -> None:
        self.assertEqual(combinations(1, 1, []), [[1]])

    def test_2(self) -> None:
        self.assertEqual(combinations(2, 1, []), [[2]])

    def test_3(self) -> None:
        self.assertEqual(combinations(3, 1, []), [[3]])

    def test_4(self) -> None:
        self.assertEqual(combinations(4, 1, []), [[4]])

    def test_5(self) -> None:
        self.assertEqual(combinations(5, 1, []), [[5]])

    def test_6(self) -> None:
        self.assertEqual(combinations(6, 1, []), [[6]])

    def test_7(self) -> None:
        self.assertEqual(combinations(7, 1, []), [[7]])

    def test_8(self) -> None:
        self.assertEqual(combinations(8, 1, []), [[8]])

    def test_9(self) -> None:
        self.assertEqual(combinations(9, 1, []), [[9]])

    def test_cage_with_sum_45_contains_all_digits_1_9(self) -> None:
        self.assertEqual(combinations(45, 9, []), [[1, 2, 3, 4, 5, 6, 7, 8, 9]])

    def test_cage_with_only_1_possible_combination(self) -> None:
        self.assertEqual(combinations(7, 3, []), [[1, 2, 4]])

    def test_cage_with_several_combinations(self) -> None:
        self.assertEqual(combinations(10, 2, []), [[1, 9], [2, 8], [3, 7], [4, 6]])

    def test_cage_with_several_combinations_that_is_restricted(self) -> None:
        self.assertEqual(combinations(10, 2, [1, 4]), [[2, 8], [3, 7]])


test = KillerSudokuHelperTest()
test.test_cage_with_several_combinations_that_is_restricted()
