.PHONY: debug release clean rebuild cleantmp

CC = g++
CCFLAGS =-g -Wall

BIN_HOME = ../../bin

LDFLAGS = -L/usr/local/lib

MOBILE_INCL = -I../../net 
MOBILE_LIB = -lev

CCFLAGS += $(MOBILE_INCL)
LDFLAGS += $(MOBILE_LIB)

CCFLAGS += -std=c++11

LIBS = ../../net/libnet.a

OBJS = client.o

TARGET = $(BIN_HOME)/test_client

all:  $(TARGET) cleantmp
$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)
cleantmp:
	rm -f *.o
clean:
	rm -f *.o
	rm -f $(TARGET)
	
# make rule
%.o : %.c
	$(CC) $(CCFLAGS) -c $^ -o $@	

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@
