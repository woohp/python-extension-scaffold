import os
import glob
import tensorflow as tf
from tensorflow.python.framework import ops
from tensorflow.python.ops.nn_grad import _BroadcastMul

# Assumes the file is in the current working directory.
op_library_path = glob.glob(os.path.join(os.path.dirname(__file__), "{{ cookiecutter.op_name }}_op*.so"))[0]
{{ cookiecutter.op_name }}_module = tf.load_op_library(op_library_path)

def {{ cookiecutter.op_name }}(x):
    return {{ cookiecutter.op_name }}_module.{{ cookiecutter.op_name }}(x)[0]


@ops.RegisterGradient('{{ cookiecutter.cpp_kernel_name }}')
def _{{ cookiecutter.cpp_kernel_name }}Grad(op, grad_loss, _):
    grad = op.outputs[1]
    return [grad_loss * grad]
