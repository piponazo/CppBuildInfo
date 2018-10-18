import os
from conans import ConanFile

class CppBuildInfoConan(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'

    
    def configure(self):
        self.options['gtest'].shared = True

    def requirements(self):
        self.requires('gtest/1.8.0@bincrafters/stable')

    def imports(self):
        self.copy('*.dll', dst='bin', src='bin')
        self.copy('*.dylib', dst='bin', src='lib')
