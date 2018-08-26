import glob
import os
import tensorflow as tf

# Assumes the file is in the current working directory.
op_library_path = glob.glob(os.path.join(os.path.dirname(__file__), "{{ cookiecutter.op_name }}_op*.so"))[0]
{{ cookiecutter.op_name }}_module = tf.load_op_library(op_library_path)


class {{ cookiecutter.cpp_kernel_name }}Dataset(tf.data.Dataset):
    def _as_variant_tensor(self):
        # Actually construct the graph node for the dataset op.
        #
        # This method will be invoked when you create an iterator on this dataset
        # or a dataset derived from it.
        return {{ cookiecutter.op_name }}_module.{{ cookiecutter.op_name }}_dataset()

    # The following properties define the structure of each element: a scalar
    # <a href="../api_docs/python/tf/string"><code>tf.string</code></a> tensor.
    # Change these properties to match the `output_dtypes()`
    # and `output_shapes()` methods of `MyReaderDataset::Dataset` if you modify
    # the structure of each element.
    @property
    def output_types(self):
        return tf.int32

    @property
    def output_shapes(self):
        return (
            tf.TensorShape([None]),
        )

    @property
    def output_classes(self):
        return (tf.Tensor,) * len(self.output_shapes)
