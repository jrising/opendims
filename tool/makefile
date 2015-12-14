SYS = Linux

CC = g++
DEBUG = -g
ODM = ..
CFLAGS = -Wall -c $(DEBUG) -I $(ODM) -std=c++0x
LFLAGS = -Wall $(DEBUG)

all: convert.o $(ODM)/dims/Dims.o $(ODM)/dims/Dimensions.o $(ODM)/dims/Dimensionless.o $(ODM)/measure/Units.o $(ODM)/measure/Inds.o $(ODM)/dims/GlobalDimensions.o
	$(CC) $(LFLAGS) convert.o $(ODM)/dims/Dims.o $(ODM)/dims/Dimensions.o $(ODM)/dims/Dimensionless.o $(ODM)/measure/Units.o $(ODM)/measure/Inds.o $(ODM)/dims/GlobalDimensions.o -o convert

#Inference rule - states a general rule for compiling .o files
%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	\rm *.o
