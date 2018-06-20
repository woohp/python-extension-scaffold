import unittest
import {{ cookiecutter.module_name }}


class {{ cookiecutter.module_name.title()|replace('_', '') }}TestCase(unittest.TestCase):
    def test_{{ cookiecutter.function_name }}(self):
        self.assertEqual({{ cookiecutter.module_name }}.{{ cookiecutter.function_name }}(1, 2), 3)
