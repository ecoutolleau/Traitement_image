#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pnm.h>

#include "domain.h"


void 
process(int x, int y, int angle, char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(cols, rows, PnmRawPpm);

  float cosAng = cosf(angle*pi/180.0);
  float sinAng = sinf(angle*pi/180.0);
  
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){

      float xIP = (float)j * cosAng - (float)i * sinAng + (float)x * (1-cosAng) + (float)y * sinAng;
      float yIP = (float)j * sinAng + (float)i * cosAng - (float)x * sinAng + (float)y * (1-cosAng);

      for (int k = 0; k < 3; k++){
	unsigned short c = bilinear_interpolation(xIP,yIP,ims2,k);
	pnm_set_component(imd2, i, j, k, c);
      }
    }
  }
  
  pnm_save(imd2, PnmRawPpm, imd);
  free(imd2);
  free(ims2);
}


static void usage(char* s){
  fprintf(stderr,"%s <x> <y> <angle> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 5
int main(int argc, char* argv[]){
  if(argc != PARAM+1) 
    usage(argv[0]);
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  float angle = atoi(argv[3]);
  char *ims = argv[4];
  char *imd = argv[5];
  process(x, y, angle, ims, imd);
  return EXIT_SUCCESS;
}
