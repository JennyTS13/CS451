#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

typedef struct {
  float rgb[3];
} Color;

typedef struct {
  Color **data;
  int rows;
  int cols;
} Image;

typedef struct {
  Image *image;
  float intensity;
  char ascii;//error checking purposes
} Character;

typedef struct{
  Character **chars;
  int type; //0 for default 10, 1 for all
  int size; //size of character set
} CharSet;

typedef struct{
  Image *original;
  Image *after;
  Image **grid;
  float **intensity;
  float **r;
  float **g;
  float **b;
  int rows;
  int cols;
} Grid;

Pixel *readPPM(int *rows, int *cols, int * colors, char *filename);
void writePPM(Pixel *image, int rows, int cols, int colors, char *filename);

unsigned char *readPGM(int *rows, int *cols, int *intensities, char *filename);
void writePGM(unsigned char *image, long rows, long cols, int intensities, char *filename);

/* Constructor and destructors */
Image *image_create(int rows, int cols);
void image_free(Image *src);
void image_init(Image *src);
int image_alloc(Image *src, int rows, int cols);
void image_dealloc(Image *src);

/* I/O functions */
Image *image_read(char *filename);
int image_write(Image *src, char *filename);

/* Access */
float image_getc(Image *src, int r, int c, int b);
void image_setc(Image *src, int r, int c, int b, float val);


/* Utility */
void image_reset(Image *src);
void image_fill(Image *src, Color val);
void image_fillrgb(Image *src, float r, float g, float b);

/* Color */
void Color_copy(Color *to, Color *from);
void Color_set(Color *to, float r, float g, float b);

void image_setColor( Image *src, int r, int c, Color val );
Color image_getColor( Image *src, int r, int c );

/* Characters */
Character *create_char( char *filename );
void char_swap(Character *a, Character *b);
CharSet *set_create( int type );
void set_free( CharSet *c );
void char_read( CharSet *c );
void set_intensity(CharSet *c);
void quickSort( CharSet *c, int start, int end );
void set_optimize( CharSet *c );
Image *binary_search( CharSet *c, int start, int stop, float intensity );

/* Grid */
Grid *create_grid( char *filename );
void grid_free( Grid *g );
void read_to_grid( Grid *g );
void char_to_grid( Grid *g, CharSet *c );
void grid_to_pic( Grid *g );
#endif
