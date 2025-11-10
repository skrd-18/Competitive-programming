import unittest


class Zipper:
    @staticmethod
    def from_tree(tree: dict[str, dict[str, dict[str, int | None] | int | None] | dict[str, int | None] | int]) -> None:
        pass

    def value(self) -> None:
        pass

    def set_value(self) -> None:
        pass

    def left(self) -> None:
        pass

    def set_left(self) -> None:
        pass

    def right(self) -> None:
        pass

    def set_right(self) -> None:
        pass

    def up(self) -> None:
        pass

    def to_tree(self) -> None:
        pass


class ZipperTest(unittest.TestCase):
    def test_data_is_retained(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.to_tree()
        self.assertEqual(result, expected)

    def test_left_right_and_value(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().right().value()
        self.assertEqual(result, 3)

    def test_dead_end(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().left()
        self.assertIsNone(result)

    def test_tree_from_deep_focus(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().right().to_tree()
        self.assertEqual(result, expected)

    def test_traversing_up_from_top(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.up()
        self.assertIsNone(result)

    def test_left_right_and_up(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().up().right().up().left().right().value()
        self.assertEqual(result, 3)

    def test_test_ability_to_descend_multiple_levels_and_return(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().right().up().up().value()
        self.assertEqual(result, 1)

    def test_set_value(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 5,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().set_value(5).to_tree()
        self.assertEqual(result, expected)

    def test_set_value_after_traversing_up(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 5,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().right().up().set_value(5).to_tree()
        self.assertEqual(result, expected)

    def test_set_left_with_leaf(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 2,
                "left": {"value": 5, "left": None, "right": None},
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        result = (
            # pyrefly: ignore  # missing-attribute
            zipper.left().set_left({"value": 5, "left": None, "right": None}).to_tree()
        )
        self.assertEqual(result, expected)

    def test_set_right_with_null(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {"value": 2, "left": None, "right": None},
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().set_right(None).to_tree()
        self.assertEqual(result, expected)

    def test_set_right_with_subtree(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {
                "value": 6,
                "left": {"value": 7, "left": None, "right": None},
                "right": {"value": 8, "left": None, "right": None},
            },
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.set_right(
            {
                "value": 6,
                "left": {"value": 7, "left": None, "right": None},
                "right": {"value": 8, "left": None, "right": None},
            }
        ).to_tree()
        self.assertEqual(result, expected)

    def test_set_value_on_deep_focus(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        expected = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 5, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        zipper = Zipper.from_tree(initial)
        # pyrefly: ignore  # missing-attribute
        result = zipper.left().right().set_value(5).to_tree()
        self.assertEqual(result, expected)

    def test_different_paths_to_same_zipper(self) -> None:
        initial = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        # pyrefly: ignore  # missing-attribute
        result = Zipper.from_tree(initial).left().up().right().to_tree()
        final = {
            "value": 1,
            "left": {
                "value": 2,
                "left": None,
                "right": {"value": 3, "left": None, "right": None},
            },
            "right": {"value": 4, "left": None, "right": None},
        }
        # pyrefly: ignore  # missing-attribute
        expected = Zipper.from_tree(final).right().to_tree()
        self.assertEqual(result, expected)
