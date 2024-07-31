TARGET = GoL.out
COMPILER = g++

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIBS = -lncursesw

SRC = $(wildcard $(SRC_PATH)*.cpp)
OBJ = $(patsubst $(SRC_PATH)%.cpp, $(OBJ_PATH)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(COMPILER) $(OBJ) -o $(TARGET) $(LIBS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	$(COMPILER) -c $< -o $@

clean : 
	rm  $(TARGET) $(OBJ_PATH)*.o

run :
	./$(TARGET)

create :
	mkdir -p $(OBJ_PATH) $(SRC_PATH) $(INC_PATH)
