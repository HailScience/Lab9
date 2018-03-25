#makefile

#Makefile
CXX = g++


buffer: main.o menu.o
	${CXX} main.o menu.o -o buffer

main.o: main.cpp
	${CXX} -c main.cpp

menu.o: menu.cpp
	${CXX} -c menu.cpp

clean:
	rm *.o buffer
