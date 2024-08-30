#include <cstdint>

#define Width 800
#define Height 800

static uint32_t image[Height][Width];

void fill_image() {}

int main(void) {
  // aa bb gg rr --> 0xFFFF00FF;
  fill_image();
  return 0;
}
