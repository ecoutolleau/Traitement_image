#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pnm.h>

#include "domain.h"


void 
process(float tx, float ax, float ty, float ay, char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(cols, rows, PnmRawPpm);
  
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){

      float x = j + ax * sinf(2*pi*i/tx);
      float y = i + ay * sinf(2*pi*j/ty);

      for (int k = 0; k < 3; k++){
	unsigned short c = bilinear_interpolation((int)x,(int)y,ims2,k);
	pnm_set_component(imd2, i, j, k, c);
      }
    }
  }
  
  pnm_save(imd2, PnmRawPpm, imd);
  free(imd2);
  free(ims2);
}


static void usage(char* s){
  fprintf(stderr,"%s <tx> <ax> <ty> <ay> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 6
int main(int argc, char* argv[]){
  if(argc != PARAM+1) 
    usage(argv[0]);
  float tx = atoi(argv[1]);
  float ax = atoi(argv[2]);
  float ty = atoi(argv[3]);
  float ay = atoi(argv[4]);
  char *ims = argv[5];
  char *imd = argv[6];
  process(tx, ax, ty, ay, ims, imd);
  return EXIT_SUCCESS;
}
