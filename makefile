# Final Project
EXE = main

# Root paths
SRC = src/
OUT = bin/

# Src sub paths
ENGINE = $(SRC)Engine/
UTIL = $(ENGINE)Utility/

# Out sub paths
OBJ = $(OUT)obj/

# Include directories
VPATH = src : src/Engine : src/Engine/Utility : src/Engine/Objects/Brushes : src/Engine/Objects/Entities : src/Vendor/stb_image : src/Vendor/glm/glm : src/Vendor/glm/glm/gtc

# Source files
SRC = Texture.o fatal.o errcheck.o print.o loadtexbmp.o loadobj.o stb_image.o Star.o Rhombus.o Cube.o Plane.o Brush.o Motor.o Rotator.o VertexBuffer.o

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -I/opt/homebrew/include -L/opt/homebrew/lib -Qunused-arguments
LIBS=-framework GLUT -lSDL2main -lSDL2 -lSDL2_mixer -framework Cocoa -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lSDL2 -lSDL2_mixer -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

#  Create archive
objects.a:$(SRC)
	cd $(OBJ) && ar -rcs $@ $^

# Compile rules
%.o: %.c
	gcc -c $(CFLG) $< -o $(OBJ)$@
%.o: %.cpp
	g++ -c $(CFLG) $< -o $(OBJ)$@

#  Link
main: Application.o objects.a
	cd $(OBJ) && g++ $(CFLG) -o ../../$@ $^ $(LIBS)

#  Clean
clean:
	cd $(OBJ) && $(CLEAN)
