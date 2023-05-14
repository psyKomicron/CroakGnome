project('CroakGnome', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20'
  ])

add_global_arguments('-Werror=return-type', language: 'cpp')

gnome = import('gnome')

gtkmm_dep = dependency('gtkmm-4.0')
pipewire_dep = dependency('libpipewire-0.3')
fmt_dep = dependency('fmt')

dependencies = [
  gtkmm_dep,
  pipewire_dep,
  fmt_dep
]

config = configuration_data()
config.set_quoted('PACKAGE_VERSION', meson.project_version())
config.set_quoted('PACKAGE_NAME', meson.project_name())

configure_file(output: 'config.h', configuration: config)

subdir('src')