CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla

SRC = $(wildcard *.cc)

OBJECTS = $(SRC:.c=.o)

DEPENDS = ${OBJECTS:.o=.d}
EXEC = myProg

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies