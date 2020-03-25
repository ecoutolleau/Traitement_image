#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process(char *ims, char *imd, const size_t rows, const size_t cols, size_t i, size_t j){
  pnm ims2 = pnm_load(ims);
  pnm imd2 = pnm_new(cols, rows, PnmRawPpm);
  for (size_t k = 0; k < rows; k++){
    for (size_t l = 0; l < cols; l++){
      for (size_t m = 0; m < 3; m++){
	const unsigned short val = pnm_get_component(ims2, i+k, j+l, m);
	pnm_set_component(imd2, k, l, m, val);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(ims2);
  pnm_free(imd2);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<i> <j> <rows> <cols> <ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 6
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  size_t i = atoi(argv[1]);
  size_t j = atoi(argv[2]);
  size_t rows = atoi(argv[3]);
  size_t cols = atoi(argv[4]);
  char *ims = argv[5];
  char *imd = argv[6];
  process(ims, imd, rows, cols, i, j);
  return EXIT_SUCCESS;
}
