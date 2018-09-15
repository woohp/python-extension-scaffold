import unittest
import numpy as np
import torch
import {{ cookiecutter.op_name }}


class {{ cookiecutter.op_name.title()|replace('_', '') }}TestCase(unittest.TestCase):
    def test_times2(self):
        {{ cookiecutter.op_name }}_mod = {{ cookiecutter.op_name}}.{{ cookiecutter.cpp_kernel_name }}()
        x = torch.ones(2, 4)
        y = {{ cookiecutter.op_name }}_mod(x)
        np.testing.assert_array_equal(y, x * 2)

    def test_gradient(self):
        {{ cookiecutter.op_name }}_mod = {{ cookiecutter.op_name}}.{{ cookiecutter.cpp_kernel_name }}()
        x = torch.nn.Parameter(torch.arange(6, dtype=torch.float32).view(2, 3))
        y = {{ cookiecutter.op_name }}_mod(x)**3
        y.sum().backward()
        np.testing.assert_array_equal(x.grad, 6 * (2 * x.detach())**2)
