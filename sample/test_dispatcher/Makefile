# compile macro  
CC      = g++  
CFLAGS  = -g -Wall -std=c++11 
LDFLAGS = -L/usr/local/lib -lev
INCLUDES= -I/usr/local/include -I../../rpc 
  
# user modify: subdir, target and objects  
VPATH   = ../../rpc
EXENAME = ../../bin/test  
OBJECTS = net_util.o dispatcher.o main.o
  
# make target  
all:${EXENAME} cleantmp
../../bin/test: ${OBJECTS}
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