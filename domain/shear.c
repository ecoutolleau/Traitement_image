#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pnm.h>

//#include "domain.h"

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



void
horizontal(int angle, char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  float decal = tan(angle) * rows;
  int decalEnt = (int)decal;
  int cols2 = cols + decalEnt;
  pnm imd2 = pnm_new(cols2, rows, PnmRawPpm);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < 3; k++) {
	float x = i * tan(angle) + j;
	float y = i;
	unsigned short c = bilinear_interpolation(x, y, ims2, k);
	pnm_set_component(imd2, i, (int)x, k, c);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}


void 
process(char *dir, int angle, char* ims, char* imd)
{
  switch(dir[0]){
  case 'h':
    horizontal(angle, ims, imd);
    break;
/*  case 'v':
    vertical(angle, ims, imd);
    break; */
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
  int angle = atoi(argv[2]);
  char *ims = argv[3];
  char *imd = argv[4];
  process(dir, angle, ims, imd);
  return EXIT_SUCCESS;
}
