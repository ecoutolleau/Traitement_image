/**
 * @file test-bcl.c
 * @author Vinh-Thong Ta <ta@labri.fr>
 * @brief ???*
 */

#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void  
process(const size_t rows, const size_t cols)
{
  pnm imd  = pnm_new(cols, rows, PnmRawPpm);
  unsigned short *data = pnm_get_image(imd); 

  //go through the whole picture and put the buffer item at pnm_maxval
  unsigned short *p = data;
  size_t size = rows*cols*3;
  while(size--) *p++ = pnm_maxval;    
  pnm_save(imd, PnmRawPpm, "a.ppm");

  //erase red component between 1/4 and 3/4 of the picture
  size_t i0 = (size_t)rows/4;
  size_t i1 = 3*i0;
  size_t j0 = (size_t)cols/4;
  size_t j1 = 3*j0;
  for(size_t i=i0; i<i1; i++){
    for(size_t j=j0; j<j1; j++){	
      p  = data + pnm_offset(imd, i, j);
      // p  = data + (i*(cols*3)+j*3);
      *p = pnm_maxval - *p; 
      p++;
    }
  }
  pnm_save(imd, PnmRawPpm, "b.ppm");

  //erase the blue component (in cyan square and in white space around)
  // all values are at pnm_maxval
  for(size_t i=0; i<rows; i++){
    for(size_t j=0; j<cols; j++){
      for(size_t k=0; k<3; k++){
	const unsigned short val = pnm_get_component(imd, i, j, k);
	if(val == pnm_maxval){
	  pnm_set_component(imd, i, j, 2, 0);
	}
      }
    }
  }
  pnm_save(imd, PnmRawPpm, "c.ppm");

  //erase the green component from all the picture
  unsigned short *channel = pnm_get_channel(imd, NULL, 1);
  for(size_t i=0; i<rows*cols; i++) channel[i] = 0;
  pnm_set_channel(imd, channel, 1);
  pnm_save(imd, PnmRawPpm, "d.ppm");
  
  pnm_free(imd);
  free(channel);
}

void 
usage(const char *s){
  fprintf(stderr, "Usage: %s <rows> <cols> \n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 2
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  size_t rows = atoi(argv[1]);
  size_t cols = atoi(argv[2]);
  process(rows, cols);
  return EXIT_SUCCESS;
}
