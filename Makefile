BASE = equilibrium

all: $(BASE)

OS := $(shell uname -s)

ifeq ($(OS), Linux) # tested on Mint 16
  LDFLAGS += -L/usr/X11R6/lib
  LIBS += -lGL -lGLU -lglut
endif

ifeq ($(OS), Darwin) # Assume OS X
  CPPFLAGS += -D__MAC__
  LDFLAGS += -framework GLUT -framework OpenGL
endif

ifdef OPT 
  #turn on optimization
  CXXFLAGS += -O2
else 
  #turn on debugging
  CXXFLAGS += -g
endif

CXX = g++ 

OBJ = $(BASE).o ppm.o glsupport.o

$(BASE): $(OBJ)
	$(LINK.cpp) -o $@ $^ $(LIBS) -lGLEW 

clean:
	rm -f $(OBJ) $(BASE)
