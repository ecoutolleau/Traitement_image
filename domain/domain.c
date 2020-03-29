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

  if (i>= 0 && j >= 0 && i < rows && j < cols) {
    m1 = pnm_get_component(ims, i, j, c);
    if (j + 1 < cols) m2 = pnm_get_component(ims, i, j+1, c);
    if (i + 1 < rows) m3 = pnm_get_component(ims, i+1, j, c);
    if (i + 1 < rows && j + 1 < cols) m4 = pnm_get_component(ims, i+1, j+1, c);
  }
  
  res = (1-dx)*(1-dy)*m1 + dx*(1-dy)*m2 + (1-dx)*dy*m3 + dx*dy*m4;
  return res;
}


/*
#include <math.h>

#include "domain.h"


enum Case {
    Normal = 0, Right, Left, Up, Bottom, Corner_UR, Corner_UL, Corner_BR, Corner_BL, Outside
};


// Are ij, iij, ijj and iijj in the image
int points_in_image(int i, int j, int rows, int cols){
    return (0 <= i) && (i + 1 < rows) && (0 <= j) && (j + 1 < cols);
}

int points_all_outside(int i, int j, int rows, int cols){
    return (i+1 < 0) || (rows <= i) || (j+1 < 0) || (cols <= j);
}

enum Case compute_case(int i, int j, int rows, int cols){
    if(points_in_image(i, j, rows, cols)) return Normal;
    if(points_all_outside(i, j, rows, cols)) return Outside;

    if(i+1 == 0) {
        if(j+1 == 0) return Corner_BR;
        if(j+1 == cols) return Corner_BL;
        return Bottom;

    } else if(i+1 == rows) {
        if(j+1 == 0) return Corner_UR;
        if(j+1 == cols) return Corner_UL;
        return Up;
    } else {
        if(j+1 == 0) return Right;
        return Left;
    }
}


float
get_component_custom(pnm self, int i, int j, pnmChannel channel)
{
    if(i < 0 || j < 0) return 0;

    int rows = pnm_get_height(self);
    int cols = pnm_get_width(self);
    if(i >= rows || j >= cols) return 0;

    return pnm_get_component(self, i, j, channel);;
}


unsigned short 
bilinear_interpolation(float x, float y, pnm ims, int c)
{
    int i = (int) y;
    int j = (int) x;

    float Iij = get_component_custom(ims, i, j, c);
    float Iijj = get_component_custom(ims, i, j + 1, c);
    float Iiij = get_component_custom(ims, i + 1, j, c);
    float Iiijj = get_component_custom(ims, i + 1, j + 1, c);

    int cols = pnm_get_width(ims);
    int rows = pnm_get_height(ims);

    float dx = x - (float) j;
    float dy = y - (float) i;
    
    switch (compute_case(i, j, rows, cols))
    {
        //Normal = 0, Right, Left, Up, Bottom, Corner_UR, Corner_UL, Corner_BR, Corner_BL, Outside
        case Normal:
            return (1 - dx)*(1 - dy)*Iij + dx*(1 - dy)*Iijj + (1 - dx)*dy*Iiij + dx*dy*Iiijj;

        case Right:
            return (1 - dy)*Iijj + dy*Iiijj;
            
        case Left:
            return (1 - dy)*Iij + dy*Iiij;
            
        case Up:
            return (1 -dx)*Iij + dx*Iijj;
            
        case Bottom:
            return (1 -dx)*Iiij + dx*Iiijj;
            
        case Corner_UR:
            return Iijj;

        case Corner_UL:
            return Iij;

        case Corner_BR:
            return Iiijj;

        case Corner_BL:
            return Iiij;

        case Outside:
        default:
            return 0;
    }
    
}
*/
