CC		= g++
CFLAGS	= -Iinclude/ -g -Wall -std=c++11
SRC		:= $(wildcard src/*.cpp)
OBJS	:= $(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
LIBS	= -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
DEPDIR 	= -Llib/
TARGET 	= bin/libantisocial.so
BUILDS  = $(OBJS) $(TARGET)


$(TARGET): $(OBJS)
	$(CC) -DGLEW_STATIC -DGLEW_NO_GLU -shared $(CFLAGS) -o $@ $^ $(DEPDIR) $(LIBS)
	sudo cp $(TARGET) /usr/lib

obj/%.o: src/%.cpp
	$(CC) -DGLEW_STATIC -DGLEW_NO_GLU -fPIC $(CFLAGS) -c -o $@ $<

clean:
	rm $(BUILDS) 
