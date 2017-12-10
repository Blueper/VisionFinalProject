########################################
##
## Makefile
## LINUX compilation
##
##############################################

#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm
CV_LIBS = pkg-config opencv
EXEC_DIR=.


.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@
.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS)


ALL_OBJ=main_game.o ball.o opencvfuncs.o
PROGRAM=game
$(PROGRAM): $(ALL_OBJ)
	g++ `$(CV_LIBS) --cflags` $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ) `$(CV_LIBS) --libs` $(INCLUDES) $(LIBS_ALL)

all:
	make $(PROGRAM)
	make clean

.PHONY: clean
clean:
	(rm -f *.o;)

(:
