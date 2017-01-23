disposable: xiao_fei_disposable.o Box.o
	g++ -o disposable xiao_fei_disposable.o Box.o -O3

xiao_fei_disposable.o: xiao_fei_disposable.cc Box.h
	g++ -c xiao_fei_disposable.cc -std=gnu++0x -O3

Box.o: Box.cc Box.h
	g++ -c Box.cc -O3 

clean: 
	rm persistent disposable xiao_fei_disposable.o xiao_fei_persistent.o Box.o
