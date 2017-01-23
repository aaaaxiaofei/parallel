disposable: disposable.o Box.o
	g++ -o disposable disposable.o Box.o -O3

disposable.o: disposable.cc Box.h
	g++ -c disposable.cc -std=gnu++0x -O3

Box.o: Box.cc Box.h
	g++ -c Box.cc -O3 

clean: 
	rm persistent disposable disposable.o Box.o
