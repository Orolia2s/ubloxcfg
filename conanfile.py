import os
from conan import ConanFile
from conan.tools.scm import Git
from conan.tools.files import save, load, copy
from conan.tools.gnu import Autotools, AutotoolsToolchain, AutotoolsDeps

class UbloxCfgConan(ConanFile):
    name = 'ubloxcfg'
    version = '1.9'
    author = 'Philippe Kehl'
    url = 'https://github.com/phkehl/ubloxcfg.git'
    license = 'GPLv3'
    description = 'u-blox 9 positioning receivers configuration library and tool'
    topics = ('GNSS')

    settings = ('os', 'arch', 'compiler', 'build_type')
    options = {
        'shared': [True, False],
        'fPIC': [True, False]
    }
    default_options = {
        'shared': False,
        'fPIC': True
    }

    exports_sources = 'src/*', 'include/*', 'README.md', 'simple_makefile.mk', 'config.h.*'

    def configure(self):
        self.settings.rm_safe('compiler.libcxx')
        self.settings.rm_safe('compiler.cppstd')
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def generate(self):
        AutotoolsDeps(self).generate()
        AutotoolsToolchain(self).generate()

    def build(self):
        autotools = Autotools(self)
        autotools.make('shared' if self.options.shared else 'static', args=['-f', 'simple_makefile.mk'])
        autotools.make('clean', args=['-f', 'simple_makefile.mk'])

    def package(self):
        for lib in ('*.a', '*.so'):
            copy(self, lib,
                 self.build_folder,
                 os.path.join(self.package_folder, 'lib'))
        copy(self, '*.h',
             os.path.join(self.source_folder, 'include'),
             os.path.join(self.package_folder, 'include', self.name))
        copy(self, 'README.md',
             os.path.join(self.source_folder, 'src'),
             self.package_folder)

    def package_info(self):
        self.cpp_info.libs = ['ubloxcfg']
