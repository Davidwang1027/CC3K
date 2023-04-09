CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g -Werror=vla
SRC = $(wildcard *.cc)
OBJECTS = $(SRC:.c=.o)
DEPENDS=${OBJECTS:.o=.d} 
EXEC=myProgram
${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
