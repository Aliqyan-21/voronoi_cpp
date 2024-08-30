#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>

const int Width = 800, Height = 600;

const int Seeds_count = 10;

uint32_t image[Height][Width];

#define BACKGROUND_COLOR 0xFF121212
#define SEED_MARKER_RADIUS 5
#define SEED_MARKER_COLOR 0xFF121212

// pallete colors
#define flamingo 0xFFFCCDD2
#define mauve 0xFFCFA67B
#define red 0xFFFA8B83
#define maroon 0xFFEAA0CB
#define peach 0xFFF8B37A
#define yellow 0xFFFAE2F9
#define green 0xFFAAE316
#define teal 0xFF9DE254
#define sky 0xFF8EDCB9
#define sapphire 0xFF7EC7C4
#define blue 0xFF8FB4A9
#define lavender 0xFFBFBEE4
#define apricot 0xFF0B64FE

struct Point {
  int x, y;
};

Point seeds[Seeds_count];
uint32_t pallete[] = {
    flamingo, mauve, red, maroon, peach, yellow, green, teal, sky, apricot,
};
const int pallete_size = sizeof(pallete) / sizeof(pallete[0]);

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

int sqrt_dist(int x1, int y1, int x2, int y2) {
  int dx = x1 - x2;
  int dy = y1 - y2;
  return dx * dx + dy * dy;
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
          if (sqrt_dist(cx, cy, i, j) <= radius * radius)
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

void render_seed_markers() {
  for (int i = 0; i < Seeds_count; i++) {
    fill_cicle(seeds[i].x, seeds[i].y, SEED_MARKER_RADIUS, SEED_MARKER_COLOR);
  }
}

void render_voronoi() {
  for (int y = 0; y < Height; y++) {
    for (int x = 0; x < Width; x++) {
      int j = 0;
      for (int i = 1; i < Seeds_count; i++) {
        if (sqrt_dist(seeds[i].x, seeds[i].y, x, y) <
            sqrt_dist(seeds[j].x, seeds[j].y, x, y)) {
          j = i;
        }
      }
      image[y][x] = pallete[j % pallete_size];
    }
  }
}

int main(void) {
  srand(time(0));
  fill_image(BACKGROUND_COLOR); // aa bb gg rr --> 0xFF0000FF --> color_red
  generate_random_seeds();
  render_voronoi();
  render_seed_markers();
  save_image_ppm("output.ppm");

  return 0;
}
