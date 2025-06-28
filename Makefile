CC = g++
CFLAGS = -Wall -std=c++11
LIBS = -lglut -lGL -lGLU -lm

TARGET = robot3d
SOURCE = no_annimation.cpp

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)

install-deps:
	sudo apt-get update
	sudo apt-get install -y freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev

run: $(TARGET)
	./$(TARGET)

.PHONY: clean install-deps run 