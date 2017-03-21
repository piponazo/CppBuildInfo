import os
from conans import ConanFile

class CppBuildInfoConan(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'

    def requirements(self):
        self.requires('gtest/1.8.0@lasote/stable')
