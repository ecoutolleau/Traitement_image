#include <math.h>

#include <domain.h>

unsigned short 
bilinear_interpolation(float x, float y, pnm ims, int c)
{
  unsigned short res;
  int i = floor(y);
  int j = floor(x);
  float dx = x - (float)j;
  float dy = y - (float)i;
  unsigned short m1 = 0;
  unsigned short m2 = 0;
  unsigned short m3 = 0;
  unsigned short m4 = 0;
  int rows = pnm_get_height(ims);
  int cols = pnm_get_width(ims); 
  m1 = pnm_get_component(ims, i, j, c);
  if (j < cols) m2 = pnm_get_component(ims, i, j+1, c);
  if (i < rows) m3 = pnm_get_component(ims, i+1, j, c);
  if (i < rows && j < cols) m4 = pnm_get_component(ims, i+1, j+1, c);
  res = (1-dx)*(1-dy)*m1 + dx*(1-dy)*m2 + (1-dx)*dy*m3 + dx*dy*m4;
  return res;
}

