.PHONY: debug release clean rebuild cleantmp

CC = g++
CCFLAGS =-g -Wall

BIN_HOME = ../../bin

LDFLAGS = -L/usr/local/lib -L/usr/local/protobuf/lib

MOBILE_INCL = -I/usr/local/protobuf/include -I../../net -I../../rpc -I../../proto
MOBILE_LIB = -lev -lprotobuf

CCFLAGS += $(MOBILE_INCL)
LDFLAGS += $(MOBILE_LIB)

CCFLAGS += -std=c++11

LIBS = ../../net/libnet.a ../../rpc/librpc.a

OBJS = main.o ../../proto/echo_test.pb.o

TARGET = $(BIN_HOME)/test_rpc_client

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
%.o : %.cc
	$(CC) $(CCFLAGS) -c $^ -o $@
