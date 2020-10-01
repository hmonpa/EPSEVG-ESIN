OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: main.o conjunt_2enters.o
	g++ -o program.exe main.o conjunt_2enters.o
	rm *.o

solution.exe: main.o conjunt_2enters.o
	g++ -o solution.exe main.o conjunt_2enters.o
	rm *.o

main.o: main.cpp conjunt_2enters.hpp conjunt_2enters.rep
	g++ -c main.cpp $(OPCIONS)

conjunt_2enters.o: conjunt_2enters.cpp conjunt_2enters.hpp conjunt_2enters.rep
	g++ -c conjunt_2enters.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
