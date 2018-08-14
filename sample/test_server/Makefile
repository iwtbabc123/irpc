# compile macro  
CC      = g++  
CFLAGS  = -g -Wall -std=c++11 
LDFLAGS = -L/usr/local/lib -lev
INCLUDES= -I/usr/local/include -I../../net 
  
# user modify: subdir, target and objects  
VPATH   = ../../net
EXENAME = ../../bin/test_socket  
OBJECTS = socket_util.o dispatcher.o acceptor.o channel.o buffer.o byte_stream.o package.o tcp_server.o main.o
  
# make target  
all:${EXENAME} cleantmp
../../bin/test_socket: ${OBJECTS}
	${CC} -o ${EXENAME} *.o ${LDFLAGS} ${INCLUDES}

cleantmp:
	rm -rf ${OBJECTS}

# make clean  
clean:  
	rm -rf ${EXENAME} ${OBJECTS}   
  
# dependence      
%.o : %.cpp  
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@  
%.o : %.cc  
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@ 