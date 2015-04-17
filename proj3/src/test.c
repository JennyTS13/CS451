#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

int main(int argc, char *argv[]){

  int i;
  CharSet *c;
  Grid *g;
  Image *temp;

  c = set_create(1);
  char_read(c);
  set_intensity(c);
  quickSort( c, 0, c->size-1 );
  set_optimize(c);

  if(argc < 3) {
    printf("Usage: ../bin/test <input file> <output file>\n");
    exit(-1);
  }

  g = create_grid( argv[1] );
  read_to_grid(g);
  char_to_grid( g, c );
  //temp = binary_search( c, 0, c->size-1, g->intensity[10][10]);//c->chars[5]->image;
  printf("Checkpoint 3.5\n");
  grid_to_pic(g);
  image_write( g->after, argv[2] );
  printf("Checkpoint 4\n");
  grid_free(g);
  set_free(c);
  /*
  char_swap(c->chars[1],c->chars[2]);
  char_swap(c->chars[7],c->chars[6]);
  char_swap(c->chars[4],c->chars[9]);
  printf("*********Before Sorting********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii);
  }
  quickSort( c, 0, c->size-1 );
  printf("*********After Sorting********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii);
  }
  image_write(c->chars[1]->image, "1.ppm");
  image_write(c->chars[2]->image, "2.ppm");
  */
  /*
  quickSort( c, 0, c->size-1 );
  printf("*********Before Optimization********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii);
  }
  set_optimize(c);
  printf("*********After Optimization********* \n");
  for( i=0; i<c->size; i++ ){
    printf("Index: %d, Intensity: %f, Character %c, Row: %d, Col: %d\n", 
	   i, c->chars[i]->intensity, c->chars[i]->ascii,
	   c->chars[i]->image->rows, c->chars[i]->image->cols);
  }

  set_free(c);
  */
}
    
