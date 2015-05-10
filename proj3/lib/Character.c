/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

/* create a character */
Character *create_char( char *filename ){
  //  printf("Entering create_char\n");
  Character *c = malloc(sizeof(Character));
  if(!c) 
    return NULL;
  c->image = image_read(filename);
  //printf("Exiting create_char\n");  
  return c;
}

/* swap characters (used in sorting) */
void char_swap(Character *a, Character *b){
  Image *image;
  float tempInt;
  int tempAscii;

  image = b->image;
  tempInt = b->intensity;
  tempAscii = b->ascii;
  b->image = a->image;
  b->intensity = a->intensity;
  b->ascii = a->ascii;
  a->image = image;
  a->intensity = tempInt;
  a->ascii = tempAscii;
}

/* create empty character set */
CharSet *set_create(int type){
  //printf("Entering set_create\n");
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
    //printf("Exiting set_create\n");
    return c;
  }
  c->chars = malloc(sizeof(Character*)*95);
    if(!c->chars){
      free(c);
      return NULL;
    }
    c->type = 1;
    c->size = 95;
    //printf("Exiting set_create\n");
    return c;
}

/* free character set */
void set_free( CharSet *c ){
  //printf("Entering set_free\n");
  int i;
  for(i=0; i<c->size; i++){
    image_dealloc( c->chars[i]->image );
    free(c->chars[i]);
  }
  free(c->chars);
  free(c);
  //printf("Exiting set_free\n");
}

/* read characters into character sets */
void char_read(CharSet *c){
  //printf("Entering char_read\n");
  int i;
  char filename[18];
  //10 char set
  if(c->type == 0){
    c->chars[0] = create_char("character/32.ppm");
    c->chars[0]->ascii = 32;
    c->chars[1] = create_char("character/46.ppm");
    c->chars[1]->ascii = 46;
    c->chars[2] = create_char("character/58.ppm");
    c->chars[2]->ascii = 58;
    c->chars[3] = create_char("character/45.ppm");
    c->chars[3]->ascii = 45;
    c->chars[4] = create_char("character/61.ppm");
    c->chars[4]->ascii = 61;
    c->chars[5] = create_char("character/43.ppm");
    c->chars[5]->ascii = 43;
    c->chars[6] = create_char("character/42.ppm");
    c->chars[6]->ascii = 42;
    c->chars[7] = create_char("character/35.ppm");
    c->chars[7]->ascii = 35;
    c->chars[8] = create_char("character/37.ppm");
    c->chars[8]->ascii = 37;
    c->chars[9] = create_char("character/64.ppm");
    c->chars[9]->ascii = 64;
  }
  else{
    for( i = 32; i < 127; i++ ){
      sprintf(filename, "character/%d.ppm", i);
      c->chars[i-32] = create_char(filename);
      c->chars[i-32]->ascii = i;
    }
  }
  //printf("Exiting char_read\n");
}

/* calculate intensity of each character*/
void set_intensity(CharSet *c){

  //printf("Entering set_intensity\n");
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
  //printf("Exiting set_intensity\n");
}

/* sort the character set based on intensity */
void quickSort( CharSet *c, int start, int end ){

  float pivot;
  int i,j;

  pivot = c->chars[(start+end)/2]->intensity;
  i = start;
  j = end;
  
  do{
    while(c->chars[i]->intensity < pivot)
      i++;
    while(pivot < c->chars[j]->intensity)
      j--;
    if(i <= j){
      char_swap( c->chars[i], c->chars[j] );
      i++;
      j--;
    }
  } while( i <= j);

  if(start < j)
    quickSort( c, start, j );
  if(i < end)
    quickSort( c , i, end );
}

/* change range of intensity to [0, 255] */
void set_optimize( CharSet *c ){
  
  int i;
  float min, max, range; //min and max intensity before scaling

  //sort character set from low intensity to high intensity
  quickSort( c, 0, c->size-1 );
  min = c->chars[0]->intensity;
  max = c->chars[c->size-1]->intensity;
  range = max -min;

  //scale intensity
  for( i=0; i<c->size; i++ ){
    c->chars[i]->intensity = 255.0*(c->chars[i]->intensity - min) / range;
  }
}

/* returns the character with intensity closest to requested */
Image *binary_search( CharSet *c, int start, int stop, float intensity ){
  
  int half_dist;
  //printf( "start: %d, stop: %d \n", start, stop);
  
  if(start == stop)
    return c->chars[start]->image;
    
  //in between
  if(stop - start == 1){
    //closer to start
    if((c->chars[stop]->intensity - intensity) > 
       (intensity - c->chars[start]->intensity)){
      return c->chars[start]->image;
    }
    else{
      return c->chars[stop]->image;
    }
  }

  half_dist = (stop - start)/2;

  if(c->chars[half_dist]->intensity >= intensity)
    return binary_search( c, start, start+half_dist, intensity );
  else
    return binary_search( c, start+half_dist+1, stop, intensity );

}
