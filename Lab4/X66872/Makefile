OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: main.o llista.o solution.o
	g++ -o program.exe main.o llista.o solution.o
	rm *.o

solution.exe: main.o llista.o solution.o
	g++ -o solution.exe main.o llista.o solution.o
	rm *.o

solution.o: solution.cpp llista.hpp
	g++ -c solution.cpp $(OPCIONS)

main.o: main.cpp llista.hpp
	g++ -c main.cpp $(OPCIONS)

llista.o: llista.cpp llista.hpp
	g++ -c llista.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
