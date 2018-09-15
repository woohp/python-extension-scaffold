#!/usr/bin/env python
from setuptools import setup
from torch.utils.cpp_extension import CppExtension, BuildExtension
import sys


class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


libraries = []  # add any libraries, such as sqlite3, here

ext_modules = [
    CppExtension(
        '{{ cookiecutter.op_name }}.{{ cookiecutter.op_name }}_op', [
            'src/module.cpp',
        ],
        libraries=libraries,
        language='c++'
    ),
]


class BuildExt(BuildExtension):
    def build_extensions(self):
        compiler_type = self.compiler.compiler_type

        opts = ['-march=native']
        if sys.platform == 'darwin':
            opts += ['-stdlib=libc++']

        if compiler_type == 'unix':
            opts.extend([
                '-DVERSION_INFO="{}"'.format(self.distribution.get_version()),
                '-std=c++14',
            ])

        for ext in self.extensions:
            ext.extra_compile_args = opts

        super().build_extensions()


setup(
    name='{{ cookiecutter.project_slug }}',
    description='{{ cookiecutter.description }}',
    version='{{ cookiecutter.version }}',
    setup_requires=['torch>=0.4.1'],
    install_requires=['torch>=0.4.1'],
    ext_modules=ext_modules,
    cmdclass={'build_ext': BuildExt},
    test_suite='tests',
    zip_safe=False,
)
