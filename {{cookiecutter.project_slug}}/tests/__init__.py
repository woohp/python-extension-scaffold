import unittest
import {{ cookiecutter.op_name }}
import tensorflow as tf
import numpy as np


class {{ cookiecutter.cpp_kernel_name }}TestCase(unittest.TestCase):
    def test_{{ cookiecutter.op_name }}_dataset(self):
        with tf.Session() as sess:
            d = {{ cookiecutter.op_name }}.{{ cookiecutter.cpp_kernel_name }}Dataset()
            iterator = d.make_one_shot_iterator()
            next_element = iterator.get_next()
            try:
                i = 0
                while True:
                    batch = sess.run(next_element)
                    np.testing.assert_equal(batch, np.full((8,), i, dtype=np.int32))
                    i += 1

            except tf.errors.OutOfRangeError:
                pass

        self.assertEqual(i, 32)
