CC= g++
# GM_DIR = /home/adam/Documents/Green-Marl/apps/output_cpp/gm_graph
LIB = $(GM_DIR)/lib
INC = $(GM_DIR)/inc
BIN = bin
SRC = src
OBJ = obj
CFLAGS = -std=c++11 -O3 -g -I$(INC) -fopenmp -Wall 
OUT = $(BIN)/gm_convert_snap_file

# where to find source codes
vpath %.cc $(SRC)

all: $(OUT) Makefile

$(BIN)/gm_convert_snap_file: $(OBJ)/gm_convert_snap_file.o $(LIB)/libgmgraph.a
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $(OBJ)/gm_convert_snap_file.o $(LFLAGS) -L$(LIB) -lgmgraph -o $@	

$(OBJ)/%.o: %.cc 
	if [ ! -d obj ]; then mkdir obj; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)/*.o $(OUT) 
