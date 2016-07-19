full: imageProc.o processing.o processing.h
	g++ `pkg-config --cflags --libs opencv` -o imageProc.out imageProc.o processing.o
imageProc.o: processing.h imageProc.cpp
	g++ `pkg-config --cflags --libs opencv` -c imageProc.cpp
processing.o: processing.cpp processing.h
	g++ `pkg-config --cflags --libs opencv` -c processing.cpp
clean:
	rm -f *.out
	rm -f *.jpg
	rm -f *~
