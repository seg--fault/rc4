all: main

main: main.cpp rc4.o
	g++ -o $@ $^
	
rc4.o: rc4.cpp rc4.h
	g++ -c $<

.PHONY: clean

clean:
	rm *.o
