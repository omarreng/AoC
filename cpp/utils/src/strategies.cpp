#include "strategies.h"

void N(int &ix, int &iy)
{
  ix--;
}

void NE(int &ix, int &iy)
{
  ix--;
  iy++;
}

void E(int &ix, int &iy)
{
  iy++;
}

void SE(int &ix, int &iy)
{
  ix++;
  iy++;
}

void S(int &ix, int &iy)
{
  ix++;
}

void SW(int &ix, int &iy)
{
  ix++;
  iy--;
}

void W(int &ix, int &iy)
{
  iy--;
}

void NW(int &ix, int &iy)
{
  ix--;
  iy--;
}

size_t ADD(size_t ix, size_t iy)
{
  return ix + iy;
}

size_t MUL(size_t ix, size_t iy)
{
  return ix * iy;
}

size_t CONCAT(size_t ix, size_t iy)
{
  return stoll(to_string(ix) + to_string(iy));
}