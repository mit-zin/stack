FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs\
	-Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	-Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers\
	-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo\
	-Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits\
	-Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

INCL=-I.\include

OBJ_DIR=.\objects

SRC_DIR=.\source

GPP=g++ $(FLAGS) $(INCL)

OBJECTS=$(OBJ_DIR)\main.o $(OBJ_DIR)\verify_funcs.o $(OBJ_DIR)\stack_funcs.o

stack: $(OBJECTS)
	$(GPP) $(OBJECTS) -o stack

$(OBJ_DIR)\main.o: $(SRC_DIR)\main.cpp
	$(GPP) -c $(SRC_DIR)\main.cpp -o $(OBJ_DIR)\main.o

$(OBJ_DIR)\verify_funcs.o: $(SRC_DIR)\verify_funcs.cpp
	$(GPP) -c $(SRC_DIR)\verify_funcs.cpp -o $(OBJ_DIR)\verify_funcs.o

$(OBJ_DIR)\stack_funcs.o: $(SRC_DIR)\stack_funcs.cpp
	$(GPP) -c $(SRC_DIR)\stack_funcs.cpp -o $(OBJ_DIR)\stack_funcs.o
