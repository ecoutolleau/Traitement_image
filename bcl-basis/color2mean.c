#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process(char *ims, char *imd){
  pnm imd2 = pnm_load(ims);
  int rows = pnm_get_height(imd2);
  int cols = pnm_get_width(imd2);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      unsigned short r = pnm_get_component(imd2, i, j, PnmRed);
      unsigned short g = pnm_get_component(imd2, i, j, PnmGreen);
      unsigned short b = pnm_get_component(imd2, i, j, PnmBlue);
      unsigned short moy = (r+g+b)/3;
      pnm_set_component(imd2, i, j, PnmRed, moy);
      pnm_set_component(imd2, i, j, PnmGreen, moy);
      pnm_set_component(imd2, i, j, PnmBlue, moy);
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 2
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  char *ims = argv[1];
  char *imd = argv[2];
  process(ims, imd);
  return EXIT_SUCCESS;
}
