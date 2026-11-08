project('Naruto-Pixel-burst', 'cpp',
  version : '1.0',
  default_options : ['cpp_std=c++17'])

# Dependencies
# Try to find SFML manually
sfml_dep = [dependency('sfml-graphics'), dependency('sfml-window'), dependency('sfml-system')]

# Source files
sources = [
  'Collision.cpp',
  'Little_Physics_Engine.cpp',
  'frameanimation.cpp',
  'globales.cpp',
  'personnage.cpp',
  'settings.cpp',
  'main.cpp'
]

# Executable
executable('Naruto-Pixel-burst',
  sources,
  dependencies : sfml_dep,
  install : true
)

# Test executable
gtest_dep = dependency('gtest', required : false)
if gtest_dep.found()
  test_sources = [
    'test/test_main.cpp',
    'test/frameanimation_test.cpp',
    'test/personnage_test.cpp'
  ]
  
  executable('test_runner',
    test_sources,
    dependencies : [sfml_dep, gtest_dep],
    install : false
  )
  
  test('all_tests', 'test_runner')
endif