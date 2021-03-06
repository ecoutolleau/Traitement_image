#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>

void 
process(int dx, int dy, char* ims_name, char* imd_name)
{
  pnm ims2 = pnm_load(ims_name);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm ims = pnm_new(cols, rows, PnmRawPpm);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i+dy >= 0 && i+dy < rows && j+dx >= 0 && j+dx > 0) {
	unsigned short imsRed = pnm_get_component(ims2, i, j, PnmRed);
	unsigned short imsGreen = pnm_get_component(ims2, i, j, PnmGreen);
	unsigned short imsBlue = pnm_get_component(ims2, i, j, PnmBlue);
	pnm_set_component(ims, i+dy, j+dx, PnmRed, imsRed);
	pnm_set_component(ims, i+dy, j+dx, PnmGreen, imsGreen);
	pnm_set_component(ims, i+dy, j+dx, PnmBlue, imsBlue);
      }
    }
  }
  pnm_save(ims, PnmRawPpm, imd_name);
  pnm_free(ims);
  pnm_free(ims2);
}

void
usage(char* s)
{
  fprintf(stderr,"%s <dx> <dy> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);
  int dx = atoi(argv[1]);
  int dy = atoi(argv[2]);
  char *ims = argv[3];
  char *imd = argv[4];
  process(dx, dy, ims, imd);

  return EXIT_SUCCESS;
}
