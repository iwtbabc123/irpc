#common

CC = g++
AR = ar cru
CCFLAGS = -g -Wall -fPIC
SOFLAGS = -shared

LDFLAGS = -L/usr/local/lib -L/usr/local/protobuf/lib

ALPHA_INCL = -I../net -I/usr/local/protobuf/include
ALPHA_INCL += -std=c++11
ALPHA_LIB = -lev -lprotobuf # lpthread

CCFLAGS += $(ALPHA_INCL)
LDFLAGS += $(ALPHA_LIB)

SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
  
.PHONY : debug release clean rebuild cleantmp

TARGET = librpc.so librpc.a

all:  $(TARGET) cleantmp

librpc.so: $(OBJS)
	$(CC) $(SOFLAGS) $(LDFLAGS) $^ -o $@
librpc.a: $(OBJS)
	$(AR) $@ $^
clean:
	rm -f *.o *.so *.a
cleantmp:
	rm -f *.o
	
# make rule
%.o : %.c
	$(CC) $(CCFLAGS) -c $^ -o $@	

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@