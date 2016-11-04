TARGET = test


OBJS = svd.o
CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv) -I/usr/include/opencv2/ -Iinclude/
LDFLAGS += $(shell pkg-config --libs --static opencv)

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)
	

clean: ; rm -f $(TARGET)  $(OBJS)

