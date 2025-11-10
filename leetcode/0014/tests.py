import unittest
# pyrefly: ignore  # import-error
import main


class TestStringMethods(unittest.TestCase):

    def test_longestCommonPrefix(self) -> None:
        self.assertEqual(main.longestCommonPrefix(["flower", "flow", "flight"]), "fl")
        self.assertEqual(main.longestCommonPrefix(["dog", "racecar", "car"]), "")
        self.assertEqual(main.longestCommonPrefix(["", ""]), "")
        self.assertEqual(main.longestCommonPrefix([""]), "")
        self.assertEqual(main.longestCommonPrefix([]), "")
        self.assertEqual(main.longestCommonPrefix(["a"]), "a")
        self.assertEqual(main.longestCommonPrefix(["ab", "a"]), "a")

    def test_longestCommonPrefix2(self) -> None:
        self.assertEqual(main.longestCommonPrefix2(["flower", "flow", "flight"]), "fl")
        self.assertEqual(main.longestCommonPrefix2(["dog", "racecar", "car"]), "")
        self.assertEqual(main.longestCommonPrefix2(["a"]), "a")
        self.assertEqual(main.longestCommonPrefix2(["ab", "a"]), "a")

    # def test_upper(self):
    #     self.assertEqual("foo".upper(), "FOO")

    # def test_isupper(self):
    #     self.assertTrue("FOO".isupper())
    #     self.assertFalse("Foo".isupper())

    # def test_split(self):
    #     s = "hello world"
    #     self.assertEqual(s.split(), ["hello", "world"])
    #     # check that s.split fails when the separator is not a string
    #     with self.assertRaises(TypeError):
    #         s.split(2)


if __name__ == "__main__":
    # pyrefly: ignore  # not-callable
    unittest.main()
