amr_csr_serial: amr_csr_serial.o Box.o
	g++ -o amr_csr_serial amr_csr_serial.o Box.o -O3

amr_csr_serial.o: amr_csr_serial.cc Box.h
	g++ -c amr_csr_serial.cc -std=gnu++11 -O3

Box.o: Box.cc Box.h
	g++ -c Box.cc -O3

clean: 
	rm amr_csr_serial amr_csr_serial.o Box.o
