#!/usr/bin/env python
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys


libraries = ['tensorflow_framework']  # add any libraries, such as sqlite3, here

ext_modules = [
    Extension(
        '{{ cookiecutter.op_name }}.{{ cookiecutter.op_name }}_op',
        [
            'src/module.cpp',
        ],
        include_dirs=[],
        libraries=libraries,
        language='c++'
    ),
]


class BuildExt(build_ext):
    def build_extensions(self):
        import tensorflow as tf

        compiler_type = self.compiler.compiler_type

        opts = ['-O2', '-march=native', '-ffast-math'] + tf.sysconfig.get_compile_flags()
        if sys.platform == 'darwin':
            opts += ['-stdlib=libc++', '-mmacosx-version-min=10.8', '-undefined dynamic_lookup']

        if compiler_type == 'unix':
            opts.extend([
                '-DVERSION_INFO="{}"'.format(self.distribution.get_version()),
                '-std=c++14',
            ])

        for ext in self.extensions:
            ext.extra_compile_args = opts
            ext.extra_link_args = tf.sysconfig.get_link_flags()

        build_ext.build_extensions(self)


setup(
    name='{{ cookiecutter.project_slug }}',
    description='{{ cookiecutter.description }}',
    version='{{ cookiecutter.version }}',
    setup_requires=['tensorflow>=1.10.1'],
    install_requires=['tensorflow>=1.10.1'],
    ext_modules=ext_modules,
    packages=['{{ cookiecutter.op_name }}'],
    cmdclass={'build_ext': BuildExt},
    test_suite='tests',
    zip_safe=False,
)
