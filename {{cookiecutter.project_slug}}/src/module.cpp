#include <torch/torch.h>
using namespace std;


std::vector<at::Tensor> {{ cookiecutter.op_name }}_forward(at::Tensor input)
{
    return { input * 2 };
}

std::vector<at::Tensor> {{ cookiecutter.op_name }}_backward(at::Tensor grad_out)
{
    return { grad_out * 2 };
}


PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    using namespace pybind11::literals;

    m.def("forward", {{ cookiecutter.op_name }}_forward);
    m.def("backward", {{ cookiecutter.op_name }}_backward);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#endif
}
