#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

unsigned short min(unsigned short a, unsigned short b) {
    return a<b ? a : b;
}

unsigned short max(unsigned short a, unsigned short b) {
    return a>b ? a : b;
}

void process(int Min, int Max, char *ims, char *imd){
  pnm imd2 = pnm_load(ims);
  int rows = pnm_get_height(imd2);
  int cols = pnm_get_width(imd2);
  unsigned short minIR = 255;
  unsigned short minIG = 255;
  unsigned short minIB = 255;
  unsigned short maxIR = 0;
  unsigned short maxIG = 0;
  unsigned short maxIB = 0;
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      unsigned short r = pnm_get_component(imd2, i, j, PnmRed);
      unsigned short g = pnm_get_component(imd2, i, j, PnmGreen);
      unsigned short b = pnm_get_component(imd2, i, j, PnmBlue);
      minIR = min(minIR, r);
      minIG = min(minIG, g);
      minIB = min(minIB, b);
      maxIR = max(maxIR, r);
      maxIG = max(maxIG, g);
      maxIB = max(maxIB, b);
    }
  }
  /*  unsigned short q1R = (Max-Min)/(maxIR-minIR);
  unsigned short q1G = (Max-Min)/(maxIG-minIG);
  unsigned short q1B = (Max-Min)/(maxIB-minIB);
  unsigned short q2R = (Min*maxIR - Max*minIR)/(maxIR-minIR);
  unsigned short q2G = (Min*maxIG - Max*minIG)/(maxIG-minIG);
  unsigned short q2B = (Min*maxIB - Max*minIB)/(maxIB-minIB);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      unsigned short r = pnm_get_component(imd2, i, j, PnmRed);
      unsigned short g = pnm_get_component(imd2, i, j, PnmGreen);
      unsigned short b = pnm_get_component(imd2, i, j, PnmBlue);
      pnm_set_component(imd2,i,j,PnmRed, q1R*r+q2R);
      pnm_set_component(imd2,i,j,PnmGreen, q1G*g+q2G);
      pnm_set_component(imd2,i,j,PnmBlue, q1B*b+q2B);
    }
    }*/
  float q1R = ((float)Max-(float)Min)/((float)maxIR-(float)minIR);
  float q1G = ((float)Max-(float)Min)/((float)maxIG-(float)minIG);
  float q1B = ((float)Max-(float)Min)/((float)maxIB-(float)minIB);
  float q2R = ((float)Min*(float)maxIR - (float)Max*(float)minIR)/((float)maxIR-(float)minIR);
  float q2G = ((float)Min*(float)maxIG - (float)Max*(float)minIG)/((float)maxIG-(float)minIG);
  float q2B = ((float)Min*(float)maxIB - (float)Max*(float)minIB)/((float)maxIB-(float)minIB);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      unsigned short r = pnm_get_component(imd2, i, j, PnmRed);
      unsigned short g = pnm_get_component(imd2, i, j, PnmGreen);
      unsigned short b = pnm_get_component(imd2, i, j, PnmBlue);
      pnm_set_component(imd2,i,j,PnmRed, q1R*(float)r+q2R);
      pnm_set_component(imd2,i,j,PnmGreen, q1G*(float)g+q2G);
      pnm_set_component(imd2,i,j,PnmBlue, q1B*(float)b+q2B);
    }
  }   
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<min> <max> <ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  int Min = atoi(argv[1]);
  int Max = atoi(argv[2]);
  char *ims = argv[3];
  char *imd = argv[4];
  process(Min, Max, ims, imd);
  return EXIT_SUCCESS;
}
