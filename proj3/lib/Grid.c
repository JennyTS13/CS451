/* Beatrice Liang and Jenny Lin */
/* Spring 2015 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"

#define USECPP 0

/* create a grid */
Grid *create_grid( char *filename ){
  int i, r, c;

  Grid *g = malloc(sizeof(Grid));
  if(!g)
    return NULL;
  //reads the image into the grid
  g->original = image_read(filename);
  g->after = image_create(g->original->rows, g->original->cols);

  r = g->original->rows/14;
  c = g->original->cols/12;

  //create the grid so that it's divided into 14x12 rectangles
  g->grid = malloc(sizeof(Image)*r);
  if(!g->grid){
    printf("Inside \n");
    image_dealloc(g->original);
    free(g);
    return NULL;
  }

  g->grid[0] = malloc(sizeof(Image)*r*c);
  if(!g->grid[0]){
    printf("Inside \n");
    image_dealloc(g->original);
    free(g->grid);
    free(g);
    return NULL;
  }

  for(i = 1; i < r; i++){
    g->grid[i] = &(g->grid[0][i*c]);
  }

  g->rows = r;
  g->cols = c;
  return g;
}

/* reads and calculate values (intensity & rgb) and store into grid */
/*
void read_to_grid( Grid *g ){
  int row, col;
  for (row = 0; row < g->rows-1; row++){
    for(col = 0; col < g->cols-1; col++){
        g->intensity[row][col] = 
	  (g->original->data[(row+1)*14][(col+1)*12].rgb[0] +
	   g->original->data[(row+1)*14][(col+1)*12].rgb[1] +
	   g->original->data[(row+1)*14][(col+1)*12].rgb[2])/3;
    }
  }
}
*/

Image *create_bw(Grid *g){
    Image *temp;
    int row, col, i;
    temp = image_create(g-> original->rows, g->original->cols);
    for (row = 0; row < g-> original->rows; row++){
      for(col = 0; col< g-> original->cols; col++){
          for(i = 0; i <3 ; i++){
            image_setc(temp, row, col, i, 
		       (g->original->data[row][col].rgb[0] + 
			g->original->data[row][col].rgb[1] +
			g->original->data[row][col].rgb[2])/3);
          }
      }
    }
    return temp;
}

Image *pixelate(Grid *g){
  Image *temp;
  int row, col, i;
  temp = image_create(g->rows, g->cols);
  for (row = 0; row < g->rows-1; row++){
    for(col = 0; col < g->cols-1; col++){
      for(i = 0; i <3 ; i++){
          image_setc(temp,row,col,i,g->original->data[(row+1)*14][(col+1)*12].rgb[i]);
      }
    }
  }
  return temp;
}

/* write appropriate character into grid based on intensity */
void char_to_grid( Grid *g, CharSet *c ){

  Image *temp;
  int row, col, size;
  float intensity; 

  //size of character list
  size = c->size-1;

  for(row = 0; row < g->rows; row++){
    for(col = 0; col < g->cols; col++){
      intensity = (g->original->data[(row+1)*14][(col+1)*12].rgb[0] +
		   g->original->data[(row+1)*14][(col+1)*12].rgb[1] + 
		   g->original->data[(row+1)*14][(col+1)*12].rgb[2])/3;
      temp = binary_search(c, 0, size, intensity);;
      g->grid[row][col] = *temp;
    }
  }    
}

/* Converts the grid into a full-sized image */
void grid_to_pic( Grid *g ){

  int r,c;
  for(r = 0; r < (g->rows * 14); r++){
    for(c = 0; c < (g->cols * 12); c++){
      g->after->data[r][c].rgb[0] = g->grid[r/14][c/12].data[r%14][c%12].rgb[0];
      g->after->data[r][c].rgb[1] = g->grid[r/14][c/12].data[r%14][c%12].rgb[1];
      g->after->data[r][c].rgb[2] = g->grid[r/14][c/12].data[r%14][c%12].rgb[2];
    }
  }
}

/* Add Color to the grid */
void grid_color( Grid *g ){
  int r, c, i;
  float alpha;
  for(r = 0; r < (g->rows * 14); r++){
    for(c = 0; c < (g->cols * 12); c++){
      alpha = (255.0 - g->after->data[r][c].rgb[0])/255.0;
      for(i = 0; i <3 ; i++){
	image_setc(g->after, r, c, i, 
		   (alpha*g->original->data[r][c].rgb[i] +
		    (1-alpha)*g->after->data[r][c].rgb[i]));
      }
    }
  }
}
/* frees everything in the grid, including itself */
void grid_free(Grid *g){
  if(g){

    printf("Freeing Grid \n");
    if(g->grid){
      if(g->grid[0]){
	free(g->grid[0]);
      }
      free(g->grid);
    }
    printf("Freeing after image \n");
    if(g->after){
      image_dealloc(g->after);
    }
    printf("Freeing original image \n");
    image_dealloc(g->original);
    free(g);
  }
}

