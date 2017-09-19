CC	= g++
CFLAGS	= -I../src/ -g -Wall -std=c++11
SRC	:= $(wildcard src/*.cpp)
OBJS	:= $(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
DEPDIR 	= -L../bin/
LIBS	= -lantisocial -lGL
TARGET 	= bin/test
BUILDS  = $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(DEPDIR) $(LIBS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(BUILDS) 
