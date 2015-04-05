#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

/* create a character */
Character *create_char( char *filename ){
  printf("Entering create_char\n");
  Character *c = malloc(sizeof(Character));
  if(!c) 
    return NULL;
  c->image = image_read(filename);
  printf("Exiting create_char\n");  
  return c;
}

/* create empty character set */
CharSet *set_create(int type){
  printf("Entering set_create\n");
  CharSet *c = malloc(sizeof(CharSet));
  if(!c)
    return NULL;

  if(type == 0){
    c->chars = malloc(sizeof(Character*)*10);
    if(!c->chars){
      free(c);
      return NULL;
    }
    c->type = 0;
    c->size = 10;
    printf("Exiting set_create\n");
    return c;
  }
  c->chars = malloc(sizeof(Character*)*95);
    if(!c->chars){
      free(c);
      return NULL;
    }
    c->type = 1;
    c->size = 95;
    printf("Exiting set_create\n");
    return c;
}

/* free character set */
void set_free( CharSet *c ){
  printf("Entering set_free\n");
  int i;
  for(i=0; i<c->size; i++){
    printf("characters freed %d\n", i);
    image_dealloc( c->chars[i]->image );
    free(c->chars[i]);
  }
  free(c->chars);
  free(c);
  printf("Exiting set_free\n");
}

/* read characters into character sets */
void char_read(CharSet *c){
  printf("Entering char_read\n");
  int i;
  char filename[18];
  //10 char set
  if(c->type == 0){
    c->chars[0] = create_char("character/32.ppm");
    c->chars[1] = create_char("character/46.ppm");
    c->chars[2] = create_char("character/58.ppm");
    c->chars[3] = create_char("character/45.ppm");
    c->chars[4] = create_char("character/61.ppm");
    c->chars[5] = create_char("character/43.ppm");
    c->chars[6] = create_char("character/42.ppm");
    c->chars[7] = create_char("character/35.ppm");
    c->chars[8] = create_char("character/37.ppm");
    c->chars[9] = create_char("character/64.ppm");
  }
  else{
    for( i = 32; i < 127; i++ ){
      sprintf(filename, "character/%d.ppm", i);
      c->chars[i-32] = create_char(filename);
    }
  }
  printf("Exiting char_read\n");
}

/* calculate intensity of each character*/
void set_intensity(CharSet *c){

  printf("Entering set_intensity\n");
  int i,j,k;
  float rgb;
 
  for( i=0; i<c->size; i++){
    rgb = 0; 
    for(j=0; j<14; j++){
      for(k=0; k<12; k++){
	rgb = rgb + 
	  c->chars[i]->image->data[j][k].rgb[0] +
	  c->chars[i]->image->data[j][k].rgb[1] +
	  c->chars[i]->image->data[j][k].rgb[2];
      }
    }
    c->chars[i]->intensity = rgb/
      (3 * 14 * 12);
  }
  printf("Exiting set_intensity\n");
}
