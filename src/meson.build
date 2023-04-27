sources = [
    'croakgnome.cpp',
    'ui/App.cpp',
    'ui/MainWindow.cpp',
    'common/AudioController.cpp'
]

resources = gnome.compile_resources('resources',
  '../data/croakgnome.gresource.xml',
  source_dir: '../data',
  c_name: 'croakgnome'
)

exe = executable('croak', 
  sources + resources,
  dependencies: dependencies,
  install : true
)
