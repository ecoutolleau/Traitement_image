ROOT=../bcl

CPPFLAGS = -I$(ROOT)/include
CFLAGS   = -Wall -Wextra -Werror -std=c99
LDFLAGS  = -L$(ROOT)/lib 
LDLIBS   = -lbcl -lm

OBJ = domain.o
BIN=\
	move\
	scroll\
	flip\
	shear\
	rotate\
	wave\
	sphere

.PHONY: all
all:$(BIN)

shear: $(OBJ)

rotate: $(OBJ)

wave: $(OBJ)

sphere: $(OBJ)

.PHONY: clean cleanall
clean:
	$(RM) *.o *~ *.ppm
cleanall: clean
	$(RM) $(BIN) 



