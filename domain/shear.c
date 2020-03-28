#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pnm.h>

#include "domain.h"


void
horizontal(float angle, char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);

  float tanAng = tanf(angle*pi/180.0);
  
  float decal = fabsf(tanAng) * (float)rows;

  int cols2 = cols + (int)decal + 1;
  pnm imd2 = pnm_new(cols2, rows, PnmRawPpm);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols2; j++) {

      float x,y;
      if(angle>0) {
	x = - (float)i * tanAng + (float)j;
	y = i;
      } else {
	x = (rows-(float)i) * tanAng + (float)j;
	y = i;
      }
      
      for (int k = 0; k < 3; k++) {
	unsigned short c = bilinear_interpolation(x, y, ims2, k);
	pnm_set_component(imd2, i, j, k, c);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}


void
vertical(float angle, char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);

  float tanAng = tanf(angle*pi/180.0);
  
  float decal = fabs(tanAng) * (float)cols;

  int rows2 = rows + (int)decal + 1;
  pnm imd2 = pnm_new(cols, rows2, PnmRawPpm);

  for (int i = 0; i < rows2; i++) {
    for (int j = 0; j < cols; j++) {

      float x,y;
      if (angle>0){
	x = (float)j;
	y = (float)i - (float)j *tanAng;
      }else{
	x = (float)j;
	y = (float)i + ((float)cols-(float)j)*tanAng;
      }
      for (int k = 0; k < 3; k++) {
	unsigned short c = bilinear_interpolation(x, y, ims2, k);
	pnm_set_component(imd2, i, j, k, c);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}


void 
process(char *dir, float angle, char* ims, char* imd)
{
  switch(dir[0]){
  case 'h':
    horizontal(angle, ims, imd);
    break;
  case 'v':
    vertical(angle, ims, imd);
    break; 
  }
}


static void usage(char* s){
  fprintf(stderr,"%s <dir>{h ,v} <angle> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int main(int argc, char* argv[]){
  if(argc != PARAM+1) 
    usage(argv[0]);
  char *dir = argv[1];
  float angle = atoi(argv[2]);
  char *ims = argv[3];
  char *imd = argv[4];
  process(dir, angle, ims, imd);
  return EXIT_SUCCESS;
}
