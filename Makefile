CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -Werror=vla -MMD
EXEC = raiinet
OBJECTS = main.o controller.o player.o link.o ability.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
	${MAKE} clean

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}

.PHONY: clean
