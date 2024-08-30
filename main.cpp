#include <cstdint>
#include <fstream>
#include <iostream>

const int Width = 800, Height = 600;

const int Seeds_count = 10;

uint32_t image[Height][Width];

#define BACKGROUND_COLOR 0xFF121212
#define SEED_MARKER_RADIUS 5
#define SEED_MARKER_COLOR 0xFFFFFFFF

struct Point {
  int x, y;
};

Point seeds[Seeds_count];

void fill_image(uint32_t color) {
  for (int i = 0; i < Height; i++) {
    for (int j = 0; j < Width; j++) {
      image[i][j] = color;
    }
  }
}

void save_image_ppm(const std::string &filePath) {
  std::ofstream f(filePath, std::ios::binary);

  if (!f) {
    std::cerr << "Error: could not open file " << filePath << std::endl;
    return;
  }

  // header file
  f << "P6\n" << Width << " " << Height << "\n255\n";

  for (int i = 0; i < Height; i++) {
    for (int j = 0; j < Width; j++) {
      uint32_t pixel = image[i][j];
      // masking and taking individual r, g and b colors
      uint8_t bytes[3] = {static_cast<uint8_t>((pixel & 0x0000FF) >> 8 * 0),
                          static_cast<uint8_t>((pixel & 0x00FF00) >> 8 * 1),
                          static_cast<uint8_t>((pixel & 0xFF0000) >> 8 * 2)};
      // writing the pixels in file
      f.write(reinterpret_cast<char *>(bytes), sizeof(bytes));
    }
  }

  f.close();
}

void fill_cicle(int cx, int cy, int radius, uint32_t color) {
  int x0 = cx - radius;
  int y0 = cy - radius;
  int x1 = cx + radius;
  int y1 = cy + radius;

  for (int i = x0; i <= x1; i++) {
    if (i >= 0 && i < Width) {
      for (int j = y0; j <= y1; j++) {
        if (j >= 0 && j < Height) {
          int dx = cx - i;
          int dy = cy - j;

          if (dx * dx + dy * dy <= radius * radius)
            image[j][i] = color;
        }
      }
    }
  }
}

void generate_random_seeds() {
  for (int i = 0; i < Seeds_count; i++) {
    seeds[i].x = rand() % Width;
    seeds[i].y = rand() % Height;
  }
}

int main(void) {
  // aa bb gg rr --> 0xFF0000FF --> color_red
  fill_image(BACKGROUND_COLOR);

  generate_random_seeds();

  for (int i = 0; i < Seeds_count; i++) {
    fill_cicle(seeds[i].x, seeds[i].y, SEED_MARKER_RADIUS, SEED_MARKER_COLOR);
  }

  save_image_ppm("output.ppm");

  return 0;
}
