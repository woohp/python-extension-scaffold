import unittest
import {{ cookiecutter.module_name }}
import numpy as np


class {{ cookiecutter.module_name.title()|replace('_', '') }}TestCase(unittest.TestCase):
    def test_{{ cookiecutter.function_name }}(self):
        a = np.array([1, 2, 3], dtype=np.int32)
        self.assertEqual({{ cookiecutter.module_name }}.{{ cookiecutter.function_name }}(a), 6)
