# Naruto-Pixel-burst

My first 2D game using Naruto's sprites and songs. It is coded in C++ with SFML 2.5.

## Features

- 2D arcade-style fighting game with pixel art sprites
- Character selection system
- Multiple arenas with parallax backgrounds
- Particle effects for attacks and special moves
- 3D effects for attacks and special moves
- Combat system with multiple character abilities

## Build Instructions

### Prerequisites

- C++17 compiler
- SFML 2.5
- Meson build system
- Ninja build system

### Building

```bash
meson setup build --buildtype=release
meson compile -C build
```

### Testing

```bash
meson test -C build
```

## Project Structure

- `main.cpp` - Main game loop and initialization
- `personnage.h/cpp` - Core character class with animation system
- `frameanimation.h/cpp` - Animation handling system
- `settings.h/cpp` - Input handling system
- `Collision.h/cpp` - Collision detection system
- `character_selection.h/cpp` - Character selection system
- `arena.h/cpp` - Arena system with parallax backgrounds
- `particle_system.h/cpp` - Particle effects system
- `3d_effects.h/cpp` - 3D effects system
- `assets/` - Directory containing all game assets (sprites, backgrounds, sounds, fonts)

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Create a new Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.