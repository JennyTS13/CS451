#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  /* Mass converting between ppm and png */
  /*  
  int i;
  char *s = malloc(strlen("convert 111.png 111.ppm "));
  
  for(i = 32; i < 127; i++){
    sprintf(s, "convert %d.png %d.ppm", i, i);
    system(s);
  }
  free(s);
  */


  /* Grayscaling ascii */
  int i, j, k;
  CharSet *c;
  char *s = malloc(strlen("character/111.ppm "));
  float intensity;

  c = set_create(1);
  char_read(c);
  //set_intensity(c);
  for( i=0; i<c->size; i++ ){
    for(j = 0; j< c->chars[i]->image->rows; j++){
      for(k = 0; k < c->chars[i]->image->cols; k++){
	intensity = (c->chars[i]->image->data[j][k].rgb[0] + 
		     c->chars[i]->image->data[j][k].rgb[1] +
		     c->chars[i]->image->data[j][k].rgb[2])/3;

	c->chars[i]->image->data[j][k].rgb[0] = intensity;
	c->chars[i]->image->data[j][k].rgb[1] = intensity;
	c->chars[i]->image->data[j][k].rgb[2] = intensity;
      }
    }
    sprintf(s, "character/%d.ppm", i+32);
    
    image_write(c->chars[i]->image, s);
  }

}
