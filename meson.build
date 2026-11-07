# Meson build file with test support
# Based on SFML 2.5

project('Naruto-Pixel-Burst', 'cpp')

# Set C++ standard
cpp_std = 'c++17'

# Find SFML
sfml = dependency('sfml-graphics', version: '>=2.5')
sfml_audio = dependency('sfml-audio', version: '>=2.5')
sfml_window = dependency('sfml-window', version: '>=2.5')
sfml_system = dependency('sfml-system', version: '>=2.5')

# Define source files
sources = [
    'Collision.cpp',
    'Little_Physics_Engine.cpp',
    'frameanimation.cpp',
    'globales.cpp',
    'main.cpp',
    'personnage.cpp',
    'settings.cpp'
]

# Define headers
headers = [
    'Collision.h',
    'Little_Physics_Engine.h',
    'frameanimation.h',
    'personnage.h',
    'settings.h'
]

# Create executable
executable('Naruto-Pixel-Burst',
    sources,
    headers,
    dependencies: [sfml, sfml_audio, sfml_window, sfml_system],
    cpp_args: ['-Wall', '-Wextra', '-O2'],
    install: true
)

# Create test executable
test_exe = executable('tests',
    'test_frameanimation.cpp',
    'test_settings.cpp',
    'test_personnage.cpp',
    'test_physics.cpp',
    'catch.hpp',
    dependencies: [sfml, sfml_audio, sfml_window, sfml_system],
    cpp_args: ['-Wall', '-Wextra', '-O2']
)

# Add tests
test('frameanimation', test_exe, args: ['--success'])
test('settings', test_exe, args: ['--success'])
test('personnage', test_exe, args: ['--success'])