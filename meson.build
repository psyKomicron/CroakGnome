project('CroakGnome', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20'
  ])

gnome = import('gnome')

dependencies = dependency('gtkmm-4.0')

config = configuration_data()
config.set_quoted('PACKAGE_VERSION', meson.project_version())
config.set_quoted('PACKAGE_NAME', meson.project_name())

configure_file(output: 'config.h', configuration: config)

subdir('src')