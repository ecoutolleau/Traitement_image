#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process(char *ims0, char *ims1, char *ims2, char *imd){
  pnm ims02 = pnm_load(ims0);
  pnm ims12 = pnm_load(ims1);
  pnm ims22 = pnm_load(ims2);
  pnm imd2 = pnm_dup(ims02);
  unsigned short *r = pnm_get_channel(ims02, NULL, PnmRed);
  unsigned short *g = pnm_get_channel(ims12, NULL, PnmGreen);
  unsigned short *b = pnm_get_channel(ims22, NULL, PnmBlue);
  pnm_set_channel(imd2,r,PnmRed);
  pnm_set_channel(imd2,g,PnmGreen);
  pnm_set_channel(imd2,b,PnmBlue);
  pnm_save(imd2,PnmRawPpm, imd);
  pnm_free(ims02);
  pnm_free(ims12);
  pnm_free(ims22);
  pnm_free(imd2);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<ims0> <ims1> <ims2> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  char *ims0 = argv[1];
  char *ims1 = argv[2];
  char *ims2 = argv[3];
  char *imd = argv[4];
  process(ims0, ims1, ims2, imd);
  return EXIT_SUCCESS;
}
