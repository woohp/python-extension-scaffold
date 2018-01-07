#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
using namespace std;
namespace py = pybind11;


int add(int x, int y)
{
    return x + y;
}


PYBIND11_MODULE(myproject, m)
{
    using namespace pybind11::literals;

    m.doc() = "My Python extension";

    const auto add_docstring =
R"(Adds two numbers.

    Args:
        x: the first number to add
        y: the second number to add

    Returns:
        sum of the two numbers.
)";
    m.def("add", &add, add_docstring, "x"_a, "y"_a);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#endif
}
