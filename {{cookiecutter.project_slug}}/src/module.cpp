#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
using namespace std;
namespace py = pybind11;


int {{ cookiecutter.function_name }}(int x, int y)
{
    return x + y;
}


PYBIND11_MODULE({{ cookiecutter.module_name }}, m)
{
    using namespace pybind11::literals;

    m.doc() = "My Python extension";

    const auto {{ cookiecutter.function_name }}_docstring =
        R"(Adds two numbers.

    Args:
        x: the first number to add
        y: the second number to add

    Returns:
        sum of the two numbers.
)";
    m.def("{{ cookiecutter.function_name }}", &{{ cookiecutter.function_name }}, {{ cookiecutter.function_name }}_docstring, "x"_a, "y"_a);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#endif
}
