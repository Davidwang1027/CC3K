CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS=actiondisplay.o ba.o bd.o controller.o enemy.o floor.o main.o perpotion.o player.o textdisplay.o wa.o wd.o tempotion.o dragon.o gold.o
DEPENDS=${OBJECTS:.o=.d} 
EXEC=cc3k
${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
