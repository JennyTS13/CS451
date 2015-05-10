/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

int main(int argc, char *argv[]){

  CharSet *c;
  Grid *g;

  if(argc < 4) {
    printf("Usage: ../bin/ascii <0 or 1> <input file> <output file>\n");
    exit(-1);
  }

  c = set_create(atoi(argv[1]));
  char_read(c);
  set_intensity(c);
  quickSort( c, 0, c->size-1 );
  set_optimize(c);

  g = create_grid( argv[2] );
  char_to_grid( g, c );
  grid_to_pic(g);
  grid_color(g);
  image_write( g->after, argv[3] );
  grid_free(g);
  set_free(c);
  
}
    
