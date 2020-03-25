#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process(pnmChannel num, char *ims, char *imd){
  pnm ims2 = pnm_load(ims);
  pnm imd2 = pnm_dup(ims2);
  unsigned short *r = pnm_get_channel(ims2, NULL, num);
  pnmChannel num2 = (num+1)%3;
  pnmChannel num3 = (num+2)%3;
  pnm_set_channel(imd2,r,num2);
  pnm_set_channel(imd2,r,num3);
  pnm_save(imd2, PnmRawPpm, imd);
  pnm_free(ims2);
  pnm_free(imd2);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<num> <ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 3
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  pnmChannel num = atoi(argv[1]);
  char *ims = argv[2];
  char *imd = argv[3];
  process(num, ims, imd);
  return EXIT_SUCCESS;
}
