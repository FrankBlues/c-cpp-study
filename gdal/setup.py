from distutils.core import setup, Extension

module1 = Extension('spam',
                    include_dirs = ['/usr/include/python3.8'],
                    libraries = ['python3.8'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['spammodule.c'])

setup (name = 'spam',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
