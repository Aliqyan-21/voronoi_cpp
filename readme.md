## Voronoi Diagram Generator

This project generates a Voronoi diagram using randomly placed seeds on a 2D plane. The diagram is rendered as an image in the PPM format, where each pixel is colored based on its proximity to the nearest seed.

![sample](https://github.com/user-attachments/assets/28a9377d-3cee-4d50-93df-1b6610ca0e1d)

### Features

- **Voronoi Diagram Rendering:** Generates a Voronoi diagram with a specified number of seeds.
- **Seed Marker Rendering:** Highlights the seed positions with a distinct color.
- **Custom Color Palette:** Uses a predefined set of colors to differentiate regions in the Voronoi diagram.
- **C++ Implementation:** Written in C++ with a focus on simplicity and performance.
- **PPM Image Output:** Outputs the generated Voronoi diagram as a .ppm image file.

### Requirements

- C++ compiler (e.g. g++)
- CMake (version 3.28.2 or higher)

### Build Instructions

1. Clone the repo

```bash
git clone https://github.com/aliqyan-21/voronoi_cpp.git
cd voronoi
```

2. Run Cmake

```bash
cmake -Bbuild
```

```bash
cmake --build build
```

3. Run the executable

```bash
./build/main
```

### How It Works

The program generates a Voronoi diagram by following these steps:

1. **Initialization:** The image is filled with a background color.
2. **Seed Generation:** Seeds are placed randomly across the image.
3. **Voronoi Rendering:** Each pixel is assigned a color based on the nearest seed using a distance formula.
4. **Seed Marking:** Small circles are drawn around the seed positions to highlight them.
5. **Image Saving:** The final image is saved in PPM format.

### Example Output

Running the program will generate an `output.ppm` file, which you can open with any image viewer that supports the PPM format.
