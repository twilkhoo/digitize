CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -Werror=vla -MMD
EXEC = raiinet
OBJECTS = main.o controller.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
# Remember to add -lX11 to the end of the linking line below for graphics.
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 
	${MAKE} clean

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}

.PHONY: clean
