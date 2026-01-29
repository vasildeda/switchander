# Swichander

A JUCE application project.

## Setup

1. Clone or download JUCE framework and place it in a `JUCE` subdirectory, or use git submodule:
   ```bash
   git submodule add https://github.com/juce-framework/JUCE.git JUCE
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure with CMake:
   ```bash
   cmake ..
   ```

4. Build:
   ```bash
   cmake --build .
   ```

## Project Structure

- `Source/` - Source code files
- `Assets/` - Resources (icons, etc.)
- `CMakeLists.txt` - CMake configuration
- `JUCE/` - JUCE framework (git submodule or manually added)
