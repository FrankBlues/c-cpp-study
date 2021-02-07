#
# define name of output executable
#

PROG = Geotiff

#
# specify name of C++ compiler.
#
 
CC = g++
  
#
# include directories for header files.
#
  
CPPFLAGS = -g -Wall -I/usr/include
   
LDFLAGS = -L/usr/lib -lgdal -lm
   
# 
# clean-up option to remove executable.
# 
  
all:
	@$(CC) Main.cpp GeoTiff.cpp $(CPPFLAGS) $(LDFLAGS) -o $(PROG)
    
clean:
	@rm $(PROG)
