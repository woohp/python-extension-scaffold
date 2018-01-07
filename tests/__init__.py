import unittest
import myproject


class MyProjectTestCase(unittest.TestCase):
    def test_add(self):
        self.assertEqual(myproject.add(1, 2), 3)
