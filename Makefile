#list all cpp files in src directory
CPP_FILES := $(wildcard src/*.cpp)

# convert all cpp files to .o files
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

CC = g++
INCLUDE = -Iinterface

#linking main executable
.PHONY: run
run: main.exe
	main.exe

.PHONY: main
main.exe: $(OBJ_FILES) obj/main.o
	$(CC) -o $@ $^ $(INCLUDE)

# compile each .cpp file to .o file
obj/%.o: src/%.cpp
	$(CC) -c -o $@ $< $(INCLUDE)

obj/main.o : main.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE)

clean:
	del obj\*.o
	del main.o
	del main.exe