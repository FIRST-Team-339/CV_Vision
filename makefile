full:
	g++ `pkg-config --cflags --libs opencv` -o imageProc.out imageProc.cpp
clean:
	rm -f *.out
