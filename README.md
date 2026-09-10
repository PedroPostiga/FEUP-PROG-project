# Scrim Scripting & C++ Image Processing Toolset

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Build Status](https://img.shields.io/badge/build-CMake-brightgreen.svg)](https://cmake.org/)

A powerful, command-driven image processing engine built in C++17. The project parses and executes **Scrim** (`.scrim`) scripting files, performing a sequence of high-performance image transformations (such as mirroring, scaling, rotation, cropping, sliding, color replacement, and composition/overlays) on PNG images. It includes a custom PNG file format driver, a comprehensive test suite executor, and a pipeline chain processor.

---

## 🚀 Key Features

* **Custom Scripting Language**: Parse and execute `.scrim` pipelines to automate advanced sequential image transformations.
* **Command Pattern Architecture**: Easily extendable and clean design, decoupling command parsing from rendering execution.
* **Extensive Image Filters & Utilities**:
  * Canvas Generation & I/O (`blank`, `open`, `save`)
  * Color Manipulations (`invert`, `to_gray_scale`, `replace`)
  * Spatial Transforms (`h_mirror`, `v_mirror`, `move`, `slide`, `crop`, `resize`, `rotate_left`, `rotate_right`, `scaleup`)
  * Advanced Compositing (`add` overlays with custom key transparency, `chain` sequential script files)
* **CMake Build Pipeline**: Platform-independent configuration featuring active compiler sanitization (ASan and UBSan) under UNIX-like OS configurations to ensure memory safety.
* **Integrated Test Suite Driver**: Auto-validates output pixel matrices against expected baseline PNG configurations and provides clean logging tools.
* **Custom Delivery Archiver**: Generates ready-to-deploy zip deliverables automatically using standard CMake custom targets.

---

## 📂 Directory Structure

```text
├── CMakeLists.txt              # Build configuration & targets (runscrim, tester, delivery)
├── include/                     # C++ header files
│   ├── Color.hpp                # RGB Color representation
│   ├── Image.hpp                # 2D Color matrix image canvas
│   ├── Command.hpp              # Abstract base class for the command pattern
│   ├── Scrim.hpp                # Pipeline pipeline execution container
│   ├── ScrimParser.hpp          # Script tokenizer and command builder
│   ├── PNG.hpp                  # PNG encoder / decoder hooks
│   ├── Utils.h                  # File system and directory utilities
│   ├── Logger.hpp               # Custom diagnostic logging channels
│   ├── stb/                     # stb_image & stb_image_write single-header third-party code
│   └── Command/                 # Individual command subclass definitions
│       ├── Blank.hpp, Open.hpp, Save.hpp, ...
├── src/                         # C++ source file implementations
│   ├── Color.cpp, Image.cpp, Scrim.cpp, ScrimParser.cpp, PNG.cpp, Utils.cpp
│   └── Command/                 # Individual command algorithm implementations
│       ├── invert.cpp, rotate_right.cpp, crop.cpp, ...
├── main/                        # Entry points
│   ├── RunScrim.cpp             # Main executable for running scrim pipelines
│   └── Tester.cpp               # Test runner and validation framework
├── scrims/                      # Scrim script test suite (.scrim files)
├── expected/                    # Baseline PNG files for testing
├── input/                       # Source asset PNGs used in script commands
└── output/                      # Generated output PNG directory
```

---

## 🛠️ Compilation and Building

This project utilizes [CMake](https://cmake.org/) (minimum version 3.15) and requires a C++17 compatible compiler (such as GCC 9+, Clang 10+, or MSVC 2019+).

### Standard Build Steps

From the project root directory, run the following commands:

```bash
# 1. Create and enter a build directory
mkdir build
cd build

# 2. Configure the project
cmake ..

# 3. Compile the binaries
cmake --build .
```

### Compiler Optimization & Selection
To select a specific compiler (e.g., Clang), configure with:
```bash
cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

> [!NOTE]
> On Non-Windows operating systems, compilation automatically injects `-fsanitize=address` (ASan) and `-fsanitize=undefined` (UBSan) flags to trace memory safety issues.

---

## ⚡ Running the Executables

The build process produces two major target executables: `runscrim` and `tester`.

### 1. Running Scrim Scripts (`runscrim`)
To run one or multiple Scrim pipelines, pass the paths to the `.scrim` files as command-line arguments:

```bash
./runscrim ../scrims/basic_blank1.scrim ../scrims/invert1.scrim
```

### 2. Running Verification Tests (`tester`)
The test runner compares generated script outputs in `output/` with gold standard templates inside `expected/`.

```bash
# Run all tests in the 'scrims' directory matching all script configurations
./tester

# Run only test scripts matching a specific filter pattern (e.g., all crop tests)
./tester crop

# Run the raw C++ color class unit assertions
./tester Color
```

---

## 📜 Scrim Script Syntax Reference

Each script contains a space-separated sequence of commands. Colors are represented as integer RGB triplets: `R G B` (each ranging from `0` to `255`). Rectangles are defined by their top-left coordinate `(x, y)`, followed by `width` and `height`.

### Base Actions

| Command | Arguments | Description | Example |
| :--- | :--- | :--- | :--- |
| `blank` | `<w> <h> <R> <G> <B>` | Instantiates a new blank canvas with the given dimensions and background color. | `blank 300 200 255 0 0` (Red Canvas) |
| `open` | `<filename>` | Loads the image from the specified PNG file path. | `open input/cat.png` |
| `save` | `<filename>` | Encodes and exports the current state of the image to the specified PNG file. | `save output/result.png` |

---

### Image Manipulations

| Command | Arguments | Description | Example |
| :--- | :--- | :--- | :--- |
| `invert` | *None* | Inverts the color channels of all pixels (e.g., $R_{new} = 255 - R$). | `invert` |
| `to_gray_scale` | *None* | Converts the current image canvas to grayscale. | `to_gray_scale` |
| `replace` | `<R1> <G1> <B1> <R2> <G2> <B2>` | Replaces every pixel of exact color `R1 G1 B1` with `R2 G2 B2`. | `replace 0 0 0 255 255 255` (Black to White) |
| `fill` | `<x> <y> <w> <h> <R> <G> <B>` | Draws a filled rectangle of color `R G B` at coordinate `(x, y)` with dimensions `w` and `h`. | `fill 50 50 100 100 0 255 0` |
| `h_mirror` | *None* | Mirrers the canvas horizontally. | `h_mirror` |
| `v_mirror` | *None* | Mirrers the canvas vertically. | `v_mirror` |
| `move` | `<x> <y>` | Translates the canvas by shifting coordinates by `(x, y)`. | `move 20 -10` |
| `slide` | `<x> <y>` | Translates the image by `(x, y)` with a toroidal wrap-around (sliding off the edge wraps to the other side). | `slide 50 50` |
| `crop` | `<x> <y> <w> <h>` | Clips the canvas to the specified sub-rectangle. | `crop 0 0 100 100` |
| `resize` | `<x> <y> <w> <h>` | Resizes canvas bounds to `w x h` offsets, preserving source elements from `(x, y)`. Out-of-bounds fills with the canvas default. | `resize 0 0 800 600` |
| `rotate_left` | *None* | Rotates the image 90 degrees counter-clockwise. | `rotate_left` |
| `rotate_right` | *None* | Rotates the image 90 degrees clockwise. | `rotate_right` |
| `scaleup` | `<factor_x> <factor_y>` | Scales up the image by replicating pixels (nearest-neighbor) by the given horizontal and vertical integer factors. | `scaleup 2 2` |
| `add` | `<filename> <nR> <nG> <nB> <x> <y>` | Overlays a PNG image onto the canvas at `(x, y)`. Pixels matching the neutral/key color `nR nG nB` are ignored (transparent). | `add input/logo.png 255 255 255 10 10` |
| `chain` | `<file1> <file2> ... end` | Sequentially injects commands parsed from other `.scrim` pipelines into the current pipeline. | `chain scrims/part1.scrim end` |

---

## 📝 Example Scripts

### 1. Generating a Flag Image (`flag.scrim`)
Creates a `300x300` red canvas, paints a green block, overlays a blue block, and saves:
```text
blank 300 300 255 0 0
fill 0 0 200 100 0 255 0
fill 0 0 20 30 0 0 255
save output/flag.png
```

### 2. Processing an Image with Translucent Overlays (`overlay.scrim`)
Loads a background, rotates it, applies a watermark image by filtering out white backgrounds, and exports:
```text
open input/scenery.png
rotate_right
add input/watermark.png 255 255 255 20 20
save output/watermark_result.png
```

---

## 📦 Creating Deliverable Archive

To package the source and header structures into a clean zip distribution file (configured under `delivery.zip` in your build environment):

```bash
cmake --build . --target delivery
```

This commands automatically gathers target files and bundles them into `build/delivery.zip`.

---

## 👥 Contributors

* **Filipe Carvalho Cruz (@filipecruz06)**
* **Pedro Fernandes Postiga (@PedroPostiga)**
* **Vasco Manuel Fernandes Guimarães (@VascoGuimaraes)**
