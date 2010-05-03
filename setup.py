from distutils.core import setup, Extension

gooey_module = Extension('gooey',
                         include_dirs = ['/usr/local/include/SDL'],
                         libraries = ['SDL', 'pthread'],
                         library_dirs = ['/usr/lib', '/usr/local/lib'],
                         sources = ['gooey_pymodule.cpp'])

setup (name = 'gooey_package',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [gooey])
