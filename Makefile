#list all cpp files in src directory
CPP_FILES := $(wildcard src/*.cpp)

# convert all cpp files to .o files
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

CC = g++
INCLUDE = -Iinterface

#linking main executable
.PHONY: run
run: obj test.exe
	test.exe

.PHONY: test
test.exe: $(OBJ_FILES) obj/test.o
	$(CC) -o $@ $^ $(INCLUDE)

# compile each .cpp file to .o file
obj/%.o: src/%.cpp
	$(CC) -c -o $@ $< $(INCLUDE)

# check if the folder obj does not exist, create it
obj: 
	if not exist obj mkdir obj

obj/test.o : test.cpp
	
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE)

clean:
	del obj\*.o
	del main.o
	del main.exe