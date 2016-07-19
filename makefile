full: imageProc.o processing.o processing.h
	g++ -o imageProc.out imageProc.o processing.o `pkg-config --cflags --libs opencv`
imageProc.o: imageProc.cpp
	g++ -c imageProc.cpp `pkg-config --cflags --libs opencv`
processing.o: processing.cpp processing.h
	g++ -c processing.cpp `pkg-config --cflags --libs opencv`
clean:
	rm -f *.out
	rm -f *.jpg
	rm -f *~
	rm -f *.o
