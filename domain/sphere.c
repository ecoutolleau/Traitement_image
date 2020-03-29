#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pnm.h>

#include "domain.h"


void 
process(char* ims, char* imd)
{
  pnm ims2 = pnm_load(ims);
  int rows = pnm_get_height(ims2);
  int cols = pnm_get_width(ims2);
  pnm imd2 = pnm_new(cols, rows, PnmRawPpm);
  
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){

      //sphere mais très moche
      float xk = ((float)j/cols)*2-1;
      float yk = ((float)i/rows)*2-1;

      if ((yk*yk + xk*xk) <= 0.999){
	float zk = 1 - (xk*xk + yk*yk);
	
	float xs = atanf(xk/zk)*2/pi;
	float ys = atanf(yk/zk)*2/pi;
	
	int x = (int)(cols*(xs+1)/2);
	int y = (int)(rows*(ys+1)/2);
      
	/* methode alexandre
	   float ys = ((float)j/cols)*2-1;
	   float zs = 1-((float)i/rows)*2;
	   
	   float rho = 1;
	   float psi = asinf(zs/rho);
	   float theta = asinf(ys/(rho*cosf(psi)));
	   
	   float x = cols/2*((theta/pi)+1);
	   float y = rows/2*((-2*psi/pi)+1);
	*/
	for (int k = 0; k < 3; k++){
	  unsigned short c = bilinear_interpolation(x,y,ims2,k);
	  pnm_set_component(imd2, i, j, k, c);
	}
      }
    }
  }
  
  pnm_save(imd2, PnmRawPpm, imd);
  free(imd2);
  free(ims2);
}


static void usage(char* s){
  fprintf(stderr,"%s <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char* argv[]){
  if(argc != PARAM+1) 
    usage(argv[0]);
  char *ims = argv[1];
  char *imd = argv[2];
  process(ims, imd);
  return EXIT_SUCCESS;
}
