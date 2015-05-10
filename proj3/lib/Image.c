/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

///////////////////////////////////////////
///////////////////////////////////////////
//////////////////Image////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
/* Constructors and Destructors */
Image *image_create(int rows, int cols){
  int i;
  Image *image = malloc(sizeof(Image));
  if(!image) 
    return NULL;

  image->rows = rows;
  image->cols = cols;
  image->data = malloc(sizeof(Color)*rows);
  if(!image->data)
    return NULL;

  image -> data[0] = malloc(sizeof(Color)*rows*cols);
  if (!image -> data[0]){
    return (NULL);
  }
  for (i = 1; i<rows; i++){
    image -> data[i] = &(image -> data[0][i*cols]);
  }
  image -> rows = rows;
  image -> cols = cols;
  return (image);
}

void image_free(Image *src){
  if (src){
    if (src -> data){
      if(src -> data[0]){
	free (src -> data[0]);
      }
      free(src->data);
    }
    free(src);
  }
}

void image_init(Image *src){
  src->rows = 0;
  src->cols = 0;
  src->data = NULL;
}

int image_alloc(Image *src, int rows, int cols){
  //free existing memory
  int i;
  if (rows == 0 || cols == 0){
    src->rows = 0;
    src->cols = 0;
    return (1);
  }

  if (src -> rows !=0 && src -> cols != 0){
    if (src -> data){
      if(src->data[0])
	free(src ->data[0]);
      free(src->data);
    }
  }

  src -> data = malloc(sizeof(Color)*rows);
  if (!src -> data){
    src->rows = 0;
    src->cols = 0;
    return (1);
  }
  src -> data[0] = malloc(sizeof(Color)*rows*cols);
  if (!src -> data[0]){
    free(src->data);
    src->rows = 0;
    src->cols = 0;
    return (1);
  }

  for (i = 1; i<rows; i++){
    src -> data[i] = &(src -> data[0][i*cols]);
  }

  src -> rows = rows;
  src -> cols = cols;

  for (i = 0 ;i<rows*cols; i++){
    src -> data[0][i].rgb[0] = 0;
    src -> data[0][i].rgb[1] = 0;
    src -> data[0][i].rgb[2] = 0;
  }
    
  return (0);
  
}

void image_dealloc(Image *src){
  if(src->data){
    if(src->data[0])
      free(src -> data[0]);
    free(src -> data);
  }
  src -> data = NULL;
  src -> rows = 0;
  src -> cols = 0;  
}

/* End Constructor and Destructor */


/* I/O methods */

//Slightly modified from ppmIO.c from project 1
Image *image_read(char *filename) {
  int i;
  int j;
  Image *src;
  
  Pixel *image;
  int rows, cols, colors;
    
  image = readPPM(&rows, &cols,&colors,filename);
     
  src = image_create(rows,cols);
  if (src == NULL){
    return (NULL);
  }

  for ( i = 0; i<rows ; i++){
    for (j = 0; j<cols ; j++){
      src -> data[i][j].rgb[0] = image[i*cols+j].r;
      src -> data[i][j].rgb[1] = image[i*cols+j].g;
      src -> data[i][j].rgb[2] = image[i*cols+j].b;
    }
  }
  /*
  printf("R: %f, G: %f, B: %f\n", src -> data[5][5].rgb[0],
           src -> data[5][5].rgb[1],
           src -> data[5][5].rgb[2]);
  */
  free(image);
  return (src);
}

int image_write(Image *src, char *filename){
  int i;
  int j;
  Pixel *image;
  int rows;
  int cols;
  int colors;
  
  colors = 255;
  rows = src ->rows;
  cols = src ->cols;
  image = malloc((sizeof(Pixel)*rows*cols));
  if (!image ){
    return (1);
  }
  for (i = 0; i<rows; i++){
    for(j = 0; j<cols; j++){
      image[i*cols+j].r = src -> data[i][j].rgb[0];
      image[i*cols+j].g = src -> data[i][j].rgb[1];
      image[i*cols+j].b = src -> data[i][j].rgb[2];
    }
  }
  writePPM (image, rows, cols, colors, filename);
  free(image);
  return (0);
}

/* End I/O methods */

/* Access methods */

float image_getc(Image *src, int r, int c, int b){
  return src->data[r][c].rgb[b];
}

void image_setc(Image *src, int r, int c, int b, float val){
  src->data[r][c].rgb[b] = val;
}

/* End Access Methods */

/* Usage Methods */

void image_reset(Image *src){
  int i;
  for (i = 0; i<src -> rows*src -> cols; i++){
    src -> data[0][i].rgb[0] = 0.0;
    src -> data[0][i].rgb[1] = 0.0;
    src -> data[0][i].rgb[2] = 0.0;
  }
}

void image_fill(Image *src, Color val){
  int i;
  int j;
  for (i = 0; i<src -> rows; i++){
    for (j = 0; j< src -> cols ; j++){
      src -> data[i][j] = val;
    }
  }
}

void image_fillrgb(Image *src, float r, float g, float b){
  int i;
  int j;
  for (i = 0; i<src -> rows; i++){
    for (j = 0; j<src -> cols; j++){
      src -> data [i][j].rgb[0] = r;
      src -> data[i][j].rgb[1] = g;
      src -> data[i][j].rgb[2] = b;
    }
  }
}

/* copies the Color data. */
void Color_copy(Color *to, Color *from){
  to->rgb[0] = from->rgb[0];
  to->rgb[1] = from->rgb[1];
  to->rgb[2] = from->rgb[2];
}

/* sets the Color data */
void Color_set(Color *to, float r, float g, float b){
  to->rgb[0] = r;
  to->rgb[1] = g;
  to->rgb[2] = b;
}

/* copies the Color data to the proper pixel */
void image_setColor( Image *src, int r, int c, Color val ){
  src->data[r][c] = val;
}

/* returns a Color structure built from the pixel values */
Color image_getColor( Image *src, int r, int c ){
  return src->data[r][c];
}
