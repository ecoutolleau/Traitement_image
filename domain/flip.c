#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pnm.h>

void
horizontal(char * ims, char * imd) {
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(cols,rows,PnmRawPpm);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < 3; k++) {
      unsigned short imsC = pnm_get_component(ims2, i, j, k);
      pnm_set_component(imd2, i, cols-j-1, k, imsC);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}

void
vertical(char* ims, char *imd) {
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(cols, rows, PnmRawPpm);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < 3; k++) {
	unsigned short imsC = pnm_get_component(ims2, i, j, k);
	pnm_set_component(imd2, rows-i-1, j, k, imsC);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}

void
transversal(char *ims, char *imd){
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(rows, cols, PnmRawPpm);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < 3; k++) {
      unsigned short imsC = pnm_get_component(ims2, i, j, k);
      pnm_set_component(imd2, j, i, k, imsC);
      }
    }
  }
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(imd2);
  pnm_free(ims2);
}


void 
process(char *dir, char* ims_name, char* imd_name)
{
  int length = strlen(dir);
  char * ims = ims_name;
  for (int i = 0; i < length; i++){
    switch(dir[i]){
    case 'h':
      horizontal(ims, imd_name);
      break;
    case 'v':
      vertical(ims, imd_name);
      break;
    case 't':
      transversal(ims, imd_name);
      break;
    }
    ims = imd_name;
  }
}


void
usage(char* s)
{
  fprintf(stderr,"%s <dir> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}


#define PARAM 3
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);
  char *dir = argv[1];
  char *ims = argv[2];
  char *imd = argv[3];
  process(dir, ims, imd);

  return EXIT_SUCCESS;
}
