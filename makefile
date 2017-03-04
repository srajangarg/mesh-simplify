#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable
# 'make clean'  removes all .o and executable files
#

CC := c++
CFLAGS := -Wall -g2 -O2 -std=c++11 -fno-strict-aliasing
ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
INCLUDES :=
LFLAGS :=
LIBS := -lX11 -lXi -lXmu -lglut -lGLU -lGL -lm
SRCS := $(shell ls -1 $(ROOT_DIR)/src/DGP/*.cpp | sed 's/ /\\ /g') \
        $(shell ls -1 $(ROOT_DIR)/src/DGP/Graphics/*.cpp | sed 's/ /\\ /g') \
        $(shell ls -1 $(ROOT_DIR)/src/*.cpp | sed 's/ /\\ /g')
OBJS := $(SRCS:.cpp=.o)
MAIN := simplify

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	@echo  Compilation finished

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
