#include <cstdint>
#include <fstream>
#include <iostream>

const int Width = 800, Height = 600;

static uint32_t image[Height][Width];

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
  f << "P6\n" << Width << " " << Height << "\n255\n";

  for (int i = 0; i < Height; i++) {
    for (int j = 0; j < Width; j++) {
      uint32_t pixel = image[i][j];
      uint8_t bytes[3] = {static_cast<uint8_t>((pixel & 0x0000FF) >> 8 * 0),
                          static_cast<uint8_t>((pixel & 0x00FF00) >> 8 * 1),
                          static_cast<uint8_t>((pixel & 0xFF0000) >> 8 * 2)};
      f.write(reinterpret_cast<char *>(bytes), sizeof(bytes));
    }
  }

  f.close();
}

int main(void) {
  // aa bb gg rr --> 0xFF0000FF --> color_red
  fill_image(0xFF0000FF);
  save_image_ppm("output.ppm");
  return 0;
}
