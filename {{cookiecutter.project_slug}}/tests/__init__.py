import unittest
import {{ cookiecutter.op_name }}
import tensorflow as tf
import numpy as np


class {{ cookiecutter.cpp_kernel_name }}TestCase(unittest.TestCase):
    def test_{{ cookiecutter.op_name }}(self):
        x = np.arange(6, dtype=np.float32).reshape((2, 3))
        with tf.Session() as sess:
            y = sess.run({{ cookiecutter.op_name }}.{{ cookiecutter.op_name }}(x))
        np.testing.assert_array_equal(y, x * 2)

    def test_gradient(self):
        x = tf.placeholder('float32', [None, None])
        y = tf.reduce_sum({{ cookiecutter.op_name }}.{{ cookiecutter.op_name }}(x) ** 3)
        g = tf.gradients(y, x)[0]

        with tf.Session() as sess:
            x_ = np.arange(6, dtype=np.float32).reshape((2, 3))
            g_ = sess.run(g, {x: x_})
        np.testing.assert_almost_equal(g_, 6 * (2 * x_) ** 2, 2)
