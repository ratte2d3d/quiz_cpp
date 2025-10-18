CXX = g++

# OpenCV flags (pkg-config を優先、見つからなければフォールバック)
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4 2>/dev/null || pkg-config --cflags opencv 2>/dev/null || echo -I/usr/include/opencv4)
OPENCV_LIBS   := $(shell pkg-config --libs opencv4 2>/dev/null || pkg-config --libs opencv 2>/dev/null || echo -lopencv_core -lopencv_imgcodecs -lopencv_highgui)

CXXFLAGS = -Wall -fPIC -Iinclude $(OPENCV_CFLAGS)
LDFLAGS = -Llib -lDirNav -lQuiz -lQuizIO -Wl,-rpath=./lib $(OPENCV_LIBS)

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(LIB_DIR)/libDirNav.so $(LIB_DIR)/libQuiz.so $(LIB_DIR)/libQuizIO.so main

main: main.o
	$(CXX) main.o -o main $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(LIB_DIR)/libDirNav.so: $(SRC_DIR)/DirectoryNavigator.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

$(LIB_DIR)/libQuiz.so: $(SRC_DIR)/QuizManager.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

$(LIB_DIR)/libQuizIO.so: $(SRC_DIR)/QuizIO.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

clean:
	rm -f main *.o lib/*.so
	
run: all
	./main .