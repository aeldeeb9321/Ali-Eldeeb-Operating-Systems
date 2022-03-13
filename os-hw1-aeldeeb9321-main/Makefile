CPPFLAGS = -g -I.
LDFLAGS = 

SRC=hello_world.cpp 
OBJ=$(SRC:.cpp=.o)
PGM=$(SRC:.cpp=)


all: hello_world

$(OBJ) : $(SRC)

hello_world: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(PGM)
