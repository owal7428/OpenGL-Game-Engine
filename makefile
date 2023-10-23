# Final Project
EXE = main

# Root paths
SRC = src/
OUT = bin/

# Src sub paths
UTIL = $(SRC)util/

# Out sub paths
OBJ = $(OUT)obj/

VPATH = src : src/util

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

#  Create archive
util.a:fatal.o errcheck.o print.o loadtexbmp.o loadobj.o
	cd $(OBJ) && ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $< -o $(OBJ)$@
.cpp.o:
	g++ -c $(CFLG) $< -o $(OBJ)$@

#  Link
main: main.o util.a
	cd $(OBJ) && gcc $(CFLG) -o ../../$@ $^ $(LIBS)

#  Clean
clean:
	cd $(OBJ) && $(CLEAN)
