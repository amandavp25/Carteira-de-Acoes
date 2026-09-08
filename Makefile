
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

CFLAGS = -Wall -g -std=c++11 -I$(INC)


EXE = $(BIN)/tp1.out


OBJS = $(OBJ)/Acao.o $(OBJ)/Cliente.o $(OBJ)/Sistema.o $(OBJ)/main.o

all: directories $(EXE)


directories:
	@mkdir -p $(OBJ) $(BIN)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/Acao.o: $(SRC)/Acao.cpp $(INC)/Acao.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Acao.cpp -o $(OBJ)/Acao.o

$(OBJ)/Cliente.o: $(SRC)/Cliente.cpp $(INC)/Cliente.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Cliente.cpp -o $(OBJ)/Cliente.o

$(OBJ)/Sistema.o: $(SRC)/Sistema.cpp $(INC)/Sistema.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Sistema.cpp -o $(OBJ)/Sistema.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/Acao.hpp $(INC)/Cliente.hpp $(INC)/Sistema.hpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -f $(OBJ)/*.o $(EXE)