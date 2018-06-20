#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/ndarrayobject.h>
#if PY_VERSION_HEX >= 0x03000000
#define PyInt_Check PyLong_Check
#define PyInt_AsLong PyLong_AsLong
#endif
#include <pybind11/numpy.h>

using namespace std;
namespace py = pybind11;


int {{ cookiecutter.function_name }}(py::array_t<int> input)
{
    auto buf = input.request();
    int* ptr = reinterpret_cast<int*>(buf.ptr);
    return std::accumulate(ptr, ptr + buf.size, 0);
}


bool import_numpy()
{
    // wacky NumPy API: import_array1() is a macro which actually calls return with the given value
    import_array1(false);
    return true;
}


PYBIND11_MODULE({{ cookiecutter.module_name }}, m)
{
    using namespace pybind11::literals;

    import_numpy();

    m.doc() = "My Python extension";

    const auto {{ cookiecutter.function_name }}_docstring =
        R"(Sum all the numbers in an array.

    Args:
        input: the array of integers to add

    Returns:
        the sum.
)";
    m.def("{{ cookiecutter.function_name }}", &{{ cookiecutter.function_name }}, {{ cookiecutter.function_name }}_docstring, "input"_a);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#endif
}
