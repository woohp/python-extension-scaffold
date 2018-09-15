import torch
from . import {{ cookiecutter.op_name }}_op


class {{ cookiecutter.cpp_kernel_name }}Function(torch.autograd.Function):
    @staticmethod
    def forward(ctx, x):
        out = {{ cookiecutter.op_name }}_op.forward(x)
        return out[0]

    @staticmethod
    def backward(ctx, grad_x):
        outputs = {{ cookiecutter.op_name }}_op.backward(grad_x.contiguous())
        return outputs[0]


class {{ cookiecutter.cpp_kernel_name }}(torch.nn.Module):
    def forward(self, x):
        return {{ cookiecutter.cpp_kernel_name }}Function.apply(x)
