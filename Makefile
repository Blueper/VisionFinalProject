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


#Circle param calculation program
ALL_OBJ=webcam_test.o ball.o
PROGRAM=volleyball
$(PROGRAM): $(ALL_OBJ)
	g++ `$(CV_LIBS) --cflags` $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ) `$(CV_LIBS) --libs` $(INCLUDES) $(LIBS_ALL)

#Foreground Mask
FG_OBJ=motion_detection.o opencvfuncs.o
FG_PROGRAM=fgmask
$(FG_PROGRAM): $(FG_OBJ)
	g++ `$(CV_LIBS) --cflags` $(C++FLAG) -o $(EXEC_DIR)/$@ $(FG_OBJ) `$(CV_LIBS) --libs` $(INCLUDES) $(LIBS_ALL)

all:
	make $(PROGRAM)
	make $(FG_PROGRAM)
	make clean

.PHONY: clean
clean:
	(rm -f *.o;)

(:
