# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc -I/opt/X11/include -L/opt/X11/lib -I/opt/local/include -L/opt/local/lib -I./include -I/usr/local/Cellar/libtiff/4.0.3/include -L/usr/local/Cellar/libtiff/4.0.3/lib

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations -framework OpenGL -framework GLUT
CPPFLAGS = $(CFLAGS)

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -lm -limageIO
LFLAGS = -L$(LIBDIR)

# put all of the relevant include files here
_DEPS = graphics.h tiff-util.h

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = cake collision wind burn

# put a list of all the object files here for all executables (with .o endings)
_OBJ = cake.o collision.o wind.o burn.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all:	
	for i in $(EXECUTABLES); do (make $$i) ; done

# put the specific executable rules here
burn: $(ODIR)/burn.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) $(CFLAGS)

cake: $(ODIR)/cake.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) $(CFLAGS) -ltiff

collision: $(ODIR)/collision.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) $(CFLAGS)

wind: $(ODIR)/wind.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

